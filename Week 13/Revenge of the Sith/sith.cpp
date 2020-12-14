///1
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

std::istream & fp = std::cin;

void testcase(){
  int n; fp >> n;
  long r; fp >> r;
  
  std::vector<K::Point_2> planets;
  planets.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    planets.push_back(K::Point_2(x, y));
  }

  
  Triangulation tr;
  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<int> set_sizes(n, 1);

  int max_cc_size = 1;
  for (int i = n - 1; i >= 0; i--) {
    K::Point_2 & p = planets[i];
    auto new_v = tr.insert(p);
    new_v->info() = i;

    if (tr.number_of_vertices() <= 1) continue;

    Triangulation::Vertex_circulator it, start;
    it = start = new_v->incident_vertices();
    do {
      if (!tr.is_infinite(it) && CGAL::compare_squared_distance(new_v->point(), it->point(), r*r) != CGAL::LARGER) {

        if (uf.find_set(new_v->info()) == uf.find_set(it->info())) continue;

        int u_size = set_sizes[uf.find_set(new_v->info())];
        int v_size = set_sizes[uf.find_set(it->info())];
        uf.union_set(new_v->info(), it->info());

        int new_size = u_size + v_size;

        set_sizes[uf.find_set(new_v->info())] = new_size;
        max_cc_size = std::max(max_cc_size, std::min(i, new_size));
      }
    } while (++it != start);
  }

  std::cout << max_cc_size << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}