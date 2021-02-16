#include <bits/stdc++.h>
#include <CGAL/QP_models.h> 
#include <CGAL/QP_functions.h> 
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

//t = 0 min, t = 1 max
#define constraint(i, t) (2*(i) + t)

void testcase(int n, int m){
  Program lp (CGAL::SMALLER, true, 0, false, 0);
  for(int i = 0; i < n; ++i){
    int min, max; fp >> min >> max;
    lp.set_b(constraint(i, 0), -min);
    lp.set_b(constraint(i, 1), max);
  }
  for(int j = 0; j < m; ++j){
    int p; fp >> p;
    lp.set_c(j, p);
    for(int i = 0; i < n; ++i){
      int c; fp >> c;
      lp.set_a(j, constraint(i, 0), -c);
      lp.set_a(j, constraint(i, 1), c);
    }
  }
  Solution s = CGAL::solve_linear_program(lp, ET());
  if(s.is_infeasible()) std::cout << "No such diet.\n";
  else std::cout << std::fixed << std::setprecision(0) << std::floor(CGAL::to_double(s.objective_value())) << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int n, m;
  while(fp >> n >> m && (n || m)) testcase(n, m);
  return 0;
}