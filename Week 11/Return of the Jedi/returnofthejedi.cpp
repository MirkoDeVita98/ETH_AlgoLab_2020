///3
#include <bits/stdc++.h>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator oe;
typedef boost::graph_traits<weighted_graph>::edge_iterator EdgeIt;  

typedef std::pair<int, int> iPair;

struct w_edge{
  int u;
  int v;
  int w;
  
  bool operator <(const w_edge &that) const{
    return w > that.w || (w == that.w && v < that.v);
  }
};


std::istream & fp = std::cin;


void prim(std::vector<int> & parent, const weighted_graph & G,const weight_map & weights, int s){
  
  int n = parent.size() - 1;
  
  std::vector< std::vector<long> > _d(n + 1, std::vector<long> (n + 1));

  #define d(u, v) (_d[std::min(u, v)][std::max(u, v)])

  
  std::priority_queue< w_edge > pq; 
  std::vector<bool> inMST(n + 1, false); 
  
  oe e_beg, e_end;

  for (boost::tie(e_beg, e_end) = boost::out_edges(s, G); e_beg != e_end; ++e_beg) {
    int v = boost::target(*e_beg, G);
    pq.push({s, v, weights[*e_beg]});
  }
  
  for(int i = 1; i <= n; ++i) d(i, i) = 0;
  
  inMST[s] = true;
  
  long cost = 0;
  
  while (!pq.empty()) { 
    w_edge e = pq.top();
    pq.pop();
    
    if (inMST[e.v]) continue; 
    inMST[e.v] = true;
    parent[e.v] = e.u;

    d(e.v, e.u) = e.w;
    cost += e.w;
    
    for(int i = 1; i <= n; ++i){
      if(inMST[i] && i != e.v) d(e.v, i) = std::max(d(e.u, i), d(e.u, e.v));
    }
    
    for (boost::tie(e_beg, e_end) = boost::out_edges(e.v, G); e_beg != e_end; ++e_beg) {
      int neighbor = boost::target(*e_beg, G);
      
      if (!inMST[neighbor]) { 
        pq.push({e.v, neighbor, weights[*e_beg]}); 
      }
    }
  }
  
  long min_diff = std::numeric_limits<long>::max();
  EdgeIt  e_b, e_e;
  for (boost::tie(e_b, e_e) = boost::edges(G); e_b != e_e; ++e_b){
    int u = boost::source(*e_b, G);
    int v = boost::target(*e_b, G);
    if(parent[u] != v && parent[v] != u){
      assert(d(u, v) >= 1);
      min_diff = std::min(min_diff, weights[*e_b] - d(u, v));
    }
  }
  
  std::cout << cost + min_diff << "\n";
  
}

void testcase(){
  int n, i; fp >> n >> i;
  
  weighted_graph G(n + 1);
  weight_map weights = boost::get(boost::edge_weight, G);
  
  for(int j = 1; j < n; ++j){
    for(int k = 1; k <= n - j; ++k){
      int w; fp >> w;
      edge_desc e = boost::add_edge(j, k + j, G).first;
      weights[e] = w;
    }
  }
  
  std::vector<int> parent(n + 1, -1);
  prim(parent, G, weights, i);
  
}

int main(int argc,const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
}