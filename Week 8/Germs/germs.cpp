#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <bits/stdc++.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt KS;

std::istream & fp = std::cin;

long ceil_to_int(KS::FT x) {
  double a = std::floor(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return (long) a;
}

void testcase(int n){
  
  int l,b,r,t; fp >> l >> b >> r >> t;
  
  std::vector<K::Point_2> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.push_back(K::Point_2(x, y));
  }
  Delaunay tr;
  tr.insert(points.begin(), points.end());
  
  std::vector<K::FT> distances;
  
  for (auto it = tr.finite_vertices_begin(); it !=  tr.finite_vertices_end(); it++) {
    auto dist_x = std::min(CGAL::abs(l - it -> point().x()), CGAL::abs(r - it -> point().x()));
    auto dist_y = std::min(CGAL::abs(b - it -> point().y()), CGAL::abs(t - it -> point().y()));
    
    auto d = 2 * CGAL::min(dist_x, dist_y);
    d *= d;
    
    if(n > 1){
      auto neigh = CGAL::nearest_neighbor(tr, it);
      auto neigh_d = CGAL::squared_distance(neigh -> point(), it -> point());
      
      d = CGAL::min(d, neigh_d);
    }
    
    distances.push_back(d);
    
  }
  
  std::sort(distances.begin(), distances.end());
  
  KS::FT first = KS::FT(distances[0]);
  KS::FT half = KS::FT(distances[n / 2]);
  KS::FT last = KS::FT(distances[n - 1]);
  
  long first_dead = ceil_to_int(CGAL::sqrt((CGAL::sqrt(first) - 1)/2));
  long half_dead =  ceil_to_int(CGAL::sqrt((CGAL::sqrt(half) - 1)/2));
  long total_dead = ceil_to_int(CGAL::sqrt((CGAL::sqrt(last) - 1)/2));
  
  std::cout << first_dead << " " << half_dead << " " << total_dead << "\n";
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int n;
  
  while(fp >> n && n) testcase(n);
  
  return 0;
}