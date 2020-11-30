#include <bits/stdc++.h>
#include <CGAL/QP_models.h> 
#include <CGAL/QP_functions.h> 
#include <CGAL/Gmpz.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

std::istream &fp = std::cin;

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation; 
typedef K::Point_2 Point;

#define x(i, j) ((m*i) + j)
#define supply(i) (i)
#define demand_less(j) (n + j)
#define demand_great(j) (n + j + m)
#define alcohol(j) (n + j + (2 * m))

void testcase(){
  int n, m, c; fp >> n >> m >> c;
  
  std::vector<int> s(n);
  std::vector<int> a(n);
  std::vector<Point> war(n);
  
  for(int i = 0; i < n; ++i){
    int x, y; 
    fp >> x >> y >> s[i] >> a[i];
    war[i] = {x, y};
  }
  
  Triangulation t1; 
  t1.insert(war.begin(), war.end());
  
  std::vector<int> d(m);
  std::vector<int> u(m);
  std::vector<Point> stad(m);
  
  for(int i = 0; i < m; ++i){
    int x, y; 
    fp >> x >> y >> d[i] >> u[i];
    stad[i] = {x, y};
  }
  
  Triangulation t2; 
  t2.insert(stad.begin(), stad.end());

  std::vector< std::vector<int> > r(n, std::vector<int>(m));
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      fp >> r[i][j];
    }
  }
  
  std::vector< std::vector<int> > t(n, std::vector<int>(m, 0));
  
  for(int i = 0; i < c; ++i){
    int x, y, r; fp >> x >> y >> r;
    Point p(x, y);
    K::FT sq_r = r*r;
    
    Triangulation::Vertex_handle v1 = t1.nearest_vertex(p);
    Triangulation::Vertex_handle v2 = t2.nearest_vertex(p);
    
    if(CGAL::squared_distance(v1 -> point(), p) > sq_r  && CGAL::squared_distance(v2 -> point(), p) > sq_r) continue;
    
    for(int w = 0; w < n; ++w){
      for(int st = 0; st < m; ++st){
        K::FT dist1 = CGAL::squared_distance(war[w], p);
        K::FT dist2 = CGAL::squared_distance(stad[st], p);
        if((dist1 <= sq_r && dist2 > sq_r) || (dist1 > sq_r && dist2 <= sq_r)) ++t[w][st];
      }
    }
  }
  
  Program lp (CGAL::SMALLER, false, 0, false, 0);
  
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      lp.set_c(x(i, j), t[i][j] - 100 * r[i][j]);
      lp.set_a(x(i, j), supply(i), 1);
    }
    lp.set_b(supply(i), s[i]);
  }
  
  for(int j = 0; j < m; ++j){
    for(int i = 0; i < n; ++i){
      lp.set_a(x(i, j), demand_less(j), 1);
      lp.set_a(x(i, j), demand_great(j), -1);
      lp.set_a(x(i, j), alcohol(j), a[i]);
    }
    lp.set_b(demand_less(j), d[j]);
    lp.set_b(demand_great(j), -d[j]);
    lp.set_b(alcohol(j), 100*u[j]);
  }
  
  Solution sol = CGAL::solve_nonnegative_linear_program(lp, ET());
  if (sol.is_infeasible()) std::cout << "RIOT!\n";
  else std::cout << std::setprecision(0) << std::fixed << floor(CGAL::to_double(-sol.objective_value()/100)) << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  
  int t; fp >> t;
  while(t--) testcase();
}