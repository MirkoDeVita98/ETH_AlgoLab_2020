#include <bits/stdc++.h>

using namespace std;

void testcase(){
  int n; cin >> n;
  
  vector<int> heights(n);
  
  int count = 0;
  
  for(int i = 0; i < n; ++i) cin >> heights[i];
  
  int curr_height = heights[0];
  int curr_index = 0;
  
  for(int j = 0; j < n; ++j){
    if(j < curr_index + curr_height){
      count++;
      if(j + heights[j] > curr_index + curr_height){
        curr_index = j;
        curr_height = heights[j];
      }
    }
  }

  cout << count << endl;
  
}

int main(){
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) testcase();
}