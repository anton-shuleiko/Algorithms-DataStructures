#include <cmath>
#include <iostream>
#include <vector>

class Euristic {
 public:
  std::vector<std::vector<int>> graph;
  std::vector<int> depth;
  std::vector<std::vector<int>> d;
  int vertex_count = 0;

  Euristic(int vertex_num) {
    graph =  std::vector<std::vector<int>>(vertex_num + 1);
    d=std::vector<std::vector<int>>(vertex_num + 1);
    depth=std::vector<int>(vertex_num + 1);
    vertex_count = vertex_num;
    MakeSet();
  }

  void MakeSet(){
    for (int i = 0; i <= vertex_count; ++i) {
      d[i].resize(log2(vertex_count) + 1);
    }
  }
  void Add(int first, int second) {
    graph[first].push_back(second);
    graph[second].push_back(first);
  }

  void DFS(int vertex, int parent, int dpth) {
    d[vertex][0] = parent;
    depth[vertex] = dpth;
    int i = 1 ;
    while (i <= log2(vertex_count))  {
      d[vertex][i] = d[d[vertex][i - 1]][i - 1];
      ++i;
    }

    for (const auto& heir : graph[vertex]) {
      if (heir != parent) {
        DFS(heir, vertex, dpth + 1);
      }
    }
  }

  int LCA(int first, int second) {
    if (depth[first] < depth[second]) {
        first+= second;
        second = first-second;
        first -= second;
    }
    int i = log2(vertex_count);
    while (i >= 0) {
      if ( (int)(std::pow(2,i)) & depth[first] - depth[second] ) {
        first = d[first][i];
      }
       --i;
    }

    if (first == second) {
      return first;
    }

    int i = log2(vertex_count);
    while (i >= 0) {
      if (d[first][i] != d[second][i]) {
        first = d[first][i];
        second = d[second][i];
      }
      --i;
    }
    return d[first][0];
  }
};

int main() {
  int vertex_num;
  int num_request;
  int first;
  int second;

  std::cin >> vertex_num;

  Euristic tree(vertex_num);

  for (int i = 0; i < vertex_num - 1; ++i) {
    std::cin >> first >> second;
    tree.Add(first, second);
  }

  tree.DFS(1, 0, 0);

  std::cin >> num_request;

  for (int i = 0; i < num_request; ++i) {
    std::cin >> first >> second;
    std::cout << tree.depth[first] + tree.depth[second] - 2 * tree.depth[tree.LCA(first, second)] << std::endl;
  }

  return 0;
}