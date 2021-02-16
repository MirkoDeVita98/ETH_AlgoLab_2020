#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;


class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

std::istream & fp = std::cin;

#define in(i, j, k) (2*(((m)*(i)) + j) + k)

void testcase(){
  int m, n, k, c; fp >> m >> n >> k >> c;
  graph G(2 * n * m);
  edge_adder adder(G);
  
  vertex_desc source = boost::add_vertex(G);
  vertex_desc sink = boost::add_vertex(G);
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      int north = i - 1;
      int south = i + 1;
      int west = j - 1;
      int east = j + 1;
      int escape = 0;
      
      if(south < n) adder.add_edge(in(i, j, 1), in(south, j, 0), 1);
      else escape += 1;
      
      if(north >= 0) adder.add_edge(in(i, j, 1), in(north, j, 0), 1);
      else escape += 1;
      
      if(west >= 0) adder.add_edge(in(i, j, 1), in(i, west, 0), 1);
      else escape += 1;
      
      if(east < m) adder.add_edge(in(i, j, 1), in(i, east, 0), 1);
      else escape += 1;
      
      if(escape) adder.add_edge(in(i, j, 1), sink, escape);
      adder.add_edge(in(i, j, 0), in(i, j, 1), c);
    }
  }
  
  for(int i = 0; i < k; ++i){
    int x, y; fp >> x >> y;
    adder.add_edge(source, in(y, x, 0), 1);
  }
  
  std::cout << boost::push_relabel_max_flow(G, source, sink) << "\n";
}

int main(int argc, const char *argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}