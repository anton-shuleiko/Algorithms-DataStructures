#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

namespace graph {
template <typename T>
struct DefaultEdge : std::pair<T, T> {
  T len = 0;
  DefaultEdge(const T& first, const T& second, const T& length)
      : std::pair<T, T>(first, second), len(length) {}
  using BaseClass = std::pair<T, T>;
  const T& Start() const { return BaseClass::first; }
  const T& Finish() const { return BaseClass::second; }
  const T& Length() const { return len; }
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

  virtual std::vector<Edge>& GetEdges(const Vertex& vertex) = 0;

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};

template <typename Vertex = size_t, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, size_t edges_num)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges_num) {}

  std::vector<Edge>& GetEdges(const Vertex& vertex) final {
    return list_[vertex];
  }

  void AddEdges(const Vertex& vertex, const Edge& edge) {
    list_[vertex].push_back(edge);
  }

 private:
  std::unordered_map<Vertex, std::vector<Edge>> list_;
};

}  // namespace graph

namespace traverses {
namespace visitors {
template <typename Vertex, typename Edge = graph::DefaultEdge<Vertex>>
class DijsktraVisitor {
 public:
  ~DijsktraVisitor() = default;
  std::unordered_map<Vertex, size_t> distances;
  std::unordered_map<Vertex, bool> is_visited;
  std::unordered_map<Vertex, size_t> ancestors;
  std::priority_queue<std::pair<size_t, Vertex>,
                      std::vector<std::pair<size_t, Vertex>>,
                      std::greater<std::pair<size_t, Vertex>>>
      queue;
  DijsktraVisitor() {}
};
}  // namespace visitors
template <typename Vertex, class Graph, class Visitor>
class Dijsktra {
 public:
  Dijsktra(Vertex start, Graph& graph, Visitor& visitor) {
    for (size_t i = 0; i < graph.GetVerticesNumber(); ++i) {
      visitor.distances[i] = 2009000999;
      visitor.is_visited[i] = false;
    }
    visitor.distances[start] = 0;
    visitor.queue.push(std::make_pair(visitor.distances[start], start));
    Algo(graph, visitor);
  }

  void Algo(Graph& graph, Visitor& visitor) {
    Vertex curr;
    while (!visitor.queue.empty()) {
      curr = visitor.queue.top().second;
      visitor.queue.pop();
      visitor.is_visited[curr] = true;

      for (const auto& edge : graph.GetEdges(curr)) {
        if (!visitor.is_visited[edge.Finish()] &&
            visitor.distances[edge.Finish()] >
                visitor.distances[curr] + edge.Length()) {
          visitor.distances[edge.Finish()] =
              visitor.distances[curr] + edge.Length();
          visitor.queue.push(
              std::make_pair(visitor.distances[edge.Finish()], edge.Finish()));
        }
      }

      while (!visitor.queue.empty() &&
             visitor.is_visited[visitor.queue.top().second]) {
        visitor.queue.pop();
      }
    }
  }
};
}  // namespace traverses

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  size_t number;
  std::cin >> number;
  while (number != 0) {
    size_t n, m;
    std::cin >> n >> m;

    graph::AdjacencyListGraph<size_t> graph(n, m);
    traverses::visitors::DijsktraVisitor<size_t> visitor;
    for (size_t first, second, len, i = 0; i < m; ++i) {
      std::cin >> first >> second >> len;
      graph.AddEdges(first, graph::DefaultEdge(first, second, len));
      graph.AddEdges(second, graph::DefaultEdge(second, first, len));
    }

    size_t start;
    std::cin >> start;
    traverses::Dijsktra(start, graph, visitor);

    for (size_t j = 0; j < visitor.distances.size(); ++j) {
      std::cout << visitor.distances[j] << ' ';
    }
    std::cout << std::endl;
    --number;
  }
}