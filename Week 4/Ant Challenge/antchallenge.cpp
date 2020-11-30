#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

#define adj(i, j) ((*adj)[i][j])

using namespace std;


vector< vector<int> > *adj;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;



int dijkstra_dist(const weighted_graph &G, int s, int t) { 
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
  return dist_map[t]; 
}

void update_adj(weighted_graph &g, int h){
  //std::vector < boost::graph_traits < weighted_graph >::vertex_descriptor > p(boost::num_vertices(g));
  
  std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
  
  weight_map weights = boost::get(boost::edge_weight, g);
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) { 
    //std::cout << boost::source(∗it, G) << " " << boost::target(∗it, G) << "\n";
    long u = boost::source(*it, g);
    long v = boost::target(*it, g);
    if(weights[*it] < adj(u,v) || adj(u,v) == -1){
      adj(u, v) = weights[*it];
      //cout << u << "," << v << weights[*it] << "\n";
    }
  }
  
  //boost::prim_minimum_spanning_tree(g, &p[h]);
  
  /*for (std::size_t i = 0; i != p.size(); ++i){
    if(p[i] != i){
      int w = temp[p[i]][i];

      if(w != - 1){
        if(adj(p[i], i) == - 1 || adj(p[i], i) > w){
          cout << p[i] << "," << i << ": " << w << "\n" << flush;
          adj(p[i], i) = w;
        }
      }
      
    }
  }*/
    
 
}


void testcase(){
  int n, e, s, a, b; cin >> n >> e >> s >> a >> b;
  
  vector< weighted_graph > graphs(s, weighted_graph(n));
  // weight_map:  boost::get(boost::edge_weight, G);
  
  for(int i = 0; i < e; ++i){
    int t1, t2; cin >> t1 >> t2;
    for(int j = 0; j < s; ++j){
      int w; cin >> w;
      edge_desc e = boost::add_edge(t1, t2, graphs[j]).first;
      weight_map weights = boost::get(boost::edge_weight, graphs[j]);
      weights[e] = w;
    }
  }

  
  adj = new vector< vector<int> > (n, vector<int> (n, -1));
  
  for(int i = 0; i < s; ++i){
    int h; cin >> h;
    update_adj(graphs[i], h);
  }
  
  
  weighted_graph G(n);
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      if(adj(i, j) != -1){
        edge_desc e = boost::add_edge(i, j, G).first;
        weight_map weights = boost::get(boost::edge_weight, G);
        weights[e] = adj(i, j);
      }
    }
  }
  
  cout << dijkstra_dist(G, a, b) << "\n" << flush;
  
  delete adj;
  
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}