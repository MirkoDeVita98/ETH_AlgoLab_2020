/*#include <bits/stdc++.h>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
typedef boost::graph_traits<graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<graph>::vertices_size_type Vertices_size;

using namespace std;

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

vector< pair<int, int> > important;

void bridge(graph G, int u, bool visited[], int disc[],  int low[], int parent[]) { 

    static int time = 0; 
  
    visited[u] = true; 
  
    disc[u] = low[u] = ++time; 
  
    auto neighbours = boost::adjacent_vertices(u, G);
    for (auto v : make_iterator_range(neighbours)){
      
        if (!visited[v]){ 
            parent[v] = u; 
            bridge(G, v, visited, disc, low, parent); 
  
            low[u]  = min(low[u], low[v]); 
  
            if (low[v] > disc[u])
              important.push_back({u, v});

        } 
        else if ((int)v != parent[u]) 
            low[u]  = min(low[u], disc[v]); 
    } 
} 

void testcase2(){ 
  
  int n, m; cin >> n >> m;

  graph G(n);
  
  for(int i = 0; i < m; ++i){
    int e1, e2;  cin >> e1 >> e2;
    boost::add_edge(e1, e2, G);
  }

  bool *visited = new bool[n]; 
  int *disc = new int[n]; 
  int *low = new int[n]; 
  int *parent = new int[n]; 

  for (int i = 0; i < n; i++) { 
      parent[i] = -1; 
      visited[i] = false; 
  } 


  for (int i = 0; i < n; i++) 
      if (visited[i] == false) 
          bridge(G, i, visited, disc, low, parent); 
  
  
  vector< pair<int, int> > critical;
  
  for(pair<int, int> bridge : important){
    if(bridge.first < bridge.second) critical.push_back({bridge.first, bridge.second});
    else critical.push_back({bridge.second, bridge.first});
  }
  
  sort(critical.begin(), critical.end());
  
  cout << critical.size() << "\n";
  
  for(pair<int, int> b : critical){
    cout << b.first << " " << b.second << "\n";
  }
  
  important.clear();
  
} 


void testcase(){
  int n, m; cin >> n >> m;
  
  graph G(n);
  
  for(int i = 0; i < m; ++i){
    int e1, e2;  cin >> e1 >> e2;
    boost::add_edge(e1, e2, G);
  }
  
  boost::property_map < graph, edge_component_t >::type component = get(edge_component, G);

  std::size_t num_comps = biconnected_components(G, component);
  
  vector< pair<int, int> > critical;

  boost::graph_traits < graph >::edge_iterator ei, ei_end;
  
  for (tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
    if(component[*ei].size() == 1){
      if((source(*ei, G) < (target(*ei, G)) critical.push_back({(source(*ei, G), (target(*ei, G)});
      else critical.push_back({(target(*ei, G), (source(*ei, G)});
    }
  }

  sort(critical.begin(), critical.end());
  
  cout << critical.size() << "\n";
  
  for(pair<int, int> b : critical){
    cout << b.first << " " << b.second << "\n";
  }
  
}

int main(int argc, const char* argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}*/

#include <boost/config.hpp>
#include <vector>
#include <list>
#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iterator>
#include <iostream>

namespace boost
{
  struct edge_component_t
  {
    enum
    { num = 555 };
    typedef edge_property_tag kind;
  }
  edge_component;
}

using namespace std;

void testcase()
{
  using namespace boost;
  
  typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property < edge_component_t, std::size_t > >graph_t;

  graph_t g(9);
  
  int n, m; cin >> n >> m;
  
   for(int i = 0; i < m; ++i){
    int e1, e2;  cin >> e1 >> e2;
    boost::add_edge(e1, e2, g);
  }
  
  property_map < graph_t, edge_component_t >::type
    component = get(edge_component, g);

  std::size_t num_comps = biconnected_components(g, component);
  

  graph_traits < graph_t >::edge_iterator ei, ei_end;
  
  vector< vector<graph_traits < graph_t >::edge_iterator> > comp(num_comps);
  
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
    comp[component[*ei]].push_back(ei); 
  }
  
  vector< pair<int, int> > critical;
  
  for(int i = 0; i < (int)num_comps; ++i){
    if(comp[i].size() == 1){
      graph_traits < graph_t >::edge_iterator ei = (comp[i][0]);
      if(source(*ei, g) < target(*ei, g)) critical.push_back({source(*ei, g), target(*ei, g)});
      else critical.push_back({target(*ei, g), source(*ei, g)});
    }
  }
  
  sort(critical.begin(), critical.end());
  
  cout << critical.size() << "\n";
  
  for(pair<int, int> b : critical){
    cout << b.first << " " << b.second << "\n";
  }

}

int main(int argc, const char* argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}

