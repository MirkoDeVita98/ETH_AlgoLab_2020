#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>         Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Point                                        Point;
typedef Triangulation::Vertex_handle                                Vertex_handle;
typedef Triangulation::Finite_faces_iterator                        Face_iterator;


std::istream & fp = std::cin;


void from_del_to_graph(const Triangulation & t,graph & G, boost::disjoint_sets_with_storage<> & uf,const std::vector< std::pair<Point,int> > & pts,long r){
  int n = boost::num_vertices(G);
  
  for (auto it = t.finite_edges_begin(); it != t.finite_edges_end(); it++) {
    auto u = it->first->vertex((it->second + 1) % 3);
    auto v = it->first->vertex((it->second + 2) % 3);

    if (CGAL::compare_squared_distance(pts[u->info()].first, pts[v->info()].first, r*r) != CGAL::LARGER) {
        boost::add_edge(u->info(), v->info(), G);
        uf.union_set(u->info(), v->info());
    }
  }
  
  std::vector<int> last_visit(n, -1);
  std::vector< std::pair<int, int> > to_insert;
  for(int i = 0; i < n; ++i){
    std::queue<int> Q;
    Q.push(i);
    last_visit[i] = i;
    
    while(!Q.empty()){
      int v = Q.front();
      Q.pop();
      
      if (CGAL::compare_squared_distance(pts[v].first, pts[i].first, r*r) != CGAL::LARGER){
        if (i < v) to_insert.push_back({ i, v });
        graph::out_edge_iterator it, end;

        for (boost::tie(it, end) = boost::out_edges(v, G); it != end; it++) {
          int u = boost::target(*it, G);
          if(last_visit[u] < i){
            Q.push(u);
            last_visit[u] = i;
          }
        }
        
      }
      
    }
    
  }
  
  for (std::pair<int, int> & e : to_insert) boost::add_edge(e.first, e.second, G);
}

bool coloring(const graph & G){
  int n = boost::num_vertices(G);
  std::vector<int> color(n, -1);
  
  for(int i = 0; i < n; ++i){
    if(color[i] != -1) continue;
    
    std::queue<int> Q;
    Q.push(i);
    color[i] = 0;
    
    while(!Q.empty()){
      int v = Q.front();
      Q.pop();
      
      graph::out_edge_iterator it, end;

      for (boost::tie(it, end) = boost::out_edges(v, G); it != end; it++) {
        int u = boost::target(*it, G);
        if(color[u] == -1){
          color[u] = !color[v];
          Q.push(u);
        }
        
      }
    }
    
  }
  
  auto es = boost::edges(G);
  for (auto eit = es.first; eit != es.second; ++eit) 
    if (color[boost::source(*eit, G)] == color[boost::target(*eit, G)]) return false;
  
  return true;
}

void testcase(){
  int n, m; fp >> n >> m;
  long r; fp >> r;
  
  std::vector< std::pair<Point,int> > pts; 
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    fp >> x >> y; 
    pts.push_back(std::make_pair(Point(x,y),i));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  graph G(n);
  boost::disjoint_sets_with_storage<> uf(n);
  from_del_to_graph(t, G, uf,pts, r);
  
  bool is_colorable = coloring(G);
  
  for(int i = 0; i < m; ++i){
    int x, y; fp >> x >> y;
    Point a(x, y);
    fp >> x >> y;
    Point b(x, y);
    
    if(!is_colorable){
      std::cout << "n";
      continue;
    }
    
    if (CGAL::compare_squared_distance(a, b, r*r) != CGAL::LARGER) {
      std::cout << "y";
      continue;
    }
    
    auto nearest_a = t.nearest_vertex(a) -> point();
    auto nearest_b = t.nearest_vertex(b) -> point();
    auto n_a = t.nearest_vertex(a) -> info();
    auto n_b = t.nearest_vertex(b) -> info();
    
    bool connected = uf.find_set(n_a) == uf.find_set(n_b);
    connected = connected && (CGAL::compare_squared_distance(a, nearest_a, r*r) != CGAL::LARGER);
    connected = connected && (CGAL::compare_squared_distance(b, nearest_b, r*r) != CGAL::LARGER);

    std::cout << (connected ? "y" : "n");
  }
  
  std::cout << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  while(t--) testcase();
}