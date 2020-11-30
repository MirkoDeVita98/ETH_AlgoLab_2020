
#include <bits/stdc++.h>

std::istream & fp = std::cin;


int f(int (*dp)[2][2],const std::vector< std::vector<int> > & s, const std::vector<int> & c, int n, int i, int covered, int compulsory){
  
  if(dp[i][covered][compulsory] != -1)
    return dp[i][covered][compulsory];
    
  if(s[i].empty()){
    if (covered) return dp[i][covered][compulsory] = 0;
    else return dp[i][covered][compulsory] = c[i];
  }
  
  int cov = 0;
  int not_cov = 0;
  for(int j : s[i]){
    cov += f(dp, s, c, n, j, 1, 0);
    not_cov += f(dp, s, c, n, j, 0, 0);
  }
  
  if(compulsory)
    return dp[i][covered][compulsory] = c[i] + cov;

    
  if(covered)
    return dp[i][covered][compulsory] = std::min(c[i] + cov, not_cov);

  int m = c[i] + cov;
  for(int j : s[i]){
    m = std::min(m, not_cov - f(dp, s, c, n, j, 0, 0)  + f(dp, s, c, n, j, 0, 1));
  } 
  
  return dp[i][covered][compulsory] = m;
}

void testcase(){
  int n; fp >> n;
  
  std::vector< std::vector<int> > s(n);
  for(int k = 1; k < n ; ++k){
    int i,j; fp >> i >> j;
    s[i].push_back(j);
  }
  
  std::vector<int> c(n);
  for(int i = 0; i < n; ++i) fp >> c[i];
  
  int dp[n][2][2];
  memset(dp, -1, sizeof(dp));
  
  std::cout << f(dp, s, c, n, 0, 0, 0) << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}