#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

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
    auto w_map = boost::get(boost::edge_weight, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;
    w_map[rev_e] = -cost;
  }
};

typedef std::vector<int> VI;

std::istream & fp = std::cin;

#define state(i) (n + m + i - 1)
#define land(i) (n + i)
#define client(i) (i)
#define MAX_COST 100

void testcase(){
  int n, m, s; fp >> n >> m >> s;
  graph G(n + m + s);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);

  for(int i = 1; i <= s; ++i){
    int l; fp >> l;
    adder.add_edge(state(i), sink, l, 0);
  }
  
  for(int i = 0; i < m; ++i){
    int st; fp >> st;
    adder.add_edge(land(i), state(st), 1, 0);
  }
  
  for(int i = 0; i < n; ++i){
    adder.add_edge(source, client(i), 1, 0);
    for(int j = 0; j < m; ++j){
      int b; fp >> b;
      adder.add_edge(client(i), land(j), 1, MAX_COST - b);
    }
  }
  
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  int cost = boost::find_flow_cost(G);
  int s_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) s_flow += c_map[*e] - rc_map[*e];  
  std::cout << s_flow << " " << s_flow*MAX_COST - cost << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0); 
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}