#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>


using namespace std;

typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
    boost::no_property, boost::property < boost::edge_weight_t, long > > UGraph;
typedef boost::property_map < UGraph, boost::edge_weight_t >::type UWeightMap;
typedef boost::graph_traits < UGraph >::edge_descriptor UEdge;
typedef boost::graph_traits < UGraph >::vertex_descriptor UVertex;


void testcase(){
  int n,m,k,x,y; cin >> n >> m >> k >> x >> y;
  
  struct MyEdge{
    int a,b,c;
    MyEdge(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
  };
  
  UGraph G(n*(k + 1)); 
  int nv = boost::num_vertices(G);
  y += n*k; 
  UWeightMap wmap = boost::get(boost::edge_weight, G);
  vector<MyEdge> riveredges;
  
  for(int i = 0; i < m; ++i){
    int a,b,c,d; cin >> a >> b >> c >> d;
    if(d) riveredges.push_back(MyEdge(a,b,c));
    
    for(int j = 0; j <= k; ++j){
      int va = j*n + a;
      int vb = j*n + b;
      UEdge e; bool success;
      boost::tie(e, success) = boost::add_edge(va, vb, G);
      wmap[e] = c;
    }
  }
  
  int re = riveredges.size();
  
  for(int i = 0; i < re; ++i){
    MyEdge me = riveredges[i];
    
    for(int j = 0; j < k; ++j){
      int va = j*n + me.a;
      int vb = (j + 1)*n + me.b;
      
      //we add the edge that skip the repetition
      UEdge e; bool success;
      boost::tie(e, success) = boost::add_edge(va, vb, G);
      wmap[e] = me.c;
      
      //and the edge for the repetition
      
      int var = va + n;
      int vbr = vb - n;
      boost::tie(e, success) = boost::add_edge(var, vbr, G);
      wmap[e] = me.c;
      
    }
  }
  
  std::vector<UVertex> p(nv);
  std::vector<long> d(nv);
  boost::dijkstra_shortest_paths(G, x,
    predecessor_map(boost::make_iterator_property_map(p.begin(), boost::get(boost::vertex_index, G))).
    distance_map(boost::make_iterator_property_map(d.begin(), boost::get(boost::vertex_index, G))));

  cout << d[y] << "\n";
  
}

int main(int argc, const char * argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  while(t--) testcase();
  
  return 0;
}