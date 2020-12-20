///2
#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

#define to_left(i) (i)
#define water_less_nob(i) (i + n)
#define water_great_nob(i) (i + (2*n))

#define to_right(i) (i + (3 * n))
#define water_less_comm(i) (i + (3 * n) + m)
#define water_great_comm(i) (i + (3 * n) + (2 * m))

#define constraint_lengths ((3 * n) + (3 * m))

void testcase(){
  int n, m; fp >> n >> m;
  long s; fp >> s;
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  const int a = 0; const int b = 1; const int c = 2;
  const int f = 3;
  const int max = 4;
  
  long sum_x = 0;
  long sum_y = 0;
  long sum_c = 0;
  
  for(int i = 0; i < n; ++i){
    int x, y; fp >> x >> y;
    sum_x -= x;
    sum_y -= y;
    sum_c -= 1;
    
    lp.set_a(a, to_left(i), x);
    lp.set_a(b, to_left(i), y);
    lp.set_a(c, to_left(i), 1);
    
    lp.set_a(b, water_less_nob(i), x);
    lp.set_a(a, water_less_nob(i), -y);
    lp.set_a(f, water_less_nob(i), 1);
    lp.set_a(max, water_less_nob(i), -1);
    
    lp.set_a(b, water_great_nob(i), -x);
    lp.set_a(a, water_great_nob(i), y);
    lp.set_a(f, water_great_nob(i), -1);
    lp.set_a(max, water_great_nob(i), -1);
  }
  
  for(int i = 0; i < m; ++i){
    int x, y; fp >> x >> y;
    sum_x += x;
    sum_y += y;
    sum_c += 1;
    
    lp.set_a(a, to_right(i), -x);
    lp.set_a(b, to_right(i), -y);
    lp.set_a(c, to_right(i), -1);
    
    lp.set_a(b, water_less_comm(i), x);
    lp.set_a(a, water_less_comm(i), -y);
    lp.set_a(f, water_less_comm(i), 1);
    lp.set_a(max, water_less_comm(i), -1);
    
    lp.set_a(b, water_great_comm(i), -x);
    lp.set_a(a, water_great_comm(i), y);
    lp.set_a(f, water_great_comm(i), -1);
    lp.set_a(max, water_great_comm(i), -1);
  }
  
  lp.set_l(a, true, 1);
  
  lp.set_c(max, 1);
  
  Solution sol = CGAL::solve_linear_program(lp, ET());
  if(sol.is_infeasible()){
    std::cout << "Yuck!" << "\n";
    return;
  }
  
  if(s == -1){
    std::cout << std::fixed << std::setprecision(0) <<  std::ceil(CGAL::to_double(sol.objective_value())) << "\n";
    return;
  }
  else if(s == 0){
    std::cout << "Bankrupt!" << "\n";
    return;
  }
  

  lp.set_a(a, constraint_lengths , sum_x);
  lp.set_a(b, constraint_lengths , sum_y);
  lp.set_a(c, constraint_lengths , sum_c);
  lp.set_b(constraint_lengths, s);
  
  //CGAL::Quadratic_program_options options; 
  //options.set_pricing_strategy(CGAL::QP_BLAND);
  sol = CGAL::solve_linear_program(lp, ET());
  
  if(sol.is_infeasible()){
    std::cout << "Bankrupt!" << "\n";
  }
  else{
    std::cout << std::fixed << std::setprecision(0) <<  std::ceil(CGAL::to_double(sol.objective_value())) << "\n";
  }
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}