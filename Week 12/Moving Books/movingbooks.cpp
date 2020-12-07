#include <bits/stdc++.h>

std::istream & fp = std::cin;

void testcase(){
  int n, m; fp >> n >> m;
  std::vector<int> s(n);
  std::vector<int> w(m);
  for(int i = 0; i < n; ++i) fp >> s[i];
  for(int i = 0; i < m; ++i) fp >> w[i];
  
  std::sort(s.begin(), s.end(), std::greater<int>());
  std::sort(w.begin(), w.end(), std::greater<int>());
  
  if(s[0] < w[0]) {
    std::cout << "impossible\n";
    return;
  }
  
  int i = 0;
  int j = 0;
  int max = m / n + (m % n != 0);
  while(i < n && s[i] >= w[j]) ++i;
  while(i < n){
    while(j < m && s[i] < w[j]) ++j;
    int temp = j / i;
    if(j % i != 0) temp += 1;
    max = std::max(max, temp);
    while(i < n && s[i] >= w[j]) ++i;
    if(i == n) break;
  }
  
  std::cout << max * 2 + (max - 1) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}