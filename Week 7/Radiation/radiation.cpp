#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpzf ET;

typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

std::istream & fp = std::cin;

struct cell{
  int x;
  int y;
  int z;
};

void testcase(){
  int h, t; fp >> h >> t;
  
  std::vector< cell > healthy(h);
  
  for(int i = 0; i < h; ++i){
    fp >> healthy[i].x;
    fp >> healthy[i].y;
    fp >> healthy[i].z;
  }
  
  std::vector< cell > tumor(t);
  
  for(int i = 0; i < t; ++i){
    fp >> tumor[i].x;
    fp >> tumor[i].y;
    fp >> tumor[i].z;
  }
  
  if(h == 0 || t == 0){
    std::cout << "0\n";
    return;
  }
  
  const int r = 0;
  
  for(int d = 1; d <= 30; ++d){
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    
    for(int v = 0; v < h; ++v){
      int a = 1;
      ET x = 1;
      for(int i = 0; i <= d; ++i){
        ET y = 1;
        for(int j = 0; j <= d - i; ++j){
          ET z = 1;
          for(int k = 0; k <= d - i - j; ++k){
            lp.set_a(a, v, x*y*z);
            ++a;
            z *= healthy[v].z;
          }
          lp.set_a(r, v, 1);
          lp.set_b(v, 0);
          //lp.set_b(v, -1);
          y *= healthy[v].y;
        }
        x *= healthy[v].x;
      }
    }
    
    for(int v = 0; v < t; ++v){
      int a = 1;
      ET x = 1;
      for(int i = 0; i <= d; ++i){
        ET y = 1;
        for(int j = 0; j <= d - i; ++j){
          ET z = 1;
          for(int k = 0; k <= d - i - j; ++k){
            lp.set_a(a, v + h, -x*y*z);
            ++a;
            z *= tumor[v].z;
          }
          lp.set_a(r, v + h, 1);
          lp.set_b(v + h, 0);
          //lp.set_b(v + h, -1);
          y *= tumor[v].y;
        }
        x *= tumor[v].x;
      }
    }
    
    lp.set_l(r, true, 1);
    lp.set_c(r, 1);
    
    CGAL::Quadratic_program_options options; 
    options.set_pricing_strategy(CGAL::QP_BLAND);
    Solution s = CGAL::solve_linear_program(lp, ET(), options);
    
    if(s.is_optimal()){
      std::cout << d << "\n";
      return;
    }
    
    
  }
  
  std::cout << "Impossible!\n";
  
}

int main(int argc, const char* argv[]){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0); std::cout.tie(0);
  
  int t; fp >> t;
  
  while(t--) testcase();
  
}