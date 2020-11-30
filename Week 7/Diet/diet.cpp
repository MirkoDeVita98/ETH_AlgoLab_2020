#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

void testcase(int n, int m){
  
  std::vector< std::pair<int, int> > b(n);
  for(int i = 0; i < n; ++i){
    int min, max; fp >> min >> max;
    b[i] = {min, max};
  }
  
  std::vector< int> p(m);
  std::vector< std::vector<int> > c(m, std::vector<int> (n));
  
  for(int i = 0; i < m; ++i){
    fp >> p[i];
    for(int j = 0; j < n; ++j) fp >> c[i][j];
  }
  
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  
  for(int i = 0; i < n; ++i){
    int min = b[i].first;
    int max = b[i].second;
    for(int j = 0; j < m; ++j){
      lp.set_a(j, i, c[j][i]);
      lp.set_a(j, i + n, -c[j][i]); 
    }
    lp.set_b(i, max);
    lp.set_b(i + n, -min);
  }
  
  for(int i = 0; i < m; ++i){
    lp.set_c(i, p[i]);
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_optimal()) {
    int value = floor(CGAL::to_double(s.objective_value()));
    std::cout << std::fixed << std::setprecision(0) << value << "\n";
  }

  if (s.is_infeasible()) { 
    std::cout << "No such diet.\n";
  }
  
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0); std::cout.tie(0);
  
  int n, m;
  
  while(fp >> n >> m && n != 0 && m!= 0) testcase(n, m);
  
  return 0;
}