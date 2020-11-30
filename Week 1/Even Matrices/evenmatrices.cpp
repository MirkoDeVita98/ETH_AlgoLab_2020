#include <bits/stdc++.h>
#include <cassert>

using namespace std;

void testcase(){
  int n; cin >> n;
  
  vector< vector<int> > m(n, vector <int> (n));
  vector<vector <int> > temp(n, vector<int> (n));
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      cin >> m[i][j];
      temp[i][j] = m[i][j];
    }
  }
  
  int numOfSequences = 0;
  int count = 0;
  
  while(count != n){
    for(int i = count; i < n; ++i){
      vector<int> partialSums(n);
      
      partialSums[0] = m[i][0];
      for(int j = 1; j < n; ++j){
        partialSums[j] = m[i][j] + partialSums[j - 1];
      }
      
      int e = (partialSums[0] % 2 == 0) ? 1 : 0;
      for(int i = 1; i < n; ++i){
        if((partialSums[i] - partialSums[0]) % 2 == 0) ++e;
      }
  
      int o = n - e;
      int evenSequences = e + e*(e - 1)/2 + o*(o - 1)/2;
    
      
      numOfSequences += evenSequences;
    }
    
  
    ++count;
    
    for(int i = count; i < n; ++i){
      for(int j = 0; j < n; ++j){
        m[i][j] += temp[i  - count][j];
      }
    }
    
  
  }
  
  cout << numOfSequences << endl;
  

  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  for(int i = 0; i < t; ++i) testcase();
  
  return 0;
}