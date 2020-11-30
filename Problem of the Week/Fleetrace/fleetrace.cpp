#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#define MAX_COST 50

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


std::istream & fp = std::cin;

void testcase(){
  int b, s, p; fp >> b >> s >> p;
  
  graph G(b + s);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  edge_adder adder(G);  
  
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  
  for(int i = 0; i < b; ++i) adder.add_edge(source, i, 1, 0);
  for(int i = 0; i < s; ++i){
    adder.add_edge(i + b, sink, 1, 0);
    adder.add_edge(source, i + b, 1, MAX_COST);
  } 
  
  for(int i = 0; i < p; ++i){
    int b_i, s_i, c_i; fp >> b_i >> s_i >> c_i;
    adder.add_edge(b_i, s_i + b, 1, MAX_COST - c_i);
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  long cost = boost::find_flow_cost(G);
  long flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e){
    flow += c_map[*e] - rc_map[*e];     
  }
  
  std::cout << MAX_COST*flow - cost << "\n"; 
  
  
  
}

int main(int argc, const char *argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}