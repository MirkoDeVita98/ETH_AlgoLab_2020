#include <bits/stdc++.h>

using namespace std;

#define FAIL -2

#define memo(i, j)((*_memo)[n*(j) + (i)])

vector< int > *_memo;

/*int f(int m, int d, const vector<int> &match, int n){
  if(m == 0) return 0;
  if(d >= n) return FAIL;
  
  if(memo(d, m) != -1) return memo(d, m);
  
  int temp = FAIL;
  if(match[d] >= 0) temp = f(m - 1, d + match[d], match , n);
  return memo(d, m) = max(f(m, d + 1, match, n), (temp == FAIL ? temp : temp + match[d]));
  
}*/

int f(int m, int n, const vector<int> &match){
  
  vector< vector<int> > tab(n + 1, vector<int> (m + 1));
  
  for(int i = 0; i <= n; ++i) tab[i][0] = 0;
  for(int j = 1; j <= m; ++j) tab[n][j] = FAIL;
  
  
  for(int j = 1; j <= m; ++j){
    for(int i = n - 1; i >= 0; --i){
      int take = FAIL;
      if(match[i] >= 0){
        take = tab[i + match[i]][j - 1];
        if(take != FAIL) take += match[i];
      }
      
      int pass = tab[i + 1][j];
      
      tab[i][j] = max(pass, take);
      
    }
  }
  
  return tab[0][m];
}


void testcase(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  int n, k, m; 
  cin >> n >> m >> k;
  
  vector<int> S(n + 1, 0);
  vector< int > match(n, -1);
  
  for (int i = 1; i <= n; i++) {
    int temp; cin >> temp;
    S[i] = S[i-1] + temp;
  }
  
  int i = 0;
  int j = 1;
  int count = 0;
  while(i <= n - 1 && j <= n){
    int sum = S[j] - S[i];
    if(sum == k){
      count++;
      match[i] = j - i;
      i++;
    }
    else if(sum > k) i++;
    else j++;
  }
  
  if(count < m){
    cout << "fail\n";
    return;
  }

  _memo = new vector< int >(n * (m+1), -1);
 
  int res = f(m, n,match);
  if(res == FAIL) cout << "fail\n";
  else cout << res << "\n";
  
  
  delete _memo;
  
}

int main(int argc, const char * argv[]){
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}