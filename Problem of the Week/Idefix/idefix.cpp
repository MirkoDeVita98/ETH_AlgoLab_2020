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
typedef Delaunay::Vertex_handle Vertex_handle;
typedef std::tuple<int,int,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::istream & fp = std::cin;

int k_bones(const EdgeV & edges, const long & s, const std::vector< std::vector<long> > & bones){
  
  int n = bones.size();
  std::vector<int> comp(n, 0);
  int max_bones = 0;
  
  for(int i = 0; i < n; ++i){
    auto point = std::upper_bound(bones[i].begin(), bones[i].end(), s);
    int num_bones = point == bones[i].end() ? bones[i].size() : point - bones[i].begin();
    max_bones = std::max(max_bones, comp[i] = num_bones);
  }
  
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;
  
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end() && std::get<2>(*e) <= s; ++e) {
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      int num_bones = comp[c1] + comp[c2];
      uf.link(c1, c2);
      max_bones = std::max(max_bones, comp[uf.find_set(std::get<0>(*e))] = num_bones);
      if (--n_components == 1) break;
    }
  }
  
  return max_bones;
  
}

void testcase(){
  int n, m, k; fp >> n >> m;
  long s; fp >> s >> k;
  
  typedef std::pair<K::Point_2,int> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    fp >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  
  Delaunay t;
  t.insert(points.begin(), points.end());

  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });
  
  std::vector< long > tries;
  boost::disjoint_sets_with_storage<> uf(n);
  int n_components = n;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    int c1 = uf.find_set(std::get<0>(*e));
    int c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      tries.push_back(std::get<2>(*e));
      uf.link(c1, c2);
      if (--n_components == 1) break;
    }
  }
  
  std::vector< std::vector<long> > bones(n);
  for(int i = 0; i < m; ++i){
    int x, y; fp >> x >> y;
    K::Point_2 p(x, y);
    Vertex_handle v = t.nearest_vertex(p);
    K::FT dist = 4*CGAL::squared_distance(v -> point(), p);
    bones[v -> info()].push_back(dist);
    tries.push_back(dist);
  }
  
  for(int i = 0; i < n; ++i) std::sort(bones[i].begin(), bones[i].end());
  std::sort(tries.begin(), tries.end());
  
  int L = 0;
  int R = tries.size();
  
  while(L < R){
    int mid = (L + R)/2;
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






























