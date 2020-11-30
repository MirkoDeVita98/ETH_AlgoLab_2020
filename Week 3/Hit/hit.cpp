#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int n; 
  cin >> n;
  while(n){
    long x, y, a , b; cin >> x >> y >> a >> b;
    
    K::Point_2 p(x,y), q(a,b); 
    K::Ray_2 ray(p,q);

    bool intersect = false;
  
    for(int i = 0; i < n; ++i){
      long r, s, t, u; cin >> r >> s >> t >> u;
      if(!intersect){
        K::Point_2 m(r,s), z(t,u); 
        K::Segment_2 wall(m, z);
        if(CGAL::do_intersect(ray, wall)) intersect = true;
      }
      
    }
  
    if(!intersect) cout << "no\n";
    else cout << "yes\n";
    cin >> n;
  }
  
  return 0;
}