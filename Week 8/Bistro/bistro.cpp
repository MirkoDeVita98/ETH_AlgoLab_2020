#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;

std::istream & fp = std::cin;

void testcase(int n){
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  int m; fp >> m;
  while(m--){
    int x, y; fp >> x >> y;
    K::Point_2 p(x, y);
    Vertex_handle v = t.nearest_vertex(p);
    std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(CGAL::squared_distance(v -> point(), p))) << "\n";
  }
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int n;
  while(fp >> n && n) testcase(n);
  return 0;
}