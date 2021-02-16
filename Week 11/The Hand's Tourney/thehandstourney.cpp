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
typedef Delaunay::Vertex_handle Vertex_handle;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

std::istream & fp = std::cin;

typedef std::vector<int> VI;

Index n, k;

int DFS(const Delaunay & t,const K::FT & s){
  
  std::vector<bool> visited(n, false);
  VI sizes;
  
  for(auto u = t.finite_vertices_begin(); u != t.finite_vertices_end(); ++u){
    if(visited[u -> info()]) continue;
    std::stack< Vertex_handle> S;
    S.push(u);
    
    int size_c = 1;
    visited[u -> info()] = true;
    
    do{
      Vertex_handle v = S.top();
      S.pop();

      Delaunay::Vertex_circulator c = t.incident_vertices(v); 
      do {
        if (t.is_infinite(c)) continue;
        if(!visited[c -> info()] && CGAL::squared_distance(v -> point(), c -> point()) < s){
          visited[c -> info()] = true;
          S.push(c);
          size_c += 1;
        } 
      } while (++c != t.incident_vertices(v));
    }while(!S.empty());
    
    sizes.push_back(size_c);
  }
  
  int s1 = 0, s2 = 0, s3 = 0, f = 0;
  
  for(int component : sizes){
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
  int f0; 
  long s0;
  fp >> n >> k >> f0 >> s0;
  
  typedef std::pair<K::Point_2,Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());

  EdgeV edges;
  edges.reserve(3*n);
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second+1)%3)->info();
    Index i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
      [](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
            });

  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  std::vector<K::FT> tries;
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    Index c1 = uf.find_set(std::get<0>(*e));
    Index c2 = uf.find_set(std::get<1>(*e));
    if (c1 != c2) {
      uf.link(c1, c2);
      tries.push_back(std::get<2>(*e));
      if (--n_components == 1) break;
    }
  }
  
  std::sort(tries.begin(), tries.end());
  
  int L = 0;
  int R = tries.size();
  
  while(L < R){
    int mid = (L + R) / 2;
    if(DFS(t, tries[mid]) >= f0) L = mid + 1;
    else R = mid;
  }
  
  std::cout << std::fixed << std::setprecision(0) << ceil(CGAL::to_double(tries[L - 1])) << " " << DFS(t, s0) << std::endl;
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}