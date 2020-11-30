#include <bits/stdc++.h>

using namespace std;

#define memo(i, j) ((*memo)[v.size()*(i) + (j)])

vector<int> v;
vector<int> *memo;

int recursive(int i, int j){
  if((v.size() + i + j) % 2 != 0){
    if(i == j) return v[i];
    if(memo(i, j) >= 0) return memo(i,j);
    return memo(i,j) = max(v[j] + recursive(i, j - 1), v[i] + recursive(i + 1, j));
  }
  else{
    if(i == j) return 0;
    if(memo(i, j) >= 0) return memo(i,j);
    return memo(i,j) = min(recursive(i, j - 1), recursive(i + 1, j)); 
  }
 
}



void testcase(){
  int n; cin >> n;
  
  for(int i = 0; i < n; ++i){
    int x; cin >> x;
    v.push_back(x); 
  } 
  
  memo = new vector<int>(n * n, - 1);
  cout << recursive(0, n - 1) << "\n";
  
  v.clear();
  delete memo;
  
}


int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
}