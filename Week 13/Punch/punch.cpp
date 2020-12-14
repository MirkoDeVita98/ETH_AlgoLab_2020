#include <bits/stdc++.h>

std::istream & fp = std::cin;
int n, k; 

typedef std::pair<int, int> lPair;

std::vector< lPair > *_memo;

#define memo(i, q, b) (*_memo)[((2*(((k + 1)*(i)) + q)) + b)]

lPair comparator(const lPair & p1, const lPair & p2){
  if((p1.first < p2.first) || (p1.first == p2.first && p1.second > p2.second)) return p1;
  return p2;
}

lPair f(const std::vector<int> & c,const std::vector<int> & v, int i, int q, bool b){
  
  if(i >= n) return {std::numeric_limits<int>::max(), 0};
  if(q <= 0) return {0, 0};
  
  if(memo(i, q, b).second != -1) return memo(i, q, b);

  lPair take = f(c, v, i, q - v[i], false);
  if(take.first != std::numeric_limits<int>::max()) take.first += c[i]; 
  if(b == true) take.second += 1;
  
  lPair not_take = f(c, v, i + 1, q, true);
  
  return  memo(i, q, b) = comparator(take, not_take);
}

void testcase(){
  fp >> n >> k;
  
  std::vector<int> c(n);
  std::vector<int> v(n);
  
  for(int i = 0; i < n; ++i) fp >> c[i] >> v[i];
  
  _memo = new std::vector< lPair > (n * (k + 1) * 2, {0, -1});
  
  lPair res = f(c, v, 0, k, true);
  
  std::cout << res.first << " " << res.second << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}