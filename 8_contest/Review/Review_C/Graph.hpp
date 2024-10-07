#include <algorithm>

#include "AbstractGraph.hpp"

namespace graph {
template <typename Vertex = size_t,
          typename Edge = std::pair<size_t, std::pair<Vertex, Vertex>>>
class Graph : public AbstractGraph<Vertex, Edge> {
 public:
  Graph(size_t vertices_num, size_t edges_num)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges_num) {}
  void AddEdge(Edge edge) { graph_.push_back(edge); }
  void Sort() { std::sort(graph_.begin(), graph_.end()); }
  size_t Len(size_t index) { return graph_[index].first; }
  Vertex First(size_t index) { return graph_[index].second.first; }
  Vertex Second(size_t index) const { return graph_[index].second.second; }
  const std::pair<Vertex, Vertex> Both(size_t index) const {
    return graph_[index].second;
  }
  Edge& operator[](size_t i) { return graph_[i]; }

 private:
  std::vector<Edge> graph_;
};

}  // namespace graph