#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/property_map/vector_property_map.hpp>



typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_desc;

using namespace std;
using namespace boost;


void testcase(){
  int w, h; cin >> w >> h;
  
  char matrix[h][w];
  vector< vector<int> > m_dots(h, vector<int>(w, - 1));
  int dots = 0;
  
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      cin >> matrix[i][j];
      if(matrix[i][j] == '.'){
        m_dots[i][j] = dots;
        ++dots;
      } 
    }
  }
  
  Graph G(dots);
  
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      if(m_dots[i][j] != -1){
        int north = i - 1;
        int south = i + 1;
        int west = j - 1;
        int east = j + 1;
      
        if(north >= 0 && m_dots[north][j] != -1) add_edge(m_dots[north][j], m_dots[i][j], G);
        if(south <= h - 1 && m_dots[south][j] != -1) add_edge(m_dots[south][j], m_dots[i][j], G);
        if(west >= 0 && m_dots[i][west] != -1) add_edge(m_dots[i][west], m_dots[i][j], G);
        if(east <= w - 1 && m_dots[i][east] != -1) add_edge(m_dots[i][east], m_dots[i][j], G);
      }
    }
  }
  
  vector<graph_traits<Graph>::vertex_descriptor> mate(dots);

  bool success = checked_edmonds_maximum_cardinality_matching(G, &mate[0]);

  int size = matching_size(G, &mate[0]);
  
  if(success && size == ceil((float)dots / 2)) cout << "yes\n";
  else cout << "no\n";
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}