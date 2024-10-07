#include "GraphAdjacency.hpp"
#include <unordered_map>
#include <queue> 

namespace traverses::visitors{
  template<typename Vertex, typename Edge = graph::DefaultEdge<Vertex>>
  class DijsktraVisitor{
  public:
    ~DijsktraVisitor() = default;
    std::unordered_map<Vertex,size_t> distances;
    std::unordered_map<Vertex, bool> is_visited;
    std::unordered_map<Vertex, size_t> ancestors;
    std::priority_queue<std::pair<size_t, Vertex>, std::vector<std::pair<size_t, Vertex> >,
                        std::greater<std::pair<size_t, Vertex> > >
        queue;
    DijsktraVisitor(){}
};
}
