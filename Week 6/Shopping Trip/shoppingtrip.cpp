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
  int n,m; cin >> n >> m;
  long s; cin >> s;
  
  Graph G(n);
  EdgeCapacityMap  capacity = get(edge_capacity, G);
  ReverseEdgeMap  rev_edge = get(edge_reverse, G);
  EdgeAdder ea(G,capacity, rev_edge);
  
  set< int > shops;
  
  for(int i = 0; i < s; ++i){
    int shop; cin >> shop;
    shops.insert(shop);
  }
  
  for(int i = 0; i < m; ++i){
    int a, b; cin >> a >> b;
    ea.addSymmetricEdge(a, b, 1);
  }
  
  Vertex _source = 0;
  Vertex sink = add_vertex(G);
  
  set<int>::iterator it = shops.begin();
  while (it != shops.end())
  {
    ea.addEdge(*it, sink, 1);
    it++;
  }
  
  long flow = push_relabel_max_flow(G, _source, sink);

  if(flow == (long)shops.size()) cout << "yes\n";
  else cout << "no\n";
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
}