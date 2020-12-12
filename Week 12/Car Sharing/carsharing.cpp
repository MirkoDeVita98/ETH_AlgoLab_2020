///5
#include <bits/stdc++.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/functional/hash.hpp>

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
  edge_desc add_edge(int from, int to, long capacity, long cost) {
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
    return e;
  }
};

std::istream & fp = std::cin;
typedef std::pair<edge_desc, int> request;

#define MAX_COST 100
#define MAX_CARS 1000

void testcase(){
  int n, S; fp >> n >> S;
  
  std::vector<int> cars(S + 1);
  int total_cars = 0;
  for(int i = 1; i <= S; ++i){
    fp >> cars[i];
    total_cars += cars[i];
  } 
  
  graph G;
  edge_adder adder(G);
  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  
  std::vector< request > requests;
  std::vector< std::map<long,long> > station_times(S + 1);
  int max_time = 0;
  
  for(int i = 0; i < n; ++i){
    int s, t, d, a, p; fp >> s >> t >> d >> a >> p;
    max_time = std::max(max_time, a);
    if(station_times[s].find(d) == std::end(station_times[s])){
      auto v = boost::add_vertex(G);
      station_times[s].insert({d, v});
    }
    if(station_times[t].find(a) == std::end(station_times[t])){
      auto v = boost::add_vertex(G);
      station_times[t].insert({a, v});
    }
    
    edge_desc e = adder.add_edge(station_times[s].find(d) -> second, station_times[t].find(a) -> second, 1, MAX_COST*(a-d) - p);
    requests.push_back({e, p});
  }
  
  for(int i = 1; i <= S; ++i){
    auto last = std::end(station_times[i]);
    for(auto it = station_times[i].begin(); it != std::end(station_times[i]); ++it){
      if(last == std::end(station_times[i])) adder.add_edge(source, it -> second, cars[i], 0);
      else adder.add_edge(last -> second , it -> second, MAX_CARS, MAX_COST * ((it -> first) - (last -> first)));
      last = it;
    }
    if(last != std::end(station_times[i])) adder.add_edge(last -> second , sink, MAX_CARS, MAX_COST * (max_time - (last -> first)));
  }

  
  boost::successive_shortest_path_nonnegative_weights(G, source, sink);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  long profit = 0;
  for (request &rq : requests) if(!rc_map[rq.first]) profit += rq.second;
  std::cout << profit << std::flush << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}