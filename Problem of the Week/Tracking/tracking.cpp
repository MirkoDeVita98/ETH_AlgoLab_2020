#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

std::istream & fp = std::cin;

#define state(u, j) (((j)*(n)) + u)

void testcase(){
  int n, m, k, x ,y; fp >> n >> m >> k >> x >> y;
  weighted_graph G(n*(k+ 1));
  weight_map weights = boost::get(boost::edge_weight, G);
  
  for(int i = 0; i < m; ++i){
    int a, b, c, d; fp >> a >> b >> c >> d;
    for(int j = 0; j < k; ++j){
      edge_desc e = boost::add_edge(state(a, j), state(b, j + d), G).first;
      weights[e] = c;
      e = boost::add_edge(state(b, j), state(a, j + d), G).first;
      weights[e] = c;
    }
    edge_desc e = boost::add_edge(state(a, k), state(b, k), G).first;
    weights[e] = c;
    e = boost::add_edge(state(b, k), state(a, k), G).first;
    weights[e] = c;
  }
  
  std::cout << dijkstra_dist(G, x, state(y, k)) << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}