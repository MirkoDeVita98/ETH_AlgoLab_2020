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

std::istream & fp = std::cin;

void testcase(){
  Index n;
  int r; fp >> n >> r;
  K::FT rr = r;
  rr *= rr;
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  
  int max_size = 1;
  std::vector<int> sizes(n, 1);
  boost::disjoint_sets_with_storage<> uf(n);
  
  for(int i = n - 1; i >= 0; --i){
    auto v = t.insert(points[i].first);
    v -> info() = points[i].second;
    
    if(t.number_of_vertices() == 1) continue;
    
    Delaunay::Vertex_circulator c = t.incident_vertices(v); 
    do {
      if (t.is_infinite(c) || CGAL::squared_distance(c -> point(), v -> point()) >  rr) continue;
      Index c1 = uf.find_set(c -> info());
      Index c2 = uf.find_set(v -> info());
      if(c1 != c2){
        int num_planets = sizes[c1] + sizes[c2];
        uf.link(c1, c2);
        max_size = std::max(max_size, std::min(i, sizes[uf.find_set(c1)] = num_planets));
      }
      
    } while (++c != t.incident_vertices(v));
    
  }
  
  std::cout << max_size << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}