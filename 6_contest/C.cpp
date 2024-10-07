#include <iostream>
#include <vector>

class Graph {
 public:
  size_t pnum = 0;
  std::vector<std::vector<size_t>> graph;
  std::vector<size_t> indicator;
  std::vector<size_t> cycle;

  Graph(size_t n) {
    pnum = n;
    graph = std::vector<std::vector<size_t>>(pnum);
    indicator = std::vector<size_t>(pnum, 0);
  }

  void SetCycle(size_t start) {
    indicator[start] = 1;
    for (size_t i : graph[start]) {
      if (indicator[i] == 0) {
        SetCycle(i);
      }
      if (indicator[i] == 1) {
        cycle.push_back(i + 1);
        indicator[i] = 2;
        return;
      }
    }
    
  }

  void Print() {
    for (size_t i = 0; i < pnum; ++i) {
      SetCycle(i);
      if (cycle.size() > 1) {
        std::cout << "YES" << std::endl;
        for (int j = cycle.size(); j >= 0; --j) {
          std::cout << cycle[j] << " ";
        }
        return;
      }

  }
    std::cout << "NO" << std::endl;
  }
};

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Graph graf = Graph(n);

  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    std::cin >> u >> v;
    if (u == v) {
      std::cout << "YES" << std::endl;
      std::cout << u;
      return 0;
    }
    graf.graph[u - 1].push_back(v - 1);
  }
  graf.Print();
  return 0;
}