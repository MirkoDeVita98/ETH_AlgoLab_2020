#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long ll;

int r_bin(const vector< pair<ll, ll> > &subS2, ll t1, ll T){
  int L = 0;
  int R = subS2.size();
  
  while(L < R){
    int mid = (L + R)/2;
    
    if(subS2[mid].second + t1 < T) L = mid + 1;
    else R = mid;
  }
  
  return L - 1;
}

bool compare_time(pair<ll, ll> p1, pair< ll, ll> p2){
  return p1.second < p2.second;
}

bool split_and_list(ll d_gulp,const vector< pair<ll,ll> > &movements,int n,ll D,ll T){
  vector< pair<ll, ll> > S1(movements.begin(), movements.begin() + movements.size() / 2);
  vector< pair<ll, ll> > S2(movements.begin() + movements.size() / 2, movements.end());

  vector< pair<ll, ll> > subS1;
  vector< pair<ll, ll> > subS2;
  
  for (ll s = 0; s < (1 << (ll)S1.size()); ++s) {
    ll t = 0; 
    ll d = 0;
    for(ll i = 0; i < (ll)S1.size(); ++i){
      if (s & (1 << i)){
        t += S1[i].second;
        if(t > T) break;
        d += (S1[i].first + d_gulp);
      } 
    }
    if(t < T) subS1.push_back({d, t});
    if(d >= D && t < T) return true;
  }
  
  for (ll s = 0; s < (1 << (ll)S2.size()); ++s) {
    ll t = 0; 
    ll d = 0;
    for(ll i = 0; i < (ll)S2.size(); ++i){
      if (s & (1 << i)){
        t += S2[i].second;
        if(t > T) break;
        d += (S2[i].first + d_gulp);
      } 
    }
    if(t < T) subS2.push_back({d, t});
    if(d >= D && t < T) return true;
  }
  
  sort(subS2.begin(), subS2.end(), compare_time);
  
  vector<ll> partialMax(subS2.size());
  partialMax[0] = subS2[0].first;
  ll currMax = subS2[0].first;
  for(ll i = 1; i < (ll)subS2.size(); ++i){
    if(subS2[i].first > currMax) currMax = subS2[i].first;
    partialMax[i] = currMax;
  }
  
   for(ll i = 0; i < (ll)subS1.size(); ++i){
    pair<ll, ll> set1 = subS1[i];
    ll index = r_bin(subS2, set1.second, T);
    
    if(index != (ll)subS2.size() && partialMax[index] + set1.first >= D) return true;
  }
  
  return false;
}

int minimum(int n,ll D,ll T,const vector< pair<ll,ll> > &movements,vector< ll > gulps){
  int L = 0;
  int R = gulps.size();
  
  while(L < R){
    int mid = (L + R) / 2;
    if(split_and_list(gulps[mid], movements, n, D, T)) R = mid;
    else L = mid + 1;
  }
  
  return L;
}

void testcase(int test){
  int n, m; cin >> n >> m;
  ll D, T; cin >> D >> T;
  
  vector< pair<ll,ll> > movements(n);
  vector< ll > gulps(m + 1);
  
  for(int i = 0; i < n; ++i){
    ll d, t; cin >> d >> t;
    movements[i] = {d, t};
  }
  
  gulps[0] = 0;
  for(int i = 1; i <= m; ++i){
    cin >> gulps[i];
  }
  
  ll gulp = minimum(n, D, T, movements, gulps);
  
  if(gulp != (ll)gulps.size()) cout << gulp << "\n";
  else cout << "Panoramix captured\n";
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  while(t--) testcase(t);
}
