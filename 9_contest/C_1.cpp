#include <iostream>
#include <queue>
#include <vector>
#include <set>

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
  std::vector<size_t> adj_ts;
  std::vector<bool> used_after;
  std::vector<std::vector<size_t>> another_list;
  std::vector<std::vector<size_t>> order;

  Graph(int64_t num) : vert_num(num), start(0), target(vert_num - 1) {
    dist.resize(vert_num);
    ptr.resize(vert_num);
    queue.resize(vert_num);
    adj_list.resize(vert_num);
    another_list.resize(vert_num, std::vector<size_t>(vert_num, 0));
    order.resize(vert_num, std::vector<size_t>(vert_num, 0));
  }

  void Add(int64_t first, int64_t second, int64_t cap) {
    adj_list[first].push_back(static_cast<int64_t>(edges.size()));
    edges.push_back({first, second, cap, 0});
    adj_list[second].push_back(static_cast<int64_t>(edges.size()));
    edges.push_back({second, first, 0, 0});
    another_list[first][second] = cap;
    another_list[second][first] = cap;
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
   void BFSAfterFF(size_t start) {
    used_after.assign(vert_num, false);
    std::queue<size_t> que;
    que.push(start);
    adj_ts.push_back(start);
    used_after[start] = true;
    while (!que.empty()) {
      size_t from_vert = que.front();
      que.pop();

      for (size_t to_vert = 0; to_vert < vert_num; ++to_vert) {
        if (!used_after[to_vert] &&
            another_list[from_vert][to_vert] > 0) {
          used_after[to_vert] = true;
          adj_ts.push_back(to_vert);
          que.push(to_vert);
        }
      }
    }
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
    graph.Add(fst-1, scnd-1, cap);
    fst--;
    scnd--;
    graph.order[fst][scnd] = i + 1;
    graph.order[scnd][fst] = i + 1;
  }
  int64_t ans =  graph.Dinic();

  //graph.BFSAfterFF(0);

  std::set<size_t> cut_edges;

  for (size_t i = 0; i < graph.adj_ts.size(); ++i) {
    for (size_t j = 0; j < graph.vert_num; ++j) {
      if (!graph.used_after[j] &&
          graph.adj_list[graph.adj_ts[i]][j] > 0) {
        cut_edges.insert(graph.order[graph.adj_ts[i]][j]);
      }
    }
  }

  std::cout << cut_edges.size() << " " << ans << std::endl;

  for (auto iter : cut_edges) {
    std::cout << iter << " ";
  }
}

int main() {
  Work();
  return 0;
}
