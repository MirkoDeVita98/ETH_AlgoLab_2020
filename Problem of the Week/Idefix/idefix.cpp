#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/squared_distance_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K>    Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Point                                        Point;
typedef Triangulation::Vertex_handle                                Vertex_handle;
typedef Triangulation::Finite_faces_iterator                        Face_iterator;

typedef std::tuple<K::FT, int, int> Edge;

std::istream & fp= std::cin;

int k_bones(const Triangulation & t,const long & s, std::priority_queue<Edge> pq, int n, const std::vector<std::vector<long>> & bones_to_check){

  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<int> bones(n, 0);
  int max_bones = 0;
  for(int i = 0; i < n; ++i){
    
    auto pointer = upper_bound(bones_to_check[i].begin(), bones_to_check[i].end(), s/4);
    int new_bones = (pointer==bones_to_check[i].end()) ? bones_to_check[i].size() : pointer-bones_to_check[i].begin();
    
    max_bones = std::max(max_bones, bones[i] = new_bones);
  }
  
  while(!pq.empty()){
    Edge e = pq.top();
    pq.pop();
    
    K::FT d = std::get<0>(e);
    int u = std::get<1>(e);
    int v = std::get<2>(e);
    
    if(s >= d){
      if(uf.find_set(u) != uf.find_set(v)){
        int num_bones_u = bones[uf.find_set(u)];
        int num_bones_v = bones[uf.find_set(v)];
        uf.union_set(u, v);
        max_bones = std::max(max_bones, 
                        bones[uf.find_set(u)] = num_bones_u + num_bones_v
                      );
      }
    }
  
  }
  
  return max_bones;
}

void testcase(){
  int n, m; fp >> n >> m;
  long s; fp >> s;
  int k; fp >> k;
  
  std::vector<std::pair<Point,unsigned>> pts; 
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    fp >> x >> y; 
    pts.push_back(std::make_pair(Point(x,y),i));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  graph G(n);
  
  std::vector<std::vector<long>> bones_to_check(n);
  std::vector<long> tries;
  
  for(int i = 0; i < m; ++i){
    int x, y;
    fp >> x >> y;
    Point p(x, y);
    Triangulation::Vertex_handle v = t.nearest_vertex(p);
    K::FT d = CGAL::squared_distance(v -> point(), p);
    tries.push_back(4 * d);
    bones_to_check[v -> info()].push_back(d); 
  }
  
   for(int i = 0; i < n; i++) sort(bones_to_check[i].begin(), bones_to_check[i].end());
   
  std::priority_queue<Edge> pq;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int u = e->first->vertex((e->second+1)%3)->info();
    int v = e->first->vertex((e->second+2)%3)->info();
    
    auto d = t.segment(e).squared_length();
    tries.push_back(d);
    pq.push(std::make_tuple(d, u, v));
  }
  
  std::sort(tries.begin(), tries.end()); 
  
  std::cout << k_bones(t, s, pq, n, bones_to_check) << " ";
  
  int left = 0;
  int right = tries.size() - 1;
  
  while (left < right) {
    int mid = (left + right)/2;
    
    if(k_bones(t, tries[mid], pq, n, bones_to_check) < k) left = mid + 1;
    else right = mid;
    
  }
  
  std::cout << tries[left] << std::endl;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}

/*#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/squared_distance_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned, K>    Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Point                                        Point;
typedef Triangulation::Vertex_handle                                Vertex_handle;
typedef Triangulation::Finite_faces_iterator                        Face_iterator;

typedef std::tuple<K::FT, int, int> Edge;

std::istream & fp = std::cin;

long floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x)); 
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return (long)a;
}

int union_find(const Triangulation & t, int n, int m,const K::FT & s,const std::vector<Point> & bones_locations){
  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<int> bones(n, 0);
  
  for(int i = 0; i < m; ++i){
    Point p = bones_locations[i];
    Triangulation::Vertex_handle v = t.nearest_vertex(p);
    K::FT d = 4 * CGAL::squared_distance(v -> point(), p);
    if(d <= s) bones[v -> info()] += 1;
  }
  
  
  int max_bones = 0;  
  
  for(int i = 0; i < m; ++i) max_bones = std::max(max_bones, bones[i]);
   
  
  std::priority_queue<Edge> pq;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int u = e->first->vertex((e->second+1)%3)->info();
    int v = e->first->vertex((e->second+2)%3)->info();
    
    auto d = t.segment(e).squared_length();
    
    pq.push(std::make_tuple(d, u, v));
    
  }
  
  
  while(!pq.empty()){
    Edge e = pq.top();
    pq.pop();
    
    K::FT d = std::get<0>(e);
    int u = std::get<1>(e);
    int v = std::get<2>(e);
    
    if(s >= d){
      if(uf.find_set(u) != uf.find_set(v)){
        int num_bones_u = bones[uf.find_set(u)];
        int num_bones_v = bones[uf.find_set(v)];
        uf.union_set(u, v);
        max_bones = std::max(max_bones, 
                        bones[uf.find_set(u)] = num_bones_u + num_bones_v
                      );
      }
    }
  
  }
  
  return max_bones;
}

long left_most_bin(const Triangulation & t, int n, int m, int k, const std::vector<Point> & bones_locations){
  long L = 0;
  long R = 1L << 51;
  
  while (L < R) {
    long mid = (L + R)/2;
    
    if (union_find(t, n, m, mid, bones_locations) < k) {
        L = mid + 1;
    } else {
        R = mid;
    }
  }

  return L;
}

void testcase(){
  int n, m; fp >> n >> m;
  K::FT s; fp >> s;
  int k; fp >> k;
  
  std::vector<std::pair<Point,unsigned>> pts; 
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    fp >> x >> y; 
    pts.push_back(std::make_pair(Point(x,y),i));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  std::vector<Point> bones_locations;
  for(int i = 0; i < m; ++i){
    int x, y; fp >> x >> y;
    Point p(x, y);
    bones_locations.push_back(p);
  }
  
  std::cout << union_find(t, n, m, s, bones_locations) << " " << left_most_bin(t, n, m, k, bones_locations) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  while(t--) testcase();
}*/






























