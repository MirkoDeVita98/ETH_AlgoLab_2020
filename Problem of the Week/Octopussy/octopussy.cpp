#include <bits/stdc++.h>

using namespace std;

bool will_he_make_it(vector<int> &times, int &t, vector<bool> &defused, int index, int threshold){
  if(defused[index]) return true;
  
  if(index > threshold){
    if(t < times[index]){
      t++;
      return defused[index] = true;
    }
    else return false;
  }
  
  if(t >= times[index]) return false;
  
  if(will_he_make_it(times, t, defused, 2*index + 2, threshold) &&
    will_he_make_it(times, t, defused, 2*index + 1, threshold)){
    if(t < times[index]){
      t++;
      return defused[index] = true;
    }
  }
  
  return false;
}

void testcase(){
  int n; cin >> n;
  
  vector<pair<int, int>> bombs(n);
  vector< int > times(n);
  
  for(int i = 0; i < n; ++i){
    int t; cin >> t;
    times[i] = t;
    bombs[i] = {t, i};
  }
  
  sort(bombs.begin(), bombs.end());
  
  vector< bool > defused(n, false);
  
  int threshold = (n - 3)/2;
  bool check = true;
  int t = 0;
  for(int i = 0; check && i < n; ++i){
    check = will_he_make_it(times, t, defused, bombs[i].second, threshold);
  }
  
  if(check) cout << "yes\n";
  else cout << "no\n";
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  while(t--) testcase();
  
  return 0;
}