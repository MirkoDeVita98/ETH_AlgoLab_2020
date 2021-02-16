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
typedef Delaunay::Vertex_handle Vertex_handle;
typedef std::pair<K::Point_2,Index> IPoint;

std::istream & fp = std::cin;

#define BLUE 0
#define RED 1
#define GREY -1

bool interference(const Delaunay & t,const K::FT & rr) {
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
    if (t.segment(*e).squared_length() <= rr) return true; 
  return false;
}

bool uf_and_color(Delaunay & t, boost::disjoint_sets_with_storage<> & uf,const K::FT & rr){
  int n = t.number_of_vertices();
  std::vector<int> colors(n, GREY);
  
  std::vector<IPoint> pB;
  pB.reserve(n);
  std::vector<IPoint> pR;
  pR.reserve(n);
  
  for(auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v){
    
    if(colors[v -> info()] == GREY){
      colors[v -> info()] = BLUE;
      std::stack<Vertex_handle> st;
      st.push(v);
      do{
        Vertex_handle u = st.top();
        st.pop();
        
        Delaunay::Vertex_circulator c = t.incident_vertices(u); 
        do{
          if(!t.is_infinite(c) && colors[c -> info()] == GREY && CGAL::squared_distance(c -> point(), u -> point()) <= rr){
            uf.link(c -> info(), u -> info());
            colors[c -> info()] = 1 - colors[u -> info()];
            st.push(c);
          }
        }while(++c != t.incident_vertices(u));
      }while(!st.empty());
    }
    
    if(colors[v -> info()] == BLUE) pB.emplace_back(v -> point(), v -> info());
    else pR.emplace_back(v -> point(), v -> info());
    
  }
  
  Delaunay tB, tR;
  tB.insert(pB.begin(), pB.end());
  tR.insert(pR.begin(), pR.end());
  
  return !interference(tB, rr) && !interference(tR, rr);
}

void testcase(){
  Index n;
  int m;
  fp >> n >> m;
  int r; fp >> r;
  K::FT rr = K::FT(r)*K::FT(r);
  
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }
  Delaunay t;
  t.insert(points.begin(), points.end());
  
  boost::disjoint_sets_with_storage<> uf(n);
  bool success = uf_and_color(t, uf, rr);
  
  while(m--){
    int x, y; fp >> x >> y;
    K::Point_2 a(x, y);
    fp >> x >> y;
    K::Point_2 b(x, y);
    
    if(!success){
      std::cout << "n";
      continue;
    }
    
    if(CGAL::squared_distance(a, b) <= rr){
      std::cout << "y";
      continue;
    }
    
    auto na = t.nearest_vertex(a);
    auto nb = t.nearest_vertex(b);
    
    bool connected = uf.find_set(na -> info()) == uf.find_set(nb -> info());
    connected = connected && CGAL::squared_distance(na -> point(), a) <= rr;
    connected = connected && CGAL::squared_distance(nb -> point(), b) <= rr;
    
    if(connected) std::cout << "y";
    else std::cout << "n";
  }
  
  std::cout << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}