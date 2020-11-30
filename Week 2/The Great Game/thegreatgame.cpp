#include <bits/stdc++.h>

using namespace std;

#define adj(i) ((*adj)[i])


typedef std::vector< std::vector<int> > matrix;

matrix *adj;
int *own;
int *oth;



int n;


int f(int i, int p){

  if(i == n) return 1;


  if(p){
    if(own[i] != -1) return own[i];
  }
  else{
    if(oth[i] != -1) return oth[i];
  }

  int min = numeric_limits<int>::max();
  int max = numeric_limits<int>::min();
  for(int v : adj(i)){
      int temp = 1 + f(v, !p);
      if(!p){
        if(temp > max) max = temp;
      } 
      else{
        if(temp < min) min = temp;
      }
  }

  if(p) own[i] = min;
  else oth[i] = max;
  
  return !p ? max : min;

}


void testcase(){
    int m, r, b; cin >> n >> m >> r >> b;

    adj = new vector< vector<int> >(n+1);

    own = new int [n+1];
    oth = new int [n+1];
    
    for(int i = 0; i < n+1; ++i){
      own[i] = -1;
      oth[i] = -1;
    }

    for(int i = 0; i < m; ++i){
        int u; cin >> u;
        int v; cin >> v;
        adj(u).push_back(v);
    }


    int sh = f(r, 1);
    int mo = f(b, 1);

    char w;

    if(sh == mo){
        if(sh % 2 != 0) w = '1';
        else w = '0';
    }
    else if(sh < mo) w = '0';
    else w = '1';

    cout << w << "\n";

    delete adj;
    delete own;
    delete oth;

}

int main(int argc, const char *argv[]){
    ios_base::sync_with_stdio(false);

    int t; cin >> t;

    while(t--) testcase();

    return 0;
}