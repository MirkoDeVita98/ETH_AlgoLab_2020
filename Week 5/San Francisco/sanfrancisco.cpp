#include <bits/stdc++.h>

typedef std::pair<int, int> iPair;

std::istream & fp = std::cin;

std::vector<long> *_memo;
int n;
#define memo(i, k) ((*_memo)[(n*(k)) + i])


long f(const std::vector< std::vector< iPair> > & canals, int i, int k){
  if(k <= 0) return 0;
  
  if(memo(i, k) != -1) return memo(i, k);
  
  if(canals[i].empty()) return f(canals, 0, k);
  
  long max = std::numeric_limits<long>::min();
  for(iPair c : canals[i])
    max = std::max(max, c.second + f(canals, c.first, k - 1));
  
  
  return memo(i, k) = max;
}

void testcase(){
  int m, k; fp >> n >> m;
  long x; fp >> x >> k;
  std::vector< std::vector< iPair> > canals(n);
  for(int i = 0; i < m; ++i){
    int u, v, p; fp >> u >> v >> p;
    canals[u].push_back({v, p});
  }
  
  _memo = new std::vector<long>(n*(k + 1), -1);
  
  int L = 0;
  int R = k + 1;
  
  while(L < R){
    int mid = (L + R) / 2;
    if(f(canals, 0, mid) < x) L = mid + 1;
    else R = mid;
  }
  
  if(L > k) std::cout << "Impossible\n";
  else std::cout << L << "\n";
  delete _memo;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}