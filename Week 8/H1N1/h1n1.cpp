//two approaches: bgl and only CGAL with distances stored in face -> info()

#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K; 
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K> Fb; 
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; 
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Face_handle Face_handle;

typedef K::Point_2 P;

std::istream & fp = std::cin;

void testcase(int n){
  std::vector<P> pts; 
  pts.reserve(n);
  for(int i = 0; i < n; ++i) {
    int x, y;
    fp >> x >> y; pts.push_back(P(x, y));
  }
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  std::priority_queue< std::pair<K::FT, Face_handle> > pq;
  
  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
    f -> info() = t.is_infinite(f) ? std::numeric_limits<long>::max() : 0;
    pq.push({f -> info(), f});
  }
  
  while(!pq.empty()){
    Face_handle u = pq.top().second;
    K::FT w = pq.top().first;
    pq.pop();
    
    if(w < u -> info()) continue;
    
    for(int i = 0; i < 3; ++i){
      Face_handle v = u -> neighbor(i);
      K::FT link = t.segment(u, i).squared_length();
      K::FT new_w = CGAL::min(link, u -> info());
      if(new_w > v -> info()){
        v -> info() = new_w;
        pq.push({new_w, v});
      }
    }
  }
  
  int m; fp >> m;
  
  while(m--){
    int x, y; fp >> x >> y;
    long d; fp >> d;
    
    P p(x, y);
    K::FT dist = CGAL::squared_distance(t.nearest_vertex(p)->point(), p);
    
    if(dist < d){
      std::cout << "n";
      continue;
    } 
    Face_handle start = t.locate(p);
    if(start -> info() >= 4*d) std::cout << "y";
    else std::cout << "n";
  }
  
  std::cout << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int n;
  while(fp >> n && n) testcase(n);
  return 0;
}

/*#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/graph/adjacency_list.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K; 
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long,K> Fb; 
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; 
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, K::FT>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator oe_it;

std::istream & fp = std::cin;

void dijkstra(weighted_graph G, long inf_face, std::vector<K::FT> & distances) { 

  std::vector<bool> visited(boost::num_vertices(G), false);
  
  long src = inf_face;
  distances[src] = std::numeric_limits<long>::max();
  
  std::priority_queue< std::pair<K::FT, long> > min_heap;
  
  min_heap.push({distances[src], src});
  
  weight_map weights = boost::get(boost::edge_weight, G);
  
  while(!min_heap.empty()){
    
    long v = min_heap.top().second;
    min_heap.pop();
    
    if(!visited[v]){
      visited[v] = true;
      
      oe_it it, end;
      
      for(boost::tie(it, end) = boost::out_edges(v, G); it != end; ++it){
        
        long neighbor = boost::target(*it, G);
        
        if( !visited[neighbor] && distances[neighbor] < CGAL::min(distances[v], weights[*it])){
          distances[neighbor]  = CGAL::min(distances[v], weights[*it]);
          min_heap.push({distances[neighbor], neighbor});
        }
        
      }
    }
    
  }
  
  
} 

void testcase(int n){
  
  std::vector<K::Point_2> pts; 
  pts.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y; pts.push_back(K::Point_2(x, y));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  long cnt = 0;
  for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
    f -> info() = cnt++;
  }
  
  weighted_graph G(cnt + 1);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  long inf_face = cnt + 1;
  
  for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
    
    for (int i = 0; i < 3; ++i){ 
      Triangulation::Face_handle neighbour = f->neighbor(i);
      Triangulation::Edge e = std::make_pair(f,i);
      K::FT length = t.segment(e).squared_length();
      
      //auto neigh_v1 = f->vertex((i + 1) % 3)->point();
      //auto neigh_v2 = f->vertex((i + 2) % 3)->point();
                
      //K::Segment_2 length(neigh_v1, neigh_v2);
      
      if (t.is_infinite(neighbour)) {
        edge_desc ed = boost::add_edge(f -> info(), inf_face, G).first;
        weights[ed] = length;
      }
      else if (f -> info() < neighbour -> info()){
        edge_desc ed = boost::add_edge(f -> info(), neighbour -> info(), G).first;
        weights[ed] = length;
      }
    }
      
  }
  
  std::vector<K::FT> distances(boost::num_vertices(G), 0);
  dijkstra(G, inf_face, distances);
  
  int m; fp >> m;
  
  while(m--){
    int x, y; fp >> x >> y;
    long d; fp >> d;
    
    K::Point_2 p(x, y);
    
    if (CGAL::squared_distance(t.nearest_vertex(p)->point(),p) < d){ 
      std::cout << "n";            
      continue;
    } 
    
    Triangulation::Face_handle start = t.locate(p);
    if (t.is_infinite(start)){
      std::cout << "y";
      continue;
    }
    else if(4 * d <= distances[start -> info()]) std::cout << "y";
    else std::cout << "n";

    
  }
  
  std::cout << "\n";
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int n; 
  while(fp >> n && n) testcase(n);
}*/