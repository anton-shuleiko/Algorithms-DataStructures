#ifndef HEADER_FILE_NAME_H
#define HEADER_FILE_NAME_H
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace graph {
template <typename Vertex, typename Edge>
class AbstractGraph {
 public:
  using VertexType = Vertex;
  using EdgeType = Edge;

  explicit AbstractGraph(size_t vertices_num, size_t edges_num = 0)
      : vertices_number_(vertices_num), edges_number_(edges_num) {}

  size_t GetVerticesNumber() const { return vertices_number_; }
  size_t GetEdgesNumber() const { return edges_number_; }

 protected:
  size_t vertices_number_ = 0;
  size_t edges_number_ = 0;
};
}  // namespace graph
#endif