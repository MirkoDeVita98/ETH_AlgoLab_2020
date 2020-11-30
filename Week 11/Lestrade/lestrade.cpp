#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>         Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Point                                        Point;


std::istream & fp = std::cin;

void testcase(){
  
  int z, u ,v ,w, a, g; fp >> z >> u >> v >> w >> a >> g;
  
  std::vector<int> where(g);
  std::vector<int> who(g);
  std::vector<int> how(g);
  std::vector< std::pair<Point,int> > gang;
  gang.reserve(g);
  for (int i = 0; i < g; ++i) {
    int x, y;
    fp >> x >> y >> where[i] >> who[i] >> how[i]; 
    gang.push_back(std::make_pair(Point(x,y),i));
  }
  
  Triangulation t; 
  t.insert(gang.begin(), gang.end());
  
  std::vector<int> cost(g, std::numeric_limits<int>::max());
  for (int i = 0; i < a; ++i) {
    int x, y, z_i;
    fp >> x >> y >> z_i; 
    auto near_g = t.nearest_vertex(Point(x, y)) -> info();
    cost[near_g] = std::min(z_i, cost[near_g]);
  }
  
  Program lp (CGAL::SMALLER, true, 0, true, 24);

  int h = 0;
  for(int i = 0; i < g; ++i){
    if(cost[i] == std::numeric_limits<int>::max()) continue;
    
    lp.set_a(h, 0, -where[i]);
    lp.set_a(h, 1, -who[i]);
    lp.set_a(h, 2, -how[i]);
    lp.set_c(h, cost[i]);
    
    ++h;
  }
  lp.set_b(0, -u);
  lp.set_b(1, -v);
  lp.set_b(2, -w);
  
  Solution s = CGAL::solve_linear_program(lp, ET()); 

  if (s.objective_value() > z || s.is_infeasible()) std::cout << "H\n";
  else std::cout << "L\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}