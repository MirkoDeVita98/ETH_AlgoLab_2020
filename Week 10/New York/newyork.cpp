#include <bits/stdc++.h>

std::istream & fp = std::cin;

typedef std::pair<int, int> iPair;

struct Critical_Point{
  int h;
  int parent = 0;
  std::vector<int> r;
};

void testcase(){
  int n, m, k; fp >> n >> m >> k;
  
  std::vector<Critical_Point> cpts(n);
  for(int i = 0; i < n; ++i){
    fp >> cpts[i].h;
  }
  
  for(int i = 1; i < n; ++i){
    int u, v; fp >> u >> v;
    cpts[u].r.push_back(v);
    cpts[v].parent = u; 
  }
  
  std::stack<int> st;
  std::set<iPair> T;
  st.push(0);
  int interval = 0;
  int first = 0;
  std::vector<bool> in_interval(n, false);
  std::set<int> journey;
  
  while(!st.empty()){
    int u = st.top();
    st.pop();
    
    in_interval[u] = true;
    T.insert({cpts[u].h, u});
    interval += 1;
    
    if(!T.empty() && interval == m && (T.rbegin() -> first - T.begin() -> first) <= k) journey.insert(first);
  
    //set the new first
    if(interval == m){
      interval -= 1;
      T.erase({cpts[first].h, first});
      in_interval[first] = false;
      
      for(int child : cpts[first].r){
        if(in_interval[child]){
          first = child;
          break;
        } 
      }
    }
    
    //if not leaf add children to the stack
    if(!cpts[u].r.empty()) for(int v : cpts[u].r) st.push(v);
    //if leaf move th interval back and set the st.top() to last
    else{
      while(!st.empty() && u != cpts[st.top()].parent){
        in_interval[u] = false;
        T.erase({cpts[u].h, u});
        
        //move the first back if necessary
        if(!in_interval[cpts[first].parent]){
          in_interval[cpts[first].parent] = true;
          first = cpts[first].parent;
          T.insert({cpts[first].h, first});
          interval += 1;
        }
      
        interval -= 1;
        u = cpts[u].parent;
      }
    }
  }
  
  if(!journey.empty()){
    for(int start : journey) std::cout << start << " ";
  }
  else std::cout << "Abort mission";
  
  std::cout << "\n";
}

int main(int argc, const char * argv[]){
  std::ios_base::sync_with_stdio(false);
  fp.tie(0);
  int t; fp >> t;
  while(t--) testcase();
  return 0;
}