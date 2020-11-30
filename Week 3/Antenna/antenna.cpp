#include <CGAL/Exact_predicates_exact_constructions_kernel.h> 
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h> 
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <bits/stdc++.h>


using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K; 
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt Ks; 
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef CGAL::Min_circle_2_traits_2<Ks> Traits_S;
typedef CGAL::Min_circle_2<Traits_S> Min_circle_S;

double floor_to_double(const Ks::FT& x) {
  double a = std::floor(CGAL::to_double(x)); 
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return (long)a;
}

int main(int argc, const char *argv[]) {
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  vector<K::Point_2> P;
  cout << std::fixed << std::setprecision(0);
  
  int n;
  
  while(cin >> n && n){
    
    P.clear();
    
    for (int i = 0; i < n; ++i){
      long x, y; cin >> x >> y; 
      P.push_back(K::Point_2(x, y));
    }
    
    Min_circle mc(P.begin(), P.end(), true);
    Traits::Circle c = mc.circle();
    
    
    K::FT a = c.squared_radius();
    
    unsigned long L = 0;
    unsigned long R = 1UL << 50;
    
    while(L < R){
      unsigned long m = (L + R) / 2;
      K::FT square_m = K::FT(m) * K::FT(m);
      
      if (square_m < a) L = m + 1;
      else R = m;
    }
        
    cout << floor_to_double(L) << "\n";
    
  }


  return 0;
}