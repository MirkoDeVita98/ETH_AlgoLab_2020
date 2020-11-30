#include <bits/stdc++.h>

using namespace std;

bool compare(const pair<int, int> &p1, const pair<int, int> &p2){
  return p1.second < p2.second;
}

bool compare_checker(const tuple<int, int, int> &t1, const tuple<int, int, int> &t2){
  
  if(get<0>(t1) < get<0>(t2)) return get<1>(t1) > get<1>(t2);
  return get<0>(t1) < get<0>(t2);
}

int scheduling(const vector< pair<int, int> > &intervals, int m, pair<int, int> start){
  
  int a = start.first;
  int b = start.second;
  
  int last = b;
  int count = a != b;
  
  for(pair<int, int> interval : intervals){
    if(interval.second >= m + a) break;
    if(interval.first > last){
      ++count;
      last = interval.second;
    }
  }
  
  return count;
  
}

void testcase(){
  int n, m; cin >> n >> m;
  
  vector< pair<int, int> > jedies(n + 1);
  vector< pair<int, int> > intervals;
  vector< tuple<int, int, int> > checker;
  
  for(int i = 1; i <= n; ++i){
    int a, b; cin >> a >> b;
    
    checker.push_back(make_tuple(a, 1, i));
    checker.push_back(make_tuple(b, -1, i));
    
    if(a > b){
      jedies[i] = {a - m, b};
      intervals.push_back({a - m, b});
      intervals.push_back({a, b + m});
    } 
    else{
      jedies[i] = {a, b};
      intervals.push_back({a, b});
      intervals.push_back({a + m, b + m});
    } 
    
  }
  
  sort(intervals.begin(), intervals.end(), compare);
  
  vector< pair<int, int> > starting;
  //find the segment and the starting intervals
  
  sort(checker.begin(), checker.end(), compare_checker);
  
  int num_intervals = 0;
  int segment = 0;
  for(tuple<int, int, int> temp : checker){
    if(num_intervals = 10)
  }
  
  int max = 0;
  for(pair<int, int> start : starting){
    int num = scheduling(intervals, m, start);
    if(num > max) max = num;
  }
  
  cout << max << "\n";
  
}

int main(int argc, const char *argv[]){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  
  int t; cin >> t;
  
  while(t--) testcase();
  
  return 0;
}