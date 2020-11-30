#include <bits/stdc++.h>

using namespace std;

void testcase(){
  int n; cin >> n;
  
  vector<int> m(n);
  vector < vector<int> > p(n);
  
  
  for(int i = 0; i < n; ++i) cin >> m[i];
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m[i]; ++j){
      int temp; cin >> temp;
      p[i].push_back(temp);
    }  
  }
    
  
  vector<int> c(n, 0);
  set< pair<int, int> > nexts;
  
  for(int i = 0; i < n; ++i){
    nexts.insert({p[i][0], i});
  }
  
  int in = nexts.rbegin() -> first - nexts.begin() -> first + 1;
  while(true){
    pair<int, int> next = *nexts.begin();
    if(c[next.second] < m[next.second] - 1){
        nexts.erase(next);
        nexts.insert({p[next.second][++c[next.second]], next.second});
    }
    else break;
    int candidate = nexts.rbegin() -> first - nexts.begin() -> first + 1;
    if(candidate < in) in = candidate;
  }
  
  
  cout << in << "\n";
  
}

int main(int argc, const char * argv[]){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int t; cin >> t;
  while(t--) testcase();
  
  
  return 0;
}