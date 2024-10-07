#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 public:
  size_t pnum = 0;
  std::vector<std::vector<size_t>> graph;
  std::vector<size_t> indicator;
  std::vector<size_t> res;

  Graph(size_t n) {
    pnum = n;
    graph = std::vector<std::vector<size_t>>(pnum);
    indicator = std::vector<size_t>(pnum, 0);
  }

  bool Dfs(size_t start) {
    indicator[start] = 1;
    for (size_t i : graph[start]) {
      if (indicator[i] == 0) {
        if(Dfs(i)){
          return true;
        }
      }
      if (indicator[i] == 1) {
        return true;
      }
    }
    res.push_back(start);
    indicator[start] = 2;
    return false;
  }

  bool TopSort(){
    for(size_t i = 0 ; i < pnum; ++i){
      if(indicator[i] == 0){
        if(Dfs(i)){
          return false;
        }
      }
    }
    std::reverse(res.begin(), res.end());
    return true;
  }
};

int main() {
  size_t n, m;
  std::cin >> n >> m;

  Graph graf = Graph(n);

  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    std::cin >> u >> v;
    graf.graph[u - 1].push_back(v - 1);
  }

  if(graf.TopSort()){
    for(size_t r: graf.res){
      std::cout << r + 1 << " ";
    }
  }else{
    std::cout << -1 ;
  }
  return 0;
}