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
  int l, p; cin >> l >> p;
  
  Graph G(l);
  EdgeCapacityMap  capacity = get(edge_capacity, G);
  ReverseEdgeMap  rev_edge = get(edge_reverse, G);
  EdgeAdder ea(G,capacity, rev_edge);
  
  
  vector<int> soldiers(l);
  for(int i = 0; i < l; ++i){
    int g, d; cin >> g >> d;
    soldiers[i] = d - g;
  }
  
  vector< vector<int> > edges(l, vector<int> (l, numeric_limits<int>::min()));
  
  for(int i = 0; i < p; i++){
    int f, t, c, C; cin >> f >> t >> c >> C;
    soldiers[f] += c;
    soldiers[t] -= c;
    ea.addEdge(f, t, C - c);
  }
  
  Vertex _source = add_vertex(G);
  Vertex sink = add_vertex(G);
  long demand = 0;
  
   for(int i = 0; i < l; i++){
      if(soldiers[i] >= 0){
          demand += soldiers[i];
          ea.addEdge(i, sink, soldiers[i]);
      } else {
          soldiers[i] *= -1;
          ea.addEdge(_source, i, soldiers[i]);
      }
    }
  
  long flow = push_relabel_max_flow(G, _source, sink);
  
  if(flow == demand) cout << "yes\n";
  else cout << "no\n";
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  while(t--) testcase();
}