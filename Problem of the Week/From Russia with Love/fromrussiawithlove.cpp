#include <bits/stdc++.h>

using namespace std;

#define own(i, j) ((*own)[s.size()*(i) + (j)])
#define oth(i, j) ((*oth)[s.size()*(i) + (j)])

vector<int> s;
int m, k, n;

vector< int > *own;
vector< int > *oth;

int f(int i, int l, int r){
  if(l > r) return 0;
  if(i == m) i = 0;
  
  if(i == k){
    
    if(own(l, r) != -1) return own(l, r);
    
    own(l, r) = max(s[l] + f(i + 1, l + 1, r), s[r] + f(i + 1, l, r - 1));
    
    return own(l, r);

  }
  else{
    
    if(oth(l, r) != -1) return oth(l, r);
    
    oth(l, r) = min(f(i + 1, l + 1, r), f(i + 1, l, r - 1));
    
    return oth(l, r);
  }
  
}

void testcase(){
  cin >> n >> m >> k;
  
  own = new vector<int>(n * n, - 1);
  oth = new vector<int>(n * n, - 1);
  
  for(int i = 0; i < n; ++i){
    int x; cin >> x;
    s.push_back(x);
  } 
  
  int w;
  
  if(k == 0){
    w = max(s[0] + f(1, 1, n - 1), s[n - 1] + f(1, 0, n - 2));
  }
  else{
    w = min(f(1, 1, n - 1), f(1, 0, n - 2));
  }
  
  cout << w << "\n";
  
  s.clear();
  
  delete own;
  delete oth;
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}