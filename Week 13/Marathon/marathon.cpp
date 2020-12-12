///2
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;

long right_bin_search(long L, long R, const std::function<bool(long)> &predicate) {
  while (L < R) {
    long mid = (L + R)/2;
    if (predicate(mid)) L = mid + 1;
    else R = mid;
  }
  return L - 1;
}

long min_dist(const weighted_graph &G, int s, int f) {
  int n = boost::num_vertices(G);
  std::vector<long> dist_map(n);

  boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[f];
}


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

void testcase(){
  int n, m, s ,f; fp >> n >> m >> s >> f;
  graph G(n);
  
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  
  weighted_graph G_dijkstra(n);
  auto w_map = boost::get(boost::edge_weight, G_dijkstra);
  
  for(int i = 0; i < m; ++i){
    int a, b, c, d; fp >> a >> b >> c >> d;
    if(a != b){
      adder.add_edge(a, b, c, d);
      adder.add_edge(b, a, c, d);
      auto e = boost::add_edge(a, b, G_dijkstra).first;
      w_map[e] = d;
    } 
  }

  auto source = boost::add_vertex(G);
  adder.add_edge(source, s, std::numeric_limits<long>::max(), 0);
  auto src_edge = boost::edge(source, s, G).first;
  boost::successive_shortest_path_nonnegative_weights(G, source, f);
  const auto rc_map = boost::get(boost::edge_residual_capacity, G);
  long max_athletes = c_map[src_edge] - rc_map[src_edge] + 1;

  long bound_dist = min_dist(G_dijkstra, s, f);
  
  auto predicate = [&](long mid) {
    c_map[src_edge] = mid;

    boost::successive_shortest_path_nonnegative_weights(G, source, f);
    
    long s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }

    return boost::find_flow_cost(G) <= bound_dist * s_flow;
  };
  
  std::cout << right_bin_search(0, max_athletes, predicate) << "\n";

}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}