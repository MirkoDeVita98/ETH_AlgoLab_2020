#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/constructions_d.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K; 
typedef CGAL::Delaunay_triangulation_2<K> Triangulation; 
typedef Triangulation::Finite_faces_iterator Face_iterator;

std::istream & fp = std::cin;

template <typename K> long floor_to_double(const K& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long) a;
}

template <typename K> long ceil_to_double(const K& x) {
    return -floor_to_double(-x);
}

int main(int argc, const char *argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int n;
  while(fp >> n && n){
    std::vector<K::Point_2> pts;
    pts.reserve(n);
    
    for(int i = 0; i < n; ++i){
      int x, y;
      fp >> x >> y;
      pts.push_back(K::Point_2(x, y));
    }
    
    Triangulation t; 
    t.insert(pts.begin(), pts.end());
    
    int m; fp >> m;
    
    for(int i = 0; i < m; ++i){
      int x, y;
      fp >> x >> y;
      K::Point_2 p(x, y);
      Triangulation::Vertex_handle v = t.nearest_vertex(p);
      
      std::cout << ceil_to_double(CGAL::squared_distance(p, v -> point())) << "\n";
      
    }
    
  }
  
  return 0;
  
}