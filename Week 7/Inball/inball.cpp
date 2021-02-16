#include <bits/stdc++.h>
#include <CGAL/QP_models.h> 
#include <CGAL/QP_functions.h> 
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

void testcase(int n){
  int d; fp >> d;
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  const int r = d;
  lp.set_l(r, true, 0);
  
  for(int j = 0; j < n; ++j){
    int sum_of_squares = 0;
    for(int i = 0; i < d; ++i){
      int a; fp >> a;
      sum_of_squares += (a*a);
      lp.set_a(i, j, a);
    }
    int b; fp >> b;
    int norm = std::sqrt(sum_of_squares);
    lp.set_b(j, b);
    lp.set_a(r, j, norm);
  }
  
  lp.set_c(r, -1);
  
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) std::cout << "none\n";
  else if(s.is_unbounded()) std::cout << "inf\n";
  else std::cout << std::fixed << std::setprecision(0) << std::floor(CGAL::to_double(-s.objective_value())) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int n;
  while(fp >> n && n) testcase(n);
  return 0;
}