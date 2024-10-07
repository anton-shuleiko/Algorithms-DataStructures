#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

namespace graph {
  template <typename T>
  struct DefaultEdge : std::pair<T, T> {
    T len = 0;
    DefaultEdge(const T& first, const T& second, const T& length) : std::pair<T, T>(first, second), len(length) {}
    using BaseClass = std::pair<T, T>;
    const T& Start() const { return BaseClass::first; }
    const T& Finish() const { return BaseClass::second; }
    const T& Length() const { return len;}
  };

  template <typename Vertex = int, typename Edge = DefaultEdge<Vertex>>
  class AbstractGraph {
  public:
    using VertexType = Vertex;
    using EdgeType = Edge;

    explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0) :
        vertices_number_(vertices_num), edges_number_(edges_num) {}

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
