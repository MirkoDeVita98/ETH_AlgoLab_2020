#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it; // Iterator

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

std::istream & fp = std::cin;

long right_bin_search(long L, long R, const std::function<bool(long)> &predicate) {
  while (L < R) {
    long mid = (L + R)/2;
    if (predicate(mid)) L = mid + 1;
    else R = mid;
  }
  return L - 1;
}

void testcase(){
  int c,g,b,k,a; fp >> c >> g >> b >> k >> a;
  
  graph G(c);
  auto c_map = boost::get(boost::edge_capacity, G);
  edge_adder adder(G);
  
  for(int i = 0; i < g; ++i){
    int x, y, d, e; fp >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }
  
  auto source = boost::add_vertex(G);
  adder.add_edge(source, k, std::numeric_limits<long>::max(), 0);
  auto src_edge = boost::edge(source, k, G).first;
  
  boost::successive_shortest_path_nonnegative_weights(G, source, a);
  const auto rc_map = boost::get(boost::edge_residual_capacity, G);
  long max_luggages = c_map[src_edge] - rc_map[src_edge] + 1;
  
  auto predicate = [&](long mid) {
    c_map[src_edge] = mid;

    boost::successive_shortest_path_nonnegative_weights(G, source, a);

    return boost::find_flow_cost(G) <= b;
  };
  
  std::cout << right_bin_search(0, max_luggages, predicate) << "\n";
  
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}