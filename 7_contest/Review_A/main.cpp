#include "Dijsktra.hpp"

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
      graph.AddEdges(first,graph::DefaultEdge(first, second, len));
      graph.AddEdges(second,graph::DefaultEdge(second, first, len));
    }

    size_t start;
    std::cin >> start;
    traverses::Dijsktra(start, graph,visitor);

    for(size_t j = 0 ; j < visitor.distances.size(); ++j){
        std::cout << visitor.distances[j]<< ' ';
    }
    std::cout << std::endl;
  }
}