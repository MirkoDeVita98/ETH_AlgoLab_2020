#include <bits/stdc++.h>

using namespace std;

void testcase(){
  int n; cin >> n;
  vector<int> x(n);
  for(int i = 0; i < n; ++i) cin >> x[i];
  sort(x.begin(), x.end());
  
  int j = 0;
  int i = 0;
  int max = 0;
  int min = numeric_limits<int>::max();
  vector<int> b;
  while(j < n){
    int temp = abs(x[j] - x[i]);
    int f = (int)floor((float)temp/2);
    int c = (int)ceil((float)temp/2);
    
    if(temp > 200) ++i;
    else{
      if(j - i + 1 > max){
        max = j - i + 1;
        b.clear();
        min = c;
        b.push_back(f + x[i]);
        if(c != f) b.push_back(c + x[i]);
      }
      else if(j - i + 1 == max){
        if(c < min){
          min = c;
          b.clear();
          b.push_back(f + x[i]);
          if(c != f) b.push_back(c + x[i]);
        } 
        else if(c == min){
          b.push_back(f + x[i]);
          if(c != f) b.push_back(c + x[i]);
        }
        
      }
      ++j;
    }
  }
  
  cout << max << " " << min << "\n";
  for(int bar : b) cout << bar << " ";
  cout << "\n";
}


int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}