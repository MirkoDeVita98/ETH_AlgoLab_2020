#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 Point;
typedef std::tuple<long, Index, Index> Edge;
typedef std::vector< Edge> EdgeV;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, long>> graph;
typedef boost::property_map<graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator oe;

std::istream & fp = std::cin;

int func(const graph & G, int k, const K::FT & s,const weight_map & weights){
  int n = boost::num_vertices(G);
  std::vector<bool> visited(n, false); 
  std::vector<int> c_size; 
  
  for(int i = 0; i < n; i++){
    if(visited[i]) continue; 
    int size = 0; 
    std::queue<int> Q; 
    Q.push(i); 
    while(!Q.empty()){
      int u = Q.front(); 
      Q.pop();
      visited[u] = true; 
      size++; 
      oe e_beg, e_end;
      for (boost::tie(e_beg, e_end) = boost::out_edges(u, G); e_beg != e_end; ++e_beg){
        int v = boost::target(*e_beg, G);
        if(!visited[v] && weights[*e_beg] < s) Q.push(v);
      }
    }
    c_size.push_back(size); 
  }
  
  int s1 = 0; 
  int s2 = 0; 
  int s3 = 0; 
  int f = 0; 
  for(int component : c_size){
    if(component == 1) s1++; 
    else if(component == 2) s2++; 
    else if(component == 3) s3++; 
    
    if(component >= k) f++; 
  }
  
  switch(k){
    case(1):
      return f;
    case(2):
      return f + s1 / 2; 
    case(3):
      if(s2 <= s1) return f + s2 + (s1 - s2) / 3; 
      else return f + s1 + (s2 - s1) / 2; 
    case(4):
      int match2 = s2/2; 
      int match31 = std::min(s1, s3); 
      int rem1 = std::max(0, s1 - s3); 
      int rem2 = s2 % 2; 
      int rem3 = std::max(0, s3-s1); 
      int extra = 0; 
      if(rem1 > 1) extra = (rem1 + rem2 * 2) / 4; 
      else if(rem3) extra += rem2 + (rem3 - rem2) / 2; 
      return extra + match2 + match31 + f; 
  }
  
  //error
  return -1;
  
}

void testcase(){
  int n, k, f; fp >> n >> k >> f;
  long s; fp >> s;
  
  std::vector<std::pair<Point, int>> pts(n); 
  for(int i = 0; i < n; i++){
    int x, y; 
    fp >> x >> y; 
    pts[i] = {Point(x, y), i}; 
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  EdgeV edges;
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
    Index u = e -> first->vertex( (e -> second+1)%3 )->info();
    Index v = e -> first->vertex( (e -> second+2)%3 )->info();
    if(u > v) std::swap(u, v);
    long weight = t.segment(e).squared_length();
    edges.push_back(std::make_tuple(weight, u, v));
  }
  
  std::sort(edges.begin(), edges.end());
  
  boost::disjoint_sets_with_storage<> uf(n);
  graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  Index num_comp = n;
  std::vector<long> edges_to_try;
  for(EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e){
    Index u = std::get<1>(*e);
    Index v = std::get<2>(*e);
    if(uf.find_set(u) != uf.find_set(v)){
      uf.link(u, v);
      edge_desc ed = boost::add_edge(u, v, G).first;
      weights[ed] = std::get<0>(*e);
      edges_to_try.push_back(std::get<0>(*e));
      num_comp -= 1;
      if(num_comp == 1) break;
    }
  }
  
  int max_f_with_s0 = func(G, k, s, weights);
  std::sort(edges_to_try.begin(), edges_to_try.end());
  int l = 0;
  int r = edges_to_try.size() - 1;

  while(l < r){
    int m = (l + r) / 2;
    int res = func(G, k, edges_to_try[m], weights);
    if(res >= f) l = m + 1; 
    else r = m;
  }
  
  std::cout << edges_to_try[l - 1] << " " << max_f_with_s0 << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}