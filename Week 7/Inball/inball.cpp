#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>


typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

void testcase(int n, int d){
  
  std::vector< std::vector<int> > planes(n, std::vector<int>(d + 1));
  
  std::vector<int> norms(n);
  
  for(int i = 0; i < n; ++i){
    int squares = 0;
    for(int j = 0; j <= d; ++j){
      fp >> planes[i][j];
      if(j != d){
        squares += (planes[i][j]*planes[i][j]);
      } 
    }
    norms[i] = std::sqrt(squares);
  }
  
  Program lp (CGAL::SMALLER, false, 0, false, 0); 
  
  const int r = d;
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < d; ++j){
      lp.set_a(j, i,  planes[i][j]);
    }
    lp.set_a(r, i,  norms[i]);
    lp.set_b(i, planes[i][d]);
  }
  
  lp.set_c(r, -1);  
  lp.set_l(r, true, 0);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  
  if (s.is_optimal()) {
    int value = ceil(CGAL::to_double(s.objective_value()));
    std::cout << std::fixed << std::setprecision(0) << -value << "\n";
  }
  
  if (s.is_unbounded()) { 
    std::cout << "inf\n";
  }

  if (s.is_infeasible()) { 
    std::cout << "none\n";
  }
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0); std::cout.tie(0);
  
  int n, d;
  
  while(fp >> n && n){
    fp >> d;
    
    testcase(n, d);
  }
}