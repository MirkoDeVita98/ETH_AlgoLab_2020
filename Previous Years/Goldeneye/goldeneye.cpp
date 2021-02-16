#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::vector< std::pair<K::Point_2, K::Point_2> > VPP;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::istream & fp = std::cin;

bool f(const EdgeV & edges, const K::FT & p, const VPP & queries, const Delaunay & tr){
  int n = tr.number_of_vertices();
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && std::get<2>(*e) <= p; ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  
  for(std::pair<K::Point_2, K::Point_2> points : queries){
    auto s = tr.nearest_vertex(points.first);
    auto t = tr.nearest_vertex(points.second);
    
    bool connected = uf.find_set(s -> info()) == uf.find_set(t -> info());
    connected = connected && 4*CGAL::squared_distance(s -> point(), points.first) <= p;
    connected = connected && 4*CGAL::squared_distance(t -> point(), points.second) <= p;
    
    if(!connected) return false;
  }
  
  return true;
}

void true_queries(const EdgeV & edges, const K::FT & p, const VPP & queries, const Delaunay & tr, VPP & new_queries, std::vector<K::FT> & tries){
  int n = tr.number_of_vertices();
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && std::get<2>(*e) <= p; ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  
  for(std::pair<K::Point_2, K::Point_2> points : queries){
    auto s = tr.nearest_vertex(points.first);
    auto t = tr.nearest_vertex(points.second);
    
    bool connected = uf.find_set(s -> info()) == uf.find_set(t -> info());
    connected = connected && 4*CGAL::squared_distance(s -> point(), points.first) <= p;
    connected = connected && 4*CGAL::squared_distance(t -> point(), points.second) <= p;
    
    tries.push_back(4*CGAL::squared_distance(s -> point(), points.first));
    tries.push_back(4*CGAL::squared_distance(t -> point(), points.second));
    
    if(connected){
      std::cout << "y";
      new_queries.push_back(points);
    }
    else std::cout << "n";
  }
  
  std::cout << "\n";
}

void testcase(){
  Index n;
  int m;
  long p; fp >> n >> m >> p;
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay tr;
  tr.insert(points.begin(), points.end());
  
  EdgeV edges;
  edges.reserve(3*n); // there can be no more in a planar graph
  for (auto e = tr.finite_edges_begin(); e != tr.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, tr.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
            
  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<K::FT> tries;
  Index n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      tries.push_back(std::get<2>(*e));
      if (--n_components == 1) break;
    }
  }
  
  tries.push_back(p);
  tries.push_back(0);
  
  VPP queries(m); 
  for(int i = 0; i < m; ++i){
    int x, y; fp >> x >> y;
    int z, t; fp >> z >> t;
    queries[i] = {{x, y}, {z, t}};
  }
  
  VPP new_queries;
  true_queries(edges, p, queries, tr, new_queries, tries);
  
  std::sort(tries.begin(), tries.end());
  
  int L = 0;
  int R = tries.size();
  while(L < R){
    int mid = (L + R) / 2;
    if(!f(edges, tries[mid], queries, tr)) L = mid + 1;
    else R = mid;
  }
  
  std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(tries[L])) << "\n";
  
  L = 0;
  R = tries.size();
  while(L < R){
    int mid = (L + R) / 2;
    if(!f(edges, tries[mid], new_queries, tr)) L = mid + 1;
    else R = mid;
  }
  
  std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(tries[L])) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}