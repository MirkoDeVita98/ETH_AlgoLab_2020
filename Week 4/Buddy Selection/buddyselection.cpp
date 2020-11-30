#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/property_map/vector_property_map.hpp>



typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

using namespace std;

bool maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    vector<bool> checker(n, false);
    std::vector<vertex_desc> mate_map(n); 
    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    for (int i = 0; i < n; ++i) {
        if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) {
            checker[i] = true;
            checker[mate_map[i]] = true;
        }
    }
    for(int i = 0; i < n; ++i) {
        if(!checker[i]) return false;
    }
    return true;
}

void testcase(){
  int n, c, f; cin >> n >> c >> f;
  
  map < string, int > feat;
  
  int num_c = 0;
  graph G(n);
  
  vector< set<int> > buddies (n);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < c; ++j){
      string temp; cin >> temp;
      map< string, int >::iterator exist = feat.find (temp);
      
      if (exist == feat.end()){
        buddies[i].insert(num_c);
        feat.insert( pair< string, int >(temp, num_c));
        ++num_c;
      }
      else{
        buddies[i].insert(exist -> second);
      }
      
    }
  }
  
  for(int i = 0; i < n; ++i){
    for(int j = i + 1; j < n; ++j){
      int count = 0;

      for(int c1 : buddies[i]){
        
        if(buddies[j].find(c1) != buddies[j].end()) ++count;
        if(count > f){
          boost::add_edge(i, j, G);
          break;
        }

      }
    }
  }
  
  if(maximum_matching(G)) cout << "not optimal\n";
  else cout << "optimal\n";
  
  
}

int main(int agrc, const char* argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}