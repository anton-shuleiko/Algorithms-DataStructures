#include <iostream>
#include <vector>

class Graph {
 public:
  const int64_t kInf = INT64_MAX;
  struct Edge {
    int64_t first = 0;
    int64_t second = 0;
    int64_t cap = 0;
    int64_t flow = 0;
  };

  int64_t vert_num = 0;
  int64_t start = 0;
  int64_t target = 0;
  std::vector<int64_t> dist;
  std::vector<int64_t> ptr;
  std::vector<int64_t> queue;
  std::vector<Edge> edges;
  std::vector<std::vector<int64_t>> adj_list;

  Graph(int64_t num) : vert_num(num), start(0), target(vert_num - 1) {
    dist.resize(vert_num);
    ptr.resize(vert_num);
    queue.resize(vert_num);
    adj_list.resize(vert_num);
    
  }

  void Add(int64_t first, int64_t second, int64_t cap) {
    adj_list[first].push_back(static_cast<int64_t>(edges.size()));
    edges.push_back({first, second, cap, 0});
    adj_list[second].push_back(static_cast<int64_t>(edges.size()));
    edges.push_back({second, first, 0, 0});
  }

  bool Bfs() {
    int64_t qh = 0;
    int64_t qt = 0;
    queue[qt++] = start;
    dist.assign(vert_num, -1);
    dist[start] = 0;
    while (qh < qt && dist[target] == -1) {
      int64_t vert = queue[qh++];
      for (size_t i = 0; i < adj_list[vert].size(); ++i) {
        int64_t id = adj_list[vert][i];
        int64_t to = edges[id].second;
        if (dist[to] == -1 && edges[id].flow < edges[id].cap) {
          queue[qt++] = to;
          dist[to] = dist[vert] + 1;
        }
      }
    }
    return dist[target] != -1;
  }

  int64_t Dfs(int64_t vert, int64_t flow) {
    if (flow == 0) {
      return 0;
    }
    if (vert == target) {
      return flow;
    }
    for (; ptr[vert] < static_cast<int64_t>(adj_list[vert].size());
         ++ptr[vert]) {
      int64_t id = adj_list[vert][ptr[vert]];
      int64_t to = edges[id].second;
      if (dist[to] != dist[vert] + 1) {
        continue;
      }
      int64_t pushed = Dfs(to, std::min(flow, edges[id].cap - edges[id].flow));
      if (pushed != 0) {
        edges[id].flow += pushed;
        edges[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  int64_t Dinic() {
    int64_t flow = 0;
    for (;;) {
      if (!Bfs()) {
        break;
      }
      ptr.assign(vert_num, 0);
      while (int64_t pushed = Dfs(start, kInf)) {
        flow += pushed;
      }
    }
    return flow;
  }
};

void Work() {
  int64_t vert_num = 0;
  int64_t edge_num = 0;
  std::cin >> vert_num >> edge_num;
  Graph graph(vert_num);
  for (int64_t i = 0; i < edge_num; ++i) {
    int64_t fst = 0;
    int64_t scnd = 0;
    int64_t cap = 0;
    std::cin >> fst >> scnd >> cap;
    graph.Add(fst - 1, scnd - 1, cap);
  }
  std::cout << graph.Dinic() << std::endl;
  for (size_t i = 0; i < graph.edges.size(); i += 2) {
    std::cout << graph.edges[i].flow << std::endl;
  }
}

int main() {
  Work();
  return 0;
}
