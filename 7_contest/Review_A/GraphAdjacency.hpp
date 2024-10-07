#include "AbstractGraph.hpp"

namespace graph {

template <typename Vertex = size_t, typename Edge = DefaultEdge<Vertex>>
class AdjacencyListGraph : public AbstractGraph<Vertex, Edge> {
 public:

  AdjacencyListGraph(size_t vertices_num, size_t edges_num) : AbstractGraph<Vertex, Edge>(vertices_num, edges_num) {}

  std::vector<Edge>& GetEdges(const Vertex& vertex) final {
    return list_[vertex];
  }

  void AddEdges(const Vertex& vertex, const Edge& edge) {
    list_[vertex].push_back(edge);
  }
private:
  std::unordered_map<Vertex, std::vector<Edge>> list_;
};
}
