#include <bits/stdc++.h>

using namespace std;

void testcase(){
  int n; cin >> n;
  
  vector<int> partialSums(n, 0);
  
  cin >> partialSums[0];
  for(int i = 1; i < n; ++i){
    int x; cin >> x;
    partialSums[i] = x + partialSums[i - 1];
  }
  
  int e = (partialSums[0] % 2 == 0) ? 1 : 0;
  for(int i = 1; i < n; ++i){
    if((partialSums[i] - partialSums[0]) % 2 == 0) ++e;
  }
  
  int o = n - e;
  int evenSequences = e + e*(e - 1)/2 + o*(o - 1)/2;
  
  cout << evenSequences << endl;
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) testcase();
}