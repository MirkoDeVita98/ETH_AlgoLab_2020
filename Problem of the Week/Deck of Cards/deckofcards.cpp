#include <bits/stdc++.h>

using namespace std;

/*void testcase(){
  int n; cin >> n;
  int k; cin >> k;
  
  vector<int> v(n);
  vector<int> ps(n);

  cin >> v[0];
  ps[0] = v[0];
  for(int i = 1; i < n; ++i){
    cin >> v[i];
    ps[i] = v[i] + ps[i - 1];
  }
  

  vector<int>::iterator i = ps.begin();
  int best =  abs(k - (v[0]));
  int best_j = 0;
  for(int j = 0; j < n; ++j){
    auto lb = lower_bound(ps.begin(), ps.begin() + j, ps[j] - k);
    auto ub = upper_bound(ps.begin(), ps.begin() + j, ps[j] - k);
    
    int a = abs(k - (ps[j] - *lb));
    int b = abs(k - (ps[j] - *ub));
    int c = abs(k - ps[j]);
    
    int m = min({a, b , c, best});
    
    if(m != best){
      if(b == m){
        i = ub + 1;
        best = b;
      }
      else if(a == m){
        i = lb + 1;
        best = a;
      }
      else{
        i = ps.begin();
        best = c;
      }
      best_j = j;
    }
    
    if(best == 0) break;
  }
  
  cout << (i - ps.begin()) << " " << best_j << "\n";
  
}*/

void testcase(){
  int n; cin >> n;
  int k; cin >> k;
  
  vector<int> v(n);
  vector<int> ps(n);
  
  for(int i = 0; i < n; ++i){
    cin >> v[i];
  }

  pair<int, int> best = {0, 0};
  int best_sum = v[0];
  int sum = v[0];
  int j = 0;
  int i = 0;
  while(i < n && j < n){
    
    if(sum < k){
      sum += v[++j];
    }
    else if(sum == k) break;
    else{
      sum -= v[i++];
      if(i > j){
        j = i;
        sum = v[i];
      } 
    }
    
    if(abs(k - sum) < abs(k - best_sum)){
      best = {i, j};
      best_sum = sum;
    }
  }

  cout << best.first << " " << best.second << "\n";
  
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) testcase();
  
  return 0;
}