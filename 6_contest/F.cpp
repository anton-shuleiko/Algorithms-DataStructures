#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Graph {
 public:
  size_t pnum = 0;
  std::vector<std::vector<size_t>> graph;
  std::vector<size_t> indicator;
  std::vector<size_t> down;
  std::vector<size_t> up;
  std::vector<size_t> used_pnt;
  std::set<size_t> sochlen_points;
  size_t count = 1;

  Graph(size_t n) {
    pnum = n;
    graph = std::vector<std::vector<size_t>>(pnum);
    indicator = std::vector<size_t>(pnum, 0);
    down = std::vector<size_t>(pnum, 0);
    up = std::vector<size_t>(pnum, 0);
    used_pnt = std::vector<size_t>(pnum, 0);
  }

  void Dfs(size_t start, int parent = -1) {
    size_t children = 0;
    indicator[start] = 1;
    down[start] = up[start] = count++;
    for (size_t i : graph[start]) {
      if ((static_cast<int>(i) == parent)) {
        continue;
      }
      if (indicator[i] == 1) {
        up[start] = std::min(up[start], down[i]);
      } else {
        Dfs(i, start);
        up[start] = std::min(up[start], up[i]);
        if ((up[i] >= down[start]) && (parent != -1)) {
          if(used_pnt[start] == 0){
            sochlen_points.insert(start);
            used_pnt[start] = 1;
          }
        }
        children++;
      }
    }

    if ((parent == -1) && (children > 1)) {
      if(used_pnt[start] == 0){
            sochlen_points.insert(start);
            used_pnt[start] = 1;
      }
    }
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
  for (size_t i = 0; i < n; i++) {
    if (graf.indicator[i] == 0) {
      graf.Dfs(i);
    }
  }
  std::cout << graf.sochlen_points.size() << std::endl;
  for (size_t it : graf.sochlen_points) {
    std::cout << it + 1 << std::endl;
  }

  return 0;
}