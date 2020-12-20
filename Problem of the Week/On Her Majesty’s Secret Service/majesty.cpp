#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

std::istream & fp = std::cin;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> dijkstra_graph;
typedef boost::property_map<dijkstra_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<dijkstra_graph>::edge_descriptor edge_desc;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> card_graph;
typedef boost::graph_traits<card_graph>::vertex_descriptor vertex_desc;

bool escape(int t, const std::vector< std::vector<int> > & dist_map, const std::vector<int> & shelters,int c, int d){
  
  int a = (int)dist_map.size();
  int s = (int)shelters.size();
  card_graph G(a + c*s);
  
  for(int i = 0; i < a; ++i){
    for(int j = 0; j < s; ++j){
      for(int k = 0; k < c; ++k){
        if(dist_map[i][shelters[j]] <= t - (k + 1) * d){
          boost::add_edge(i, a + k*s + j, G);
        }
      }
    }
  }
  
  std::vector<boost::graph_traits<card_graph>::vertex_descriptor> mate(a + c*s);
  edmonds_maximum_cardinality_matching(G, &mate[0]);
  
  return (int)boost::matching_size(G, &mate[0]) == a;
  
}

void testcase(){
  int n, m, a, s, c, d; fp >> n >> m >> a >> s >> c >> d;
  dijkstra_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  int total_time = 0;
  for(int i = 0; i < m; ++i){
    char w; fp >> w;
    int x, y, z; fp >> x >> y >> z;
    
    total_time += z;
    
    edge_desc e1 = boost::add_edge(x, y, G).first;
    weights[e1] = z;
    
    if(w == 'L'){
      edge_desc e2 = boost::add_edge(y, x, G).first;
      weights[e2] = z;
    }
  }
  
  std::vector< std::vector<int> > dist_map(a, std::vector<int> (n));
  for(int i = 0; i < a; ++i){
    int agent_pos; fp >> agent_pos;
    boost::dijkstra_shortest_paths(G, agent_pos, boost::distance_map(boost::make_iterator_property_map(dist_map[i].begin(), boost::get(boost::vertex_index, G))));
  }
  
  std::vector<int> shelters(s);
  for(int i = 0; i < s; ++i) fp >> shelters[i];
  
  int L = 0, R = total_time + c*d;
  while(L < R){
    int mid = (L + R) / 2;
    
    if(escape(mid, dist_map, shelters, c, d)) R = mid;
    else L = mid + 1;
    
  }
  
  std::cout << L << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}