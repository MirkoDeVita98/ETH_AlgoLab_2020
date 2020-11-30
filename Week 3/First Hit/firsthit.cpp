#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;


long floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x)); 
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return (long)a;
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int n; 
  cin >> n;
  
  while(n){
    long x, y, a , b; cin >> x >> y >> a >> b;
    K::Ray_2 ray((K::Point_2){x, y},(K::Point_2){a, b});
    
    
    vector<K::Segment_2> walls;
    
    
    for(int i = 0; i < n; ++i){
      long r, s, t, u; cin >> r >> s >> t >> u;
      K::Segment_2 wall((K::Point_2){r, s},(K::Point_2){t, u});
      walls.push_back(wall);
    }
    
    random_shuffle(walls.begin(), walls.end());
    
    bool intersect = false;
    K::Segment_2 seg;
    
    for(int i = 0; i < n; ++i){
      
      if(!intersect){
        
        auto isect = CGAL::intersection(ray, walls[i]);
        
        if(isect){
          if(const K::Point_2* point = boost::get<K::Point_2>(&*isect)) {
            seg = {ray.start(), *point};
            intersect = true;
          }
          else if(const K::Segment_2* segment = boost::get<K::Segment_2>(&*isect)) {
          //K::FT d1 = squared_distance(walls[i].start(), p);
          //K::FT d2 = squared_distance(walls[i].end(), p);
          
            seg = {ray.start(), segment -> start()};
          
          /*if(d1 <= d2){
            result = walls[i].start();
            seg = {p, walls[i].start()};
          }
          else{
            result = walls[i].end();
            seg = {p, walls[i].end()};
          }*/ 
            intersect = true;
          }
        }
        
      }
      else{
        
        auto isect = CGAL::intersection(seg, walls[i]);
        
        if(isect){
          if(const K::Point_2* point = boost::get<K::Point_2>(&*isect)) {
          
            seg = {ray.start(), *point};
          
          }
          else if(const K::Segment_2* segment = boost::get<K::Segment_2>(&*isect)) {
          //K::FT d1 = squared_distance(walls[i].start(), p);
          //K::FT d2 = squared_distance(walls[i].end(), p);
          
            seg = {ray.start(), segment -> start()};
          
          /*if(d1 <= d2){
            result = walls[i].start();
            seg = {p, walls[i].start()};
          }
          else{
            result = walls[i].end();
            seg = {p, walls[i].end()};
          }*/
          }
        }
      
      }
        
        
    }
      
    if(!intersect) cout << "no\n";
    else{
      cout << floor_to_double(seg.end().x()) << " " << floor_to_double(seg.end().y()) << "\n";
    }
    cin >> n;
      
  }
  
  return 0; 
}
  
  