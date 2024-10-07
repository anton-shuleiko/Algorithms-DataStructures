#include <iostream>
#include <vector>

class Graph {
 public:
  size_t pnum = 0;
  std::vector<std::vector<size_t>> graph;
  std::vector<size_t> indicator;
  std::vector<std::vector<size_t>> squads;
  size_t count = 1;

  Graph(size_t n) {
    pnum = n;
    graph = std::vector<std::vector<size_t>>(pnum);
    indicator = std::vector<size_t>(pnum, 0);
  }

  void Dfs(size_t start) {
    if (indicator[start] != 0) {
      return;
    }
    indicator[start] = count;
    if (squads.size() == count - 1) {
      squads.push_back({start});
    } else {
      squads[count - 1].push_back(start);
    }
    for (size_t i : graph[start]) {
      if (indicator[i] == 0) {
        Dfs(i);
        count--;
      }
    }
    count++;
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
    graf.graph[v - 1].push_back(u - 1);
  }

  for (size_t i = 0; i < n; ++i) {
    graf.Dfs(i);
  }
  std::cout << graf.squads.size() << std::endl;
  for (std::vector<size_t> vec : graf.squads) {
    std::cout << vec.size() << std::endl;
    for (size_t sq : vec) {
      std::cout << sq + 1 << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}