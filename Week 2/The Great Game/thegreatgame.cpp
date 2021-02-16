#include <bits/stdc++.h>

std::istream & fp = std::cin;
typedef std::vector<int> VI;
typedef std::vector<VI> VII;

int n;
VI *_memo;

#define memo(u, p) ((*_memo)[(2*u) + p])

int f(const VII & t, int u, int p){
  if(u == n) return 0;
  
  if(memo(u, p) != -1) return memo(u, p);
  
  int temp = p ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
  for(int v : t[u]){
    if(p) temp = std::min(temp, 1 + f(t, v, !p));
    else temp = std::max(temp, 1 + f(t, v, !p));
  }
  return memo(u, p) = temp;
}

void testcase(){
  int m, r, b; fp >> n >> m >> r >> b;
  VII t(n + 1);
  
  for(int i = 0; i < m; ++i){
    int u, v; fp >> u >> v;
    t[u].push_back(v);
  }
  
  _memo = new VI(2*(n + 1), -1);
  
  int sh = f(t, r, 1);
  int mo = f(t, b, 1);
  
  int w;
  if(sh == mo) w = sh % 2 == 0;
  else if(sh < mo) w = 0;
  else w = 1;
  
  std::cout << w << "\n";
  
  delete _memo;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}