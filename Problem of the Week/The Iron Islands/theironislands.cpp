#include <bits/stdc++.h>


std::istream & fp = std::cin;

int sliding_window(const std::vector< int > & path, int k, const std::vector<int> & c){
  int n = path.size();

  int i = 0;
  int j = 0;
  int sum = 0;
  int max = 0;
  while(true){
    int count = j - i;
    if(sum == k){
      max = std::max(max, count);
      sum -= c[path[i++]];
    } 
    else if(sum < k){
      if(j == n) break;
      sum += c[path[j++]];
    }
    else{
      sum -= c[path[i++]];
    }
    
    if(i > j){
      j = i;
      sum = c[path[i]];
    }
  
  }
  
  return max;
}

void testcase(){
  int n, k, w; fp >> n >> k >> w;
  
  std::vector<int> c(n);
  for(int i = 0; i < n; ++i){
    fp >> c[i];
  }
  
  std::vector<std::vector< int >> paths(w);
  
  for(int i = 0; i < w; ++i){
    int l; fp >> l;
    for(int j = 0; j < l; ++j){
      int island; fp >> island;
      paths[i].push_back(island);
    }
  }
  
  int max = 0;
  for(int i = 0; i < w; ++i){
    max = std::max(max, sliding_window(paths[i], k, c));
  }
  
  std::unordered_map<int, int> lookup;
  std::vector<int> sums;
  sums.reserve(n);
  
  for(int i = 0; i < w; ++i){
    sums.resize(1);
    for(int j = 1, partialSum = 0; j < (int)paths[i].size(); ++j){
      partialSum += c[paths[i][j]];
      if(partialSum >= k) break;
      sums.push_back(partialSum);
    }
    
    for(int j = 1; j < (int)sums.size(); ++j){
      auto iter = lookup.find(k - sums[j] - c[0]);
      if(iter != std::end(lookup)){
        max = std::max(max, j + iter -> second + 1);
      }
    }
    
    for(int j = 1; j < (int)sums.size(); ++j){
      auto iter = lookup.find(sums[j]);
      if(iter != std::end(lookup)){
        iter -> second = std::max(iter -> second, j);
      }
      else{
        lookup.emplace_hint(iter, sums[j], j);
      }
    
    }
  }
  
  
  std::cout << max << "\n";
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--)
    testcase();

}