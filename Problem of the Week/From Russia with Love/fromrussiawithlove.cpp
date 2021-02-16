#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::vector<int> VI;
int n, m, k;
VI *_memo;

#define memo(l, r) (*_memo)[(n*(l)) + r]

int f(const VI & x, int l, int r){
  if(l > r) return 0;
  
  if(memo(l, r) != - 1) return memo(l, r);
  
  if( ((n - r - 1) + l) % m == k) return memo(l, r) = std::max(x[l] + f(x, l + 1, r), x[r] + f(x, l, r - 1));
  else return memo(l, r) = std::min(f(x, l + 1, r), f(x, l, r - 1));
}

void testcase(){
  fp >> n >> m >> k;
  VI x(n);
  for(int i = 0; i < n; ++i) fp >> x[i];
  
  _memo = new VI(n * n, -1);
  
  std::cout << f(x, 0, n - 1) << "\n";
  
  delete _memo;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}