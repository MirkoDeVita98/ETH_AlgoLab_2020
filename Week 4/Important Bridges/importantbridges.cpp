#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_name_t, int>> Graph;
typedef boost::property_map<Graph, boost::edge_name_t>::type ComponentMap;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;

std::istream & fp = std::cin;

typedef std::pair<int, int> iPair;

void testcase(){
  int n, m; fp >> n >> m; 
  Graph G(n);
  for(int i = 0; i < m; ++i){
    int e1, e2; fp >> e1 >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  ComponentMap componentmap = boost::get(boost::edge_name, G);
  int ncc = boost::biconnected_components(G, componentmap);
  std::vector<int> componentsize(ncc, 0);
  EdgeIt ebeg, eend;
  
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg){
    componentsize[componentmap[*ebeg]] += 1;
  }
  
  std::vector< iPair> critical;
  for (boost::tie(ebeg, eend) = boost::edges(G); ebeg != eend; ++ebeg){
    if (componentsize[componentmap[*ebeg]] == 1){
      int u = boost::source(*ebeg, G);
      int v = boost::target(*ebeg, G);
      critical.push_back({std::min(u, v), std::max(u, v)});
    }
  }
  std::sort(critical.begin(), critical.end());
  std::cout << critical.size() << std::endl;
  for(iPair bridge : critical){
    std::cout << bridge.first << " " << bridge.second << "\n";
  }
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}