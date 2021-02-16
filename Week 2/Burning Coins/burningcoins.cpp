#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::vector<int> VI;

int n;
VI * _memo;

#define memo(i, j) ((*_memo)[(n*(l)) + r])

int f(const VI & v, int l, int r){
  if(l > r) return 0;
  if(memo(l, r) != - 1) return memo(l, r);
  
  if((l + n - r - 1) % 2 == 0) return memo(l, r) = std::max(v[l] + f(v, l + 1, r), v[r] + f(v, l, r - 1));
  else return memo(l, r) = std::min(f(v, l + 1, r), f(v, l, r - 1));
}

void testcase(){
  fp >> n;
  VI v(n);
  for(int i = 0; i < n; ++i) fp >> v[i];
  _memo = new VI(n * n, - 1);
  std::cout << f(v, 0, n - 1) << "\n";
  delete _memo;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}