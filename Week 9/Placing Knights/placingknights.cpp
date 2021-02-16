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

typedef std::vector<int> VI;
typedef std::vector< VI > VII;
typedef std::pair<int, int> iPair;
typedef std::vector<iPair> VIP;

#define colored(i, j) ((i + j) % 2 == 0)
#define node(i, j) ((n*(i)) + j)
#define inside(i, j) ((((i) >= 0) && ((i) < n)) && (((j) >= 0) && ((j) < n)))

void testcase(){
  int n; fp >> n;
  graph G(n * n);
  edge_adder adder(G);  
  VII board(n, VI(n));
  
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  
  int valid = 0;
  
  VIP to_link;
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      fp >> board[i][j];
      if(board[i][j]){
        valid += 1;
        if(colored(i, j)){
          adder.add_edge(source, node(i, j), 1);
          to_link.push_back({i, j});
        }
        else adder.add_edge(node(i, j), sink, 1);
      }
    }
  }
  
  for(iPair cell : to_link){
    int i = cell.first;
    int j = cell.second;
    int index = node(i, j);
    if(inside(i - 1, j - 2) && board[i - 1][j - 2]) 
      adder.add_edge(index, node(i - 1, j - 2), 1);
        
    if(inside(i - 1, j + 2) && board[i - 1][j + 2]) 
      adder.add_edge(index, node(i - 1, j + 2) , 1);
      
    if(inside(i + 1, j - 2) && board[i + 1][j - 2]) 
      adder.add_edge(index, node(i + 1, j - 2), 1);
      
    if(inside(i + 1, j + 2) && board[i + 1][j + 2]) 
      adder.add_edge(index, node(i + 1, j + 2), 1);
      
    if(inside(i - 2, j - 1) && board[i - 2][j - 1]) 
      adder.add_edge(index, node(i - 2, j - 1), 1);
      
    if(inside(i - 2, j + 1) && board[i - 2][j + 1]) 
      adder.add_edge(index, node(i - 2, j + 1), 1);
      
    if(inside(i + 2, j - 1) && board[i + 2][j - 1]) 
      adder.add_edge(index, node(i + 2, j - 1), 1);
      
    if(inside(i + 2, j + 1) && board[i + 2][j + 1]) 
      adder.add_edge(index, node(i + 2, j + 1), 1);
  }
  
  std::cout << valid - boost::push_relabel_max_flow(G, source, sink) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}