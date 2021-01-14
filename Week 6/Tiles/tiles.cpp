//two different approaches: max flow on a bipartite graph or maximum cardinality matching (the former was the intended solution)

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

#define coord(i, j) ((w*(i)) + j)
#define colored(i, j) ((i + j) % 2 == 0)
#define cross(i, j) (grid[i][j] == 'x')

void testcase(){
  int w, h; fp >> w >> h;
  graph G(w*h);
  edge_adder adder(G);
  
  vertex_desc source = boost::add_vertex(G);
  vertex_desc sink = boost::add_vertex(G);
  
  std::vector<std::vector<char>> grid(h, std::vector<char>(w));
  
  int dots = 0;
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      fp >> grid[i][j];
      if(grid[i][j] == '.') dots += 1;
    }
  }
  
  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){
      if(cross(i, j)) continue;
      if(!colored(i, j)) adder.add_edge(coord(i, j), sink, 1);
      else{
        int north = i - 1;
        int south = i + 1;
        int west = j - 1;
        int east = j + 1;
        
        if(north >= 0 && !cross(north, j))
          adder.add_edge(coord(i, j), coord(north, j), 1);
        
        if(south < h && !cross(south, j))
          adder.add_edge(coord(i, j), coord(south, j), 1);
        
        if(west >= 0 && !cross(i, west))
          adder.add_edge(coord(i, j), coord(i, west), 1);
          
        if(east < w && !cross(i, east))
          adder.add_edge(coord(i, j), coord(i, east), 1);
          
        adder.add_edge(source, coord(i, j), 1);
      }
    }
  }
  if(boost::push_relabel_max_flow(G, source, sink) == std::ceil((float)dots/2)) std::cout << "yes\n";
  else std::cout << "no\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}


/*#include <bits/stdc++.h>
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
}*/