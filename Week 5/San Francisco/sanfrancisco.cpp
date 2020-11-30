#include <bits/stdc++.h>

using namespace std;

#define IMPOSSIBLE -2

#define memo(i, j)((*_memo)[i][j])

vector< vector<long> > *_memo;

/*int f(const vector< vector< pair<int, int> > > &board, int i, long s, long x, int k){
  if(s >= x) return 0;
  if(k == 0) return IMPOSSIBLE;
  
  //if(memo(i, k) != -1) return memo(i, k);
  
  if(board[i].empty()){
    return f(board, 0, s, x, k);
  }
  
  int min = numeric_limits<int>::max();
  for(pair<int, int> ii : board[i]){
    int v = ii.first;
    int p = ii.second;
    
    int temp = f(board, v, s + p, x, k - 1);
    if(temp != IMPOSSIBLE && temp < min) min = temp;
  }
  
  if(min == numeric_limits<int>::max()) memo(i, k) = IMPOSSIBLE;
  else memo(i, k) = 1 + min;
  
  return min == numeric_limits<int>::max() ? IMPOSSIBLE : 1 + min;
  
}*/

long f(const vector< vector< pair<int, int> > > &board, int i, int k){
  if(k == 0) return 0;
  
  if(memo(i, k) != -1) return memo(i, k);
  
  if(board[i].empty()) return f(board, 0, k);
  
  long max = 0;
  for(pair<int, int> ii : board[i]){
    int v = ii.first;
    int p = ii.second;
    
    long temp = p + f(board, v, k - 1);
    if(temp > max) max = temp;
  }
  
  return memo(i, k) = max;
  
}

void testcase(){
  int n, m, k; cin >> n >> m;
  long x; cin >> x >> k;
  
  vector< vector< pair<int, int> > > board(n);
  
  for(int i = 0; i < m; ++i){
    int u, v, p; cin >> u >> v >> p;
    board[u].push_back({v, p});
  }
  
  _memo = new vector< vector<long> > (n, vector<long> (k + 1, - 1));
  
  
  for(int i = 0; i <= k; ++i){
    if(f(board, 0, i) >= x){
      cout << i << "\n";
      delete _memo;
      return;
    } 
  }
  
  cout << "Impossible\n";
  
  delete _memo;
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
}