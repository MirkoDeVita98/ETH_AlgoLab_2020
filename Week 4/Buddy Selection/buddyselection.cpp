#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
}
std::istream & fp = std::cin;

void testcase(){
  int n, c, f; fp >> n >> c >> f;
  
  graph G(n);
  
  std::unordered_map< std::string, std::vector<int > > features;
  
  for(int i = 0; i < n; ++i){
    std::unordered_map< int, int> common;
    for(int j = 0; j < c; ++j){
      std::string s; fp >> s;
      if(features.find(s) == features.end()) features.insert({s, {i}});
      else{
        for(int buddy : features[s]){
          if(common.find(buddy) == common.end()) common.insert({buddy, 1});
          else common[buddy] += 1;
        }
        features[s].push_back(i);
      } 
    }
    for(auto& it : common){
      if(it.second > f) boost::add_edge(i, it.first, G);
    }
  }
  
  if(2*maximum_matching(G) == n) std::cout << "not optimal\n";
  else std::cout << "optimal\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}