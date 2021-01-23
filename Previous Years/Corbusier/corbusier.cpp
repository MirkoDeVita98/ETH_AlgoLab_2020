#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

VII *_memo;

#define memo(i, j) ((*_memo)[i][j])

bool f(const VI & disks, int i, int k, int index){
  if(index >= (int)disks.size()) return false;
  if(disks[index] % k == i) return true;
  
  if(memo(index, i) != -1) return memo(index, i);

  bool not_take = f(disks, i, k, index + 1);
  bool take = disks[index] <= i ? f(disks, (i - disks[index]) % k, k, index + 1) : f(disks, k - (disks[index] - i) % k, k, index + 1);
  
  return (memo(index, i) = (take || not_take));
}

void testcase(){
  int n, i, k; fp >> n >> i >> k;
  
  VI disks(n);
  for(int i = 0; i < n; ++i) fp >> disks[i];
  
  _memo = new VII(n + 1, VI(k + 1, - 1));
  
  if(f(disks, i, k, 0)) std::cout << "yes\n";
  else std::cout << "no\n";
  
  delete _memo;
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}