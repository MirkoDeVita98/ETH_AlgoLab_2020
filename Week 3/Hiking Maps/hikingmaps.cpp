#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

using namespace std;
    
int membership(K::Point_2 p1, K::Point_2 p2, const vector<K::Point_2> &t){

  if(CGAL::orientation(t[0], t[1], p1) == - CGAL::orientation(t[0], t[1], t[2])) return 0;
  if(CGAL::orientation(t[2], t[3], p1) == - CGAL::orientation(t[2], t[3], t[0])) return 0;
  if(CGAL::orientation(t[4], t[5], p1) == - CGAL::orientation(t[4], t[5], t[2])) return 0;
  if(CGAL::orientation(t[0], t[1], p2) == - CGAL::orientation(t[0], t[1], t[2])) return 0;
  if(CGAL::orientation(t[2], t[3], p2) == - CGAL::orientation(t[2], t[3], t[0])) return 0;
  if(CGAL::orientation(t[4], t[5], p2) == - CGAL::orientation(t[4], t[5], t[2])) return 0;

  return 1;

}

int cost(const vector< vector<int> > &adj, int m, int n){
  
  vector<int> temp(m - 1, 0);
  int r = 0;
  int l = 0;
  int min = n;
  bool found = false;
  while(true){
    
    assert(r < n && l < n && l <= r);
    
    if(!found && r < n){
      found = true;
      for(int i = 0; i < m - 1; ++i){
        temp[i] += adj[i][r];
        if(temp[i] == 0) found = false;
      }
      r++;
    }
    else if(l < n){
      int k = r - l;
      if(k < min) min = k;
      
      for(int i = 0; i < m - 1; ++i){
        temp[i] -= adj[i][l];
        if(temp[i] == 0) found = false;
      }
      l++;
      if(!found && r == n) break;
    }
    
    
  }
  
  return min;
  
}

void testcase(){
  int m, n; cin >> m >> n;
  
  vector<K::Point_2> p(m);
  
  vector< vector<K::Point_2> > t(n);
  
  for(int i = 0; i < m; ++i){
    int x, y; cin >> x >> y;
    p[i] = {x, y};
  }
  
  for(int i = 0; i < n; ++i){
    
    int x, y; 
    
    for(int j = 1; j <= 6; ++j){
      cin >> x >> y;
      t[i].push_back({x, y});
    }
  }
  
  
  vector< vector<int> > adj(m - 1, vector<int>(n, 0) );
  
  for(int i = 1; i < m; ++i){
    for(int j = 0; j < n; ++j) adj[i - 1][j] = membership(p[i - 1], p[i], t[j]);
  }
  
  cout << cost(adj, m, n) << "\n";
  
}

int main(int argc, const char * argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int c; cin >> c;
  
  while(c--) testcase();
  
  return 0;
}