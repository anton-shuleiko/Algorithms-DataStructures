#include "DijsktraVisitor.hpp"
#include <algorithm>

namespace traverses {
template <typename Vertex, class Graph,
          class Visitor>
class Dijsktra {
 public:
  Dijsktra(Vertex start, Graph& graph, Visitor& visitor ) {
    for(size_t i = 0; i < graph.GetVerticesNumber(); ++i){
      visitor.distances[i] = 2009000999;
      visitor.is_visited[i] = false;
    }
    visitor.distances[start] = 0;
    visitor.queue.push(std::make_pair(visitor.distances[start], start));
    Algo(start, graph, visitor);
  }

  void Algo(Vertex vertex, Graph& graph, Visitor& visitor) {
    Vertex curr;
    while (!visitor.queue.empty()) {
      curr = visitor.queue.top().second;
      visitor.queue.pop();
      visitor.is_visited[curr] = true;

      for (const auto& edge : graph.GetEdges(curr)) {
        if (!visitor.is_visited[edge.Finish()] && visitor.distances[edge.Finish()] > visitor.distances[curr] + edge.Length()) {
          visitor.distances[edge.Finish()] =  visitor.distances[curr] + edge.Length();
          visitor.queue.push(std::make_pair(visitor.distances[edge.Finish()], edge.Finish()));
        }
      }

      while (!visitor.queue.empty() && visitor.is_visited[visitor.queue.top().second]) {
        visitor.queue.pop();
      }
    }
  }
};
}  // namespace traverses
