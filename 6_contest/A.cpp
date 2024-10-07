#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace graph {
template <typename T>
struct DefaultEdge : std::pair<T, T> {
  DefaultEdge(const T& first, const T& second)
      : std::pair<T, T>(first, second) {}
  using BaseClass = std::pair<T, T>;
  const T& Start() const { return BaseClass::first; }
  const T& Finish() const { return BaseClass::second; }
};

template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;

  explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}
  size_t GetVerticesNumber() const { return vertices_number_; }
  size_t GetEdgesNumber() const { return edges_number_; }

  virtual std::vector<int> GetNeighbours(const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};
}  // namespace graph

namespace graph {
template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  std::vector<int> t_in;
  std::vector<bool> used;
  std::vector<int> ret;
  std::vector<int> res;
  int num_point;

  AdjacencyListGraph(size_t vertices_num, const std::vector<Edge>& edges)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges.size()) {
    t_in.resize(vertices_num + 1);
    ret.resize(vertices_num + 1);
    used.resize(vertices_num + 1);
    list_.resize(vertices_num + 1);
    num_point = vertices_num;

    for (const auto& edge : edges) {
      list_[edge.first].push_back(edge.second);
      list_[edge.second].push_back(edge.first);
    }
  }

  std::vector<Vertex> GetNeighbours(const Vertex& vertex) final {
    return list_[vertex];
  }

 private:
  std::vector<std::vector<Vertex>> list_;
};
}  // namespace graph

void Print(std::vector<int> res, std::vector<int> dist, int point_t);

namespace traverses {
template <class Graph, class Vertex, class Visitor>
void Bfs(Graph& graph, Vertex point_s, Visitor point_t) {
  std::queue<int> bfs_q;
  std::vector<int> dist(graph.num_point + 1, -1);
  dist[point_s] = 0;
  std::vector<int> res(graph.num_point + 1, -1);
  bfs_q.push(point_s);
  while (!bfs_q.empty()) {
    int cur = bfs_q.front();
    bfs_q.pop();
    for (int to : graph.GetNeighbours(cur)) {
      if (dist[to] == -1) {
        dist[to] = dist[cur] + 1;
        res[to] = cur;
        bfs_q.push(to);
      }
    }
  }
  if (dist[point_t] > -1) {
    Print(res, dist, point_t);
  } else {
    std::cout << -1;
  }
}
}  // namespace traverses

void Print(std::vector<int> res, std::vector<int> dist, int point_t) {
  std::cout << dist[point_t] << "\n";
  int to = res[point_t];
  std::vector<int> path;
  while (to != -1) {
    path.push_back(to);
    to = res[to];
  }
  for (int i = path.size() - 1; i >= 0; --i) {
    std::cout << path[i] << " ";
  }
  std::cout << point_t;
}

namespace traverses {
template <class Graph, class Vertex, class Visitor>
void DFS(Graph& graph, Vertex point, Visitor parent = -1) {
  graph.t_in[point] = graph.timer++;
  graph.ret[point] = graph.t_in[point];
  graph.used[point] = true;
  for (auto& to : graph.GetNeighbours(point)) {
    if (to.second == parent) {
      continue;
    }
    if (graph.used[to.first]) {
      graph.ret[point] = std::min(graph.ret[point], graph.t_in[to.first]);
    } else {
      DFS(graph, to.first, to.second);
      graph.ret[point] = std::min(graph.ret[point], graph.ret[to.first]);
      if (graph.ret[to.first] == graph.t_in[to.first]) {
        graph.res.push_back(to.second);
      }
    }
  }
}
}  // namespace traverses

void Print(std::vector<int> res) {
  std::cout << res.size() << "\n";
  for (int to : res) {
    std::cout << to << "\n";
  }
}


namespace traverses::visitors {
template <class Vertex, class Edge>
class BfsVisitor {
 public:
  virtual void TreeEdge(const Edge&) = 0;
  virtual ~BfsVisitor() = default;
};
}  // namespace traverses::visitors

namespace traverses::visitors {
template <class Vertex, class Edge>
class AncestorBfsVisitor : BfsVisitor<Vertex, Edge> {
 public:
  virtual void TreeEdge(const Edge& edge) {
    ancestors_[edge.Finish()] = edge.Start();
  }

  std::unordered_map<Vertex, Vertex> GetMap() const { return ancestors_; }

  virtual ~AncestorBfsVisitor() = default;

 private:
  std::unordered_map<Vertex, Vertex> ancestors_;
};
}  // namespace traverses::visitors

int main() {
  int number_point, number_country, point_s, point_t;

  std::cin >> number_point >> number_country >> point_s >> point_t;

  std::vector<graph::DefaultEdge<int>> edges;

  for (int i = 0; i < number_country; ++i) {
    int parent, child;

    std::cin >> parent >> child;

    graph::DefaultEdge<int> edge(parent, child);
    edges.push_back(edge);
  }

  graph::AdjacencyListGraph<int, graph::DefaultEdge<int>> graph(number_point,
                                                                edges);

  traverses::Bfs<graph::AdjacencyListGraph<int, graph::DefaultEdge<int>>, int,
                 int>(graph, point_s, point_t);
}
