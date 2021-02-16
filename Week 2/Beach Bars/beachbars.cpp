#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::vector<int> VI;

void testcase(){
  int n; fp >> n;
  VI x(n);
  for(int i = 0; i < n; ++i) fp >> x[i];
  std::sort(x.begin(), x.end());
  
  int i = 0, j = 0;
  VI loc;
  int max_par = 0;
  int min_dist = std::numeric_limits<int>::max();
  while(i < n && j < n){
    int bar = x[j] - x[i];
    int bar_f = floor((float)bar/2); 
    int bar_c = ceil((float)bar/2); 
    if(bar > 200) i += 1;
    else{
      int parasols = j - i + 1;
      if(parasols >= max_par){
        if(parasols > max_par || bar_c < min_dist){
          loc.clear();
          min_dist = bar_c;
          max_par = parasols;
        } 
        if(bar_c <= min_dist){
          loc.push_back(bar_f + x[i]);
          if(bar_c != bar_f )loc.push_back(bar_c + x[i]);
        }
      }
      j += 1;
    }
  }
  
  std::cout << max_par << " " << min_dist << "\n";
  for(int bar_loc : loc) std::cout << bar_loc << " ";
  std::cout << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}