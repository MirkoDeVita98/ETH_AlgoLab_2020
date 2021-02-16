#include <bits/stdc++.h>

typedef std::pair<long, long> lPair;

std::istream & fp = std::cin;

long D, T;

bool create_subsets(const std::vector<lPair> & S, std::vector<lPair> & M, long g){
  for (int s = 0; s < 1 << (int)S.size(); ++s) {
    long t = 0; 
    long d = 0;
    for(int i = 0; i < (int)S.size(); ++i){
      if (s & 1 << i){
        t += S[i].first;
        if(t > T) break;
        d += (S[i].second + g);
      } 
    }
    if(t < T) M.push_back({t, d});
    if(d >= D && t < T) return true;
  }
  return false;
}

bool split_and_list(const std::vector<lPair> & S1, const std::vector<lPair> & S2, long g){
  std::vector< lPair > M1;
  std::vector< lPair > M2;
  
  if(create_subsets(S1, M1, g)) return true;
  if(create_subsets(S2, M2, g)) return true;
  
  std::sort(M2.begin(), M2.end());
  
  std::vector<long> maxD(M2.size());
  long max = M2[0].second;
  for(int i = 0; i < (int)M2.size(); ++i) maxD[i] = max = std::max(max, M2[i].second);
  
  for(lPair m1 : M1){
    long t1 = m1.first;
    long d1 = m1.second;
    int L = 0;
    int R = M2.size();
    while(L < R){
      int mid = (L + R) / 2;
      long t2 = M2[mid].first;
      if(t1 + t2 < T) L = mid + 1;
      else R = mid;
    }
    
    if (d1 + maxD[L - 1] >= D) return true;
  }
  
  return false;
}

void testcase(){
  int n, m; fp >> n >> m;
  fp >> D >> T;
  std::vector< lPair> S1;
  std::vector< lPair>  S2;
  for(int i = 0; i < n; ++i){
    long d, t; fp >> d >> t;
    if(i % 2 !=  0) S1.push_back({t, d});
    else S2.push_back({t, d});
  }
  
  std::vector<long> s(m + 1, 0);
  for(int i = 1; i <= m; ++i) fp >> s[i];
  
  int L = 0;
  int R = s.size();
  while(L < R){
    int mid = (L + R) / 2;
    if(split_and_list(S1, S2, s[mid])) R = mid;
    else L  = mid + 1;
  }
  
  if(L < (int)s.size()) std::cout << L << "\n";
  else std::cout << "Panoramix captured" << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0); std::cout.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}