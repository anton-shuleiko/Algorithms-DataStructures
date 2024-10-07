#include "AbstractGraph.hpp"

namespace graph {
template <typename Vertex = size_t, typename Edge = std::pair<Vertex, size_t>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:
  AdjacencyListGraph(size_t vertices_num, size_t edges_num)
      : AbstractGraph<Vertex, Edge>(vertices_num, edges_num) {}

  std::vector<Edge>& GetEdges(const Vertex& vertex) { return list_[vertex]; }

  void AddEdges(std::pair<size_t, std::pair<Vertex, Vertex>> edge) {
    list_[edge.second.first].push_back({edge.second.second, edge.first});
    list_[edge.second.second].push_back({edge.second.first, edge.first});
  }

 private:
  std::unordered_map<Vertex, std::vector<Edge>> list_;
};
}  // namespace graph
