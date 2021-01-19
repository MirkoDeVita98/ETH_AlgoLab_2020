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

typedef std::vector<int> VI;
typedef std::pair<int, int> iPair;

std::istream & fp = std::cin;

#define node(i, j) ((w*(i)) + j)

void testcase(){
  int h, w; fp >> h >> w;
  graph G(h*w);
  edge_adder adder(G);
  std::string note; fp >> note;
  int n = note.length();
  std::unordered_map<char, iPair> map;
  for(int i = 0; i < n; ++i){
    if(map.find(note[i]) == map.end()){
      auto new_node = boost::add_vertex(G);
      map.insert({note[i], {new_node, 1}});
    }
    else map[note[i]].second += 1;
  }
  
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  
  for(const auto & entry : map){
    iPair letter = entry.second;
    adder.add_edge(letter.first, sink, letter.second);
  }
  
  for(int i = 0; i < h; ++i){
    std::string text; fp >> text;
    for(int j = 0; j < w; ++j){
      adder.add_edge(source, node(i, j), 1);
      adder.add_edge(node(i, j), map[text[j]].first, 1);
    }
  }
  
  for(int i = 0; i < h; ++i){
    std::string text; fp >> text;
    for(int j = 0; j < w; ++j){
      adder.add_edge(node(i, w - j - 1), map[text[j]].first, 1);
    }
  }
  
  if(boost::push_relabel_max_flow(G, source, sink) == n) std::cout << "Yes\n";
  else std::cout << "No\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0); 
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}