#include <iostream>
#include <vector>

std::vector<std::vector<int64_t>> adj_matr;
std::vector<std::pair<int64_t,int64_t>> edges;
std::vector<bool> visited;
int64_t num_vertex;
int64_t num_edge;
int64_t res = 0;

int64_t DFS(int64_t start, int64_t target, int64_t mflow = INT64_MAX) {
  if (start == target) {
    return mflow;
  }
  visited[start] = true;
  for (int64_t vert = 0; vert < num_vertex; ++vert) {
    if (!visited[vert] && adj_matr[start][vert] > 0) {
      int64_t flow = DFS(vert, target, std::min(mflow, adj_matr[start][vert]));
      if (flow > 0) {
        adj_matr[vert][start] += flow;
        adj_matr[start][vert] -= flow;
        return flow;
      }
    }
  }
  return 0;
}

int64_t MaxFlow(int64_t start, int64_t target) {
  visited.assign(visited.size(), false);
  int64_t flow = DFS(start - 1, target - 1);
  if (flow != 0) {
    MaxFlow(start, target);
  }
  res += flow;

  return res;
}

int main() {
  std::cin >> num_vertex >> num_edge;
  visited.resize(num_vertex);
  adj_matr.resize(num_vertex, std::vector<int64_t>(num_vertex, 0));
  int64_t first;
  int64_t second;
  int64_t capacity;
  for (int64_t i = 0; i < num_edge; ++i) {
    std::cin >> first >> second >> capacity;
    adj_matr[first - 1][second - 1] = capacity;
    edges.push_back({second-1,first-1});
  }
  MaxFlow(1, num_vertex);
  std::cout << res << std::endl;

  return 0;
}
