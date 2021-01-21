#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef Delaunay::Point                                   Point;
typedef std::tuple<int,int,long> Edge;
typedef std::vector<Edge> EdgeV;

std::istream & fp = std::cin;

int k_bones(const EdgeV & edges,const long & s, const std::vector< std::vector<long> > & bones){
  int n = bones.size();
  std::vector<int> bones_in_component(n, 0);
  
  int max_bones = 0;
  for(int i = 0; i < n; ++i){
    auto up = upper_bound(bones[i].begin(), bones[i].end(), s);
    int starting_bones = (up == bones[i].end()) ? bones[i].size() : up - bones[i].begin();
    max_bones = std::max(max_bones, bones_in_component[i] = starting_bones);
  }
  
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && get<2>(*e) <= s; ++e) {
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      int sum_of_bones = bones_in_component[c1] + bones_in_component[c2];
      uf.link(c1, c2);
      max_bones = std::max(max_bones, bones_in_component[uf.find_set(c1)] = sum_of_bones);
      if (--n_components == 1) break;
    }
  }
  
  return max_bones;
}

void testcase(){
  int n, m; fp >> n >> m;
  long s; fp >> s;
  int k; fp >> k;
  
  typedef std::pair<K::Point_2,int> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  std::vector< long > tries;
  std::vector< std::vector<long> > bones(n);
  for(int i = 0; i < m; ++i){
    int x, y;
    std::cin >> x >> y;
    Point bone(x, y);
    auto tree = t.nearest_vertex(bone);
    long dist = 4*CGAL::squared_distance(tree -> point(), bone);
    tries.push_back(dist);
    bones[tree -> info()].push_back(dist);
  }
  
  for(int i = 0; i < n; ++i) std::sort(bones[i].begin(), bones[i].end());
  
  EdgeV edges;
  edges.reserve(3*n); 
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
    tries.push_back(t.segment(e).squared_length());
  }
  sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  
  int L = 0;
  int R = tries.size() - 1;
  std::sort(tries.begin(), tries.end());
  
  while(L < R){
    int mid = (L + R) / 2;
    if(k_bones(edges, tries[mid], bones) < k) L = mid + 1;
    else R = mid;
  }
  
  std::cout << k_bones(edges, s, bones) << " " << tries[L] << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}






























