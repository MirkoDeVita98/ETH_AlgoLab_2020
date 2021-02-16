#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::vector<int> VI;
typedef std::vector< VI> VII;

int n;
VI *_memo;
#define memo(u, cov, comp) ((*_memo)[2*((2*(u)) + cov) + comp])

int f(const VII & s, const VI & c, int u, int covered, int compulsory){
  
  if(memo(u, covered, compulsory) != -1) return memo(u, covered, compulsory);
  
  if(s[u].empty()){
    if(covered) return memo(u, covered, compulsory) = 0;
    else return memo(u, covered, compulsory) = c[u];
  }
  
  int cov = c[u];
  for(int v : s[u]) cov += f(s, c, v, 1, 0);

  
  if(compulsory) return memo(u, covered, compulsory) = cov;
  
  int not_cov = 0;
  for(int v : s[u]) not_cov += f(s, c, v, 0, 0);

  
  if(covered) return memo(u, covered, compulsory) = std::min(cov, not_cov);
  
  int one_compulsory = cov;
  for(int v : s[u]){
    one_compulsory = std::min(one_compulsory, not_cov - f(s,c, v, 0, 0) + f(s, c, v, 0, 1));
  }
  
  return memo(u, covered, compulsory) = one_compulsory;
  
}

void testcase(){
  fp >> n;
  VII s(n);
  for(int i = 1; i < n; ++i){
    int u, v; fp >> u >> v;
    s[u].push_back(v);
  }
  VI c(n);
  for(int i = 0; i < n; ++i) fp >> c[i];
  
  _memo = new VI(2*2*n, -1);
  
  std::cout << f(s, c, 0, 0, 0) << "\n";
  
  delete _memo;
}


int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}