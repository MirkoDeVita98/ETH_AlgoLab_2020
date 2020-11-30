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

std::istream & fp = std::cin;


#define inside(i, j) (((i >= 0) && (i < n)) && ((j >= 0) && (j < n)))
#define is_white(i, j) ((i + j) % 2 == 0)

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
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
  int n; fp >> n;
  graph G(n*n);
  edge_adder adder(G);
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  
  std::vector< int > board(n * n, 0);
  
  int valid = 0;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      fp >> board[i * n + j];
      if(board[i * n + j]){
        ++valid;
        if(is_white(i, j)) adder.add_edge(source, i * n + j, 1);
        else adder.add_edge(i * n + j, sink, 1);
      }
    } 
  }
  
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      
      if(!is_white(i,j)) continue;
      
      int index = i * n + j;
      
      if(inside(i - 1, j - 2) && board[(i - 1) * n +  (j - 2)]) 
        adder.add_edge(index, (i - 1) * n +  (j - 2), 1);
        
      if(inside(i - 1, j + 2) && board[(i - 1) * n + (j + 2)]) 
        adder.add_edge(index, (i - 1) * n +  (j + 2), 1);
        
      if(inside(i + 1, j - 2) && board[(i + 1) * n +  (j - 2)]) 
        adder.add_edge(index, (i + 1) * n + (j - 2), 1);
        
      if(inside(i + 1, j + 2) && board[(i + 1) * n + (j + 2)]) 
        adder.add_edge(index, (i + 1) * n +  (j + 2), 1);
        
      if(inside(i - 2, j - 1) && board[(i - 2) * n +  (j - 1)]) 
        adder.add_edge(index, (i - 2) * n +  (j - 1), 1);
        
      if(inside(i - 2, j + 1) && board[(i - 2) * n +  (j + 1)]) 
        adder.add_edge(index, (i - 2) * n +  (j + 1), 1);
        
      if(inside(i + 2, j - 1) && board[(i + 2) * n +  (j - 1)]) 
        adder.add_edge(index, (i + 2) * n +  (j - 1), 1);
        
      if(inside(i + 2, j + 1) && board[(i + 2) * n +  (j + 1)]) 
        adder.add_edge(index, (i + 2) * n +  (j + 1), 1);
      
    }
  }
  
  long flow = boost::push_relabel_max_flow(G, source, sink);
  
  std::cout << valid - flow << "\n"; 
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  while(t--) testcase();
  
  return 0;
}