#include <bits/stdc++.h>

#define EMPTY 4
#define RIOT -1


inline int types(unsigned queue, int m, int k) {
  std::unordered_set<unsigned> present;
  
  for (int i = 0; i < m; i++) {
    unsigned elem = queue & 7;
    if (elem != EMPTY) {
      present.insert(elem);
    }
    
    queue >>= 3;
  }
  
  return present.size();
}


std::vector<std::vector<std::unordered_map<long, long>>> *_memo;
std::vector<int> POW_2;

#define memoid(nth, sth) (qs*(sth) + (nth))
#define memo(i, pq, nth, sth) (*_memo)[i][pq][memoid(nth, sth)]

#define pqb 11
#define qs (1 << (3*(m - 1)))

long excitement(const std::vector<unsigned> &x, int i, int pq, unsigned north, unsigned south,const int & m,const int & k) {
  const long n = x.size();
  
  if (pq < 0) {
    pq *= -1;
    std::swap(north, south);
  }

  if (i >= n) return 0;
  if (pq > pqb) return RIOT;
  
  unsigned north_cut = ((north << 3) & ((1u << (3*m)) - 1));
  unsigned south_cut = ((south << 3) & ((1u << (3*m)) - 1));
  if ((*_memo)[i][pq].find(memoid(north_cut, south_cut)) != (*_memo)[i][pq].end()) return memo(i, pq, north_cut, south_cut);
  
  unsigned north_new = x[i] | north_cut;
  unsigned south_new = x[i] | south_cut;

  long res_n = RIOT;
  long res_s = RIOT;
                                               
  long exc_n = 1000l * types(north_new, m, k) - POW_2[std::abs(pq + 1)];
  long exc_s = 1000l * types(south_new, m, k) - POW_2[std::abs(pq - 1)];
  
  if (exc_n >= 0) {
    long temp = excitement(x, i+1, pq+1, north_new, south, m, k);
    if (temp != RIOT) res_n = exc_n + temp;
  }
  
  if (exc_s >= 0) {
    long temp = excitement(x, i+1, pq-1, north, south_new, m, k);
    if (temp != RIOT) res_s = exc_s + temp;
  }

  return memo(i, pq, north_cut, south_cut) = std::max(res_s, res_n);
}



int main(int argc, const char* argv[]) {
  std::cin.sync_with_stdio(false);
  
  std::istream &fp = std::cin;
  
  int testcases;
  fp >> testcases;
  
  int curr = 1;
  for (int i = 0; i <= 12; i++) {
    POW_2.push_back(curr);
    curr *= 2;
  }
  
  for (int t = 0; t < testcases; t++) {
    int n, k, m; fp >> n >> k >> m;
    std::vector<unsigned> x(n);
    
    for (int i = 0; i < n; i++) fp >> x[i];
    
    unsigned empty_queue = 0;
    for (int i = 0; i < m; i++) {
      empty_queue <<= 3;
      empty_queue |= EMPTY;
    }
    
    _memo = new std::vector<std::vector<std::unordered_map<long, long>> >(n, std::vector<std::unordered_map<long, long>>(pqb + 1));

    
    std::cout << excitement(x, 0, 0, empty_queue, empty_queue, m, k) << "\n";
    
    delete _memo;
  }
  
  return 0;
}



