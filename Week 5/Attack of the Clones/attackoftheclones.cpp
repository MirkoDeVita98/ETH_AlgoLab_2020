#include <bits/stdc++.h>

std::istream &fp = std::cin;

struct interval {
  long a;
  long b;
  
  bool operator<(const interval &other) {
    return b < other.b;
  }
};

struct inc_point {
  long seg;
  int inc;
  long iv;
  
  bool operator<(const inc_point &other) {
    return seg < other.seg;
  }
};


long interval_sched(const std::vector<interval> &ints, long start, long end) {
  const long n = ints.size();
  
  long cnt = 0;
  for (long i = 0; i < n; i++) {
    const interval &iv = ints[i];
    
    if (iv.b > end) break;
    if (iv.a < start) continue;
    
    start = iv.b + 1;
    cnt++;
  }
  
  return cnt;
}

void testcase(){
  long n, m; fp >> n >> m;

  std::vector<interval> ints;
  for (int i = 0; i < n; i++) {
    long a, b; fp >> a >> b;
    
    if (a > b) a -= m;
    ints.push_back({ a, b });
    ints.push_back({ a+m, b+m });
  }

  std::sort(ints.begin(), ints.end());
  
  std::unordered_set<int> cur_ints;
  for (int i = 0; i < n; i++) { const auto &it = ints[i];
    if (it.a <= 1 && 1 <= it.b) cur_ints.insert(i);
  }
  
  std::vector<inc_point> ps;
  for (int i = 0; i < n; i++) {
    const auto &it = ints[i];
    
    if (ints[i].a > 1) ps.push_back({ it.a, +1, i });
    if (ints[i].b > 1) ps.push_back({ it.b+1, -1, i });
  }

  std::sort(ps.begin(), ps.end());
  
  long cur_seg = 1;
  for (auto &icp : ps) {
    cur_seg = icp.seg;

    if (icp.inc > 0) cur_ints.insert(icp.iv);
    else cur_ints.erase(icp.iv);
    
    if (cur_ints.size() <= 10) break;
  }
  
  // (cur_seg + 1) ... (cur_seg + m - 1)
  long max_ints = interval_sched(ints, cur_seg + 1, cur_seg + m - 1);
  for (auto &si : cur_ints) {
    const auto &starting_int = ints[si];
    
    // (starting_int.b + 1) ... (starting_int.a + m - 1)
    max_ints = std::max(max_ints, 1 + interval_sched(ints, starting_int.b + 1, starting_int.a + m - 1));
  }
  
  std::cout << max_ints << "\n";
}

int main(int argc, const char *argv[]) {
  std::cin.sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}