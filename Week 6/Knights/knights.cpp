#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef  adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef  adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > > >  Graph;
typedef  property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef  property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef  property_map<Graph, edge_reverse_t>::type  ReverseEdgeMap;
typedef  graph_traits<Graph>::vertex_descriptor Vertex;
typedef  graph_traits<Graph>::edge_descriptor Edge;

struct EdgeAdder {
  EdgeAdder(Graph & G, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge) : G(G), capacity(capacity), rev_edge(rev_edge) {}

  void addEdge(int u, int v, long c) {
    Edge e, reverseE;
    tie(e, tuples::ignore) = add_edge(u, v, G);
    tie(reverseE, tuples::ignore) = add_edge(v, u, G);
    capacity[e] = c;
    capacity[reverseE] = 0;
    rev_edge[e] = reverseE;
    rev_edge[reverseE] = e;
  }
  
  void addSymmetricEdge(int u, int v, long c) {
    Edge e, reverseE;
    tie(e, tuples::ignore) = add_edge(u, v, G);
    tie(reverseE, tuples::ignore) = add_edge(v, u, G);
    capacity[e] = c;
    capacity[reverseE] = c;
    rev_edge[e] = reverseE;
    rev_edge[reverseE] = e;
  }
  Graph &G;
  EdgeCapacityMap  &capacity;
  ReverseEdgeMap  &rev_edge;
};

void testcase(){
  int m, n, k, c; cin >> m >> n >> k >> c;
  
  int n_int = n * m;
  Graph G(2 * n_int);
  EdgeCapacityMap  capacity = get(edge_capacity, G);
  ReverseEdgeMap  rev_edge = get(edge_reverse, G);
  EdgeAdder ea(G,capacity, rev_edge);
  
  Vertex _source = add_vertex(G);
  Vertex sink = add_vertex(G);
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      int north = i - 1;
      int south = i + 1;
      int west = j - 1;
      int east = j + 1;
      
      int intersection = m * i + j;
      int intersection_prime = (m * i + j) + n_int;
      
      ea.addEdge(intersection, intersection_prime, c);
      
      if(south <= n - 1){
        int int_south = m * south + j;
        ea.addEdge(intersection_prime, int_south, 1);
      }
      else ea.addEdge(intersection_prime, sink, 1);
      
      if(north >= 0){
        int int_north = m * north + j;
        ea.addEdge(intersection_prime, int_north, 1);
      }
      else ea.addEdge(intersection_prime, sink, 1);
      
      if(west >= 0){
        int int_west = m * i + west;
        ea.addEdge(intersection_prime, int_west, 1);
      }
      else ea.addEdge(intersection_prime, sink, 1);
      
      if(east <= m - 1){
        int int_east = m * i + east;
        ea.addEdge(intersection_prime, int_east, 1);
      }
      else ea.addEdge(intersection_prime, sink, 1);
    }
    
  }
  
  
  for(int l = 0; l < k; ++l){
    int x, y; cin >> x >> y;
    int intersection = m * y + x;
    ea.addEdge(_source, intersection , 1);
  }
  
  cout << push_relabel_max_flow(G, _source, sink) << "\n";
}

int main(int argc, const char * argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  while(t--) testcase();
}