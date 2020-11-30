#include <bits/stdc++.h>

using namespace std;

bool compareBoats(const pair<int, int> &b1, const pair<int, int> &b2){
  return b1.second < b2.second;
}

void testcase(){
  int n; cin >> n;
  
  vector < pair < int, int> > boats;
  for(int i = 0; i < n; ++i){
    int l, r; cin >> l >> r;
    boats.push_back({l, r});
    
  }
  
  sort(boats.begin(), boats.end(), compareBoats);
  
  int previous_end = numeric_limits<int>::min();
  int count = 0;
  for(int i = 0; i < n; ++i){
    if(boats[i].second < previous_end) continue;
    
    if(boats[i].second - boats[i].first >= previous_end){
      ++count;
      previous_end = boats[i].second;
    }
    else{
      int best = previous_end + boats[i].first;
      int j = i + 1;
      int bestBoat = i;
      while(j < n && best >= boats[j].second){
        int temp = max(previous_end + boats[j].first, boats[j].second);
        if(temp < best){
          best = temp;
          bestBoat = j;
        } 
        ++j;
      }
      
      count++;
      previous_end = max(previous_end + boats[bestBoat].first, boats[bestBoat].second);
      i = bestBoat;
    }

  }
  
  cout << count << "\n";
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
}