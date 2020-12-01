#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>


typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

void testcase(){
  long x, y, n; fp >> x >> y >> n;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  const int p_x = 0;
  const int p_y = 1;
  const int t = 2;
  Solution s;

  for(long i = 0; i < n; ++i){
    long a,b,c,v; fp >> a >> b >> c >> v;

    lp.set_a(t, i,  v*std::sqrt(a*a + b*b));
    
    if(a*x+ b*y + c > 0){
      lp.set_a(p_x, i,  -a);
      lp.set_a(p_y, i,  -b);
      lp.set_b(i, c);
    }
    else{
      lp.set_a(p_x, i,  a);
      lp.set_a(p_y, i,  b);
      lp.set_b(i, -c);
    }
  }
  
  lp.set_l(t, true, 1);
  
  lp.set_c(t, -1);
  
  s = CGAL::solve_linear_program(lp, ET());
  long value = -std::ceil(CGAL::to_double(s.objective_value()));
  std::cout << std::fixed << std::setprecision(0) << value << "\n";
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  
  while(t--) testcase();
  
  return 0;
}