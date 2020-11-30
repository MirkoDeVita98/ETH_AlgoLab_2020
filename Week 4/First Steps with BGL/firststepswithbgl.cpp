#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <bits/stdc++.h>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

int dijkstra_max_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

  return *max_element(dist_map.begin(), dist_map.end());
}

int kruskal(const weighted_graph &G, weight_map weights) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  int sum = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    sum += weights[*it];
  }
  
  return sum;
}

void testcase(){
  int n, m; cin >> n >> m;
  
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  for(int i = 0; i < m; ++i){
    int a,b,w; cin >> a >> b >> w;
    edge_desc e = boost::add_edge(a, b, G).first;
    weights[e] = w;
  }
  
  cout << kruskal(G, weights) << " " << dijkstra_max_dist(G, 0) << "\n";
}

int main(int argc, const char* argv[]){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}