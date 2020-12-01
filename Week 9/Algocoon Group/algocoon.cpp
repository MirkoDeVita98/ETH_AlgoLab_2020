#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;

typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

std::istream & fp = std::cin;

void testcase(){
  int n, m; fp >> n >> m;
  
  graph G(n);
  edge_adder adder(G);
  
  for(int i = 0; i < m; ++i){
    int a, b, c; fp >> a >> b >> c;
    adder.add_edge(a, b, c);
  }
  
  long min_c = std::numeric_limits<long>::max();
  for(int i = 1; i < n; ++i){
    long flow1 = boost::push_relabel_max_flow(G, 0, i);
    long flow2 = boost::push_relabel_max_flow(G, i, 0);
    min_c = std::min({flow1, flow2, min_c});
  }
  
  std::cout << min_c << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  while(t--) testcase();
}