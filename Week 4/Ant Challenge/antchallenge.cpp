#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator oe;
typedef boost::graph_traits<weighted_graph>::edge_iterator EdgeIt;  

std::istream & fp = std::cin;

#define map(u, v) ((*_map)[std::min(u, v)][std::max(u, v)])

struct w_edge{
  int u;
  int v;
  int w;
  
  bool operator <(const w_edge &that) const{
    return w > that.w;
  }
};

std::vector< std::vector<int> > *_map;

//kruskal would work as well
void prim(weighted_graph & G, int src){
  int n = boost::num_vertices(G);
  weight_map weights = boost::get(boost::edge_weight, G);
  std::vector<bool> visited(n, false);
  std::priority_queue< w_edge > pq;
  
  visited[src] = true;
  
  oe e_beg, e_end;
  
  for (boost::tie(e_beg, e_end) = boost::out_edges(src, G); e_beg != e_end; ++e_beg) {
    int v = boost::target(*e_beg, G);
    pq.push({src, v, weights[*e_beg]});
  }
  
  while(!pq.empty()){
    int u = pq.top().u;
    int v = pq.top().v;
    int w = pq.top().w;
    pq.pop();
    if(visited[v]) continue;
    visited[v] = true;
    map(u, v) == -1 ? map(u, v) = w : map(u, v) = std::min(map(u, v), w);
    for (boost::tie(e_beg, e_end) = boost::out_edges(v, G); e_beg != e_end; ++e_beg) {
      int neighbor = boost::target(*e_beg, G);
      if(!visited[neighbor]) pq.push({v, neighbor, weights[*e_beg]});
    }
  }
}

int dijkstra_dist(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void testcase(){
  int n, e, s, a, b; fp >> n >> e >> s >> a >> b;
  std::vector< weighted_graph> nets(s, weighted_graph(n));
  for(int i = 0; i < e; ++i){
    int t1, t2; fp >> t1 >> t2;
    for(int j = 0; j < s; ++j){
      int w; fp >> w;
      edge_desc ed = boost::add_edge(t1, t2, nets[j]).first;
      weight_map weights = boost::get(boost::edge_weight, nets[j]);
      weights[ed]= w;
    }
  }
  
  
  
  _map = new std::vector<std::vector<int>> (n, std::vector<int> (n, -1));
  
  for(int i = 0; i < s; ++i){
    int src; fp >> src;
    prim(nets[i], src);
  }
  
  weighted_graph G(n);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j <= i; ++j){
      if(map(i, j) == -1) continue;
      edge_desc ed = boost::add_edge(i, j, G).first;
      weight_map weights = boost::get(boost::edge_weight, G);
      weights[ed]= map(i, j);
    }
  }
  
  std::cout << dijkstra_dist(G, a, b) << "\n";
  
  delete _map;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}