#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::pair<int, int> iPair;
typedef std::vector<int> VI;
typedef std::vector< VI > VII;

void testcase(){
  int n; fp >> n;
  
  VII p(n);
  
  for(int i = 0; i < n; ++i){
    int m; fp >> m;
    p[i].resize(m);
  }
  
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < (int)p[i].size(); ++j) 
      fp >> p[i][j];
  
  std::priority_queue< iPair , std::vector< iPair> ,std::greater< iPair> > min;
  int b = 0;
  VI index(n, 0);
  
  for(int i = 0; i < n; ++i){
    min.push({p[i][0], i});
    b = std::max(b, p[i][0]);
  } 
  
  int interval = std::numeric_limits<int>::max();
  while(true){
    iPair a = min.top();
    interval = std::min(interval, b - a.first + 1);
    index[a.second] += 1;
    if(index[a.second] == (int)p[a.second].size()) break;
    else{
      min.pop();
      min.push({p[a.second][index[a.second]], a.second});
      b = std::max(b, p[a.second][index[a.second]]);
    }
  }
  
  std::cout << interval << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}