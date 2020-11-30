#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

bool compareY(const tuple<K::Ray_2, int , K::FT> &b1, const tuple<K::Ray_2, int, K::FT> &b2) { 
    return (get<0>(b1).source().y() >= get<0>(b2).source().y()); 
} 

void testcase(){
  int n; cin >> n;
  
  vector< tuple<K::Ray_2, int, K::FT> > bikers(n);
  
  for(int i = 0; i < n; ++i){
    long y0, x1, y1; cin >> y0 >> x1 >> y1;
    K::Point_2 p(0,y0), q(x1,y1); 
    K::Ray_2 ray(p,q);
    K::FT slope = (K::FT(y1-y0))/(K::FT(x1));
    bikers[i] = make_tuple(ray, i, slope);
  }
  
  sort(bikers.begin(), bikers.end(), compareY);
  
  stack< tuple<K::Ray_2, int, K::FT> > s;
  s.push(bikers[0]);
  
  for(int i = 1; i < n; ++i){
    
    if(get<2>(bikers[i]) <= get<2>(s.top())){
      s.push(bikers[i]);
      continue;
    }
    
    while(!s.empty() 
    && CGAL::abs(get<2>(bikers[i])) <= CGAL::abs(get<2>(s.top()))
    && CGAL::do_intersect(get<0>(bikers[i]), get<0>(s.top()))) s.pop();
    
    if(s.empty() || get<2>(bikers[i]) <= get<2>(s.top())){
        s.push(bikers[i]);
    }
    
  }
  
  vector<int> res;
  while(!s.empty()){
    res.push_back(get<1>(s.top()));
    s.pop();
  }
  
  sort(res.begin(), res.end());
  
  for(int b : res){
    cout << b << " ";
  }
  
  cout << "\n";
  
}

int main(int argc, const char * argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}
