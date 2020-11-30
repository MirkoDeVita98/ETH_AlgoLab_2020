#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> graph;
typedef boost::graph_traits < graph >::out_edge_iterator oe;

std::istream & fp = std::cin;

void testcase(){
  int n, m, k; fp >> n >> m >> k;
  
  std::vector<int> h(n);
  for(int i = 0; i < n; ++i){
    fp >> h[i];
  }
  
  graph G(n);
  std::vector<int> parent(n, 0);
  
  
  for(int i = 0; i < n - 1; ++i){
    int u, v; fp >> u >> v;
    boost::add_edge(u, v, G);
    parent[v] = u;
  }
  
  std::stack<int> S;
  std::set< std::pair<int, int> > T;
  std::vector<bool> in_interval(n, false); 
  int interval = 0;
  
  S.push(0);
  int first = 0;
  
  std::set<int> critical_points;
  
  while(!S.empty()){
    int v = S.top();
    S.pop();
      
    in_interval[v] = true;
    T.insert({h[v], v});
    
    
    ++interval;
    
    
    int max = T.empty() ? 0 : T.rbegin() -> first; 
    int min = T.empty() ? 0 : T.begin() -> first; 
    
    if(!T.empty() && max - min <= k && interval == m) critical_points.insert(first);
    
    if(interval == m){
      in_interval[first] = false;
      T.erase({h[first], first});
      --interval;
      //update first
      oe ei, ei_end;
      for (boost::tie(ei, ei_end) = boost::out_edges(first, G); ei != ei_end; ++ei) {
        int child = boost::target ( *ei, G);
        if(in_interval[child]) first = child;
      }
      
    }

    bool leaf = true;
    
    oe ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::out_edges(v, G); ei != ei_end; ++ei) {
      leaf = false;
      S.push(boost::target (*ei, G));
    }
    
    
    if(leaf){
      
      while(!S.empty() && v != parent[S.top()]){
        in_interval[v] = false;
        T.erase({h[v], v});
        if(!in_interval[parent[first]]){
          in_interval[parent[first]] = true;
          first = parent[first];
          T.insert({h[first], first});
          ++interval;
        }
        --interval;
        v = parent[v];
      }
      
    }
    
        
  }
  
  if(!critical_points.empty()){
    for(int critical : critical_points) std::cout << critical << " ";
  }
  else std::cout << "Abort mission";
  
  std::cout << "\n";
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--)
    testcase();

}