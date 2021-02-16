#include <bits/stdc++.h>

typedef std::vector<double> VD;

std::istream & fp = std::cin;

int n, m;
VD *_memo;

#define memo(i, k) ((*_memo)[((m + 1)*(i)) + k])

double f(const VD & p, int i, int k){
  if(k >= m) return 1;
  if(i >= n) return 0;
  
  if(memo(i, k) != -1) return memo(i, k);
  
  double max_p = 0;
  for(int b = 0; b <= k; ++b) max_p = std::max(max_p, p[i]*f(p, i + 1, k + b) + (1 - p[i])*f(p, i + 1, k - b));
  
  return memo(i, k) = max_p;
}

void testcase(){
  int k; fp >> n >> k >> m;
  VD p(n);
  for(int i = 0; i < n; ++i) fp >> p[i];
  
  _memo = new VD((m + 1) * n, -1);
  
  std::cout << std::fixed << std::setprecision(5) << f(p, 0, k) << "\n";
  
  delete _memo;
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}