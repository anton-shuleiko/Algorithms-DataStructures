#include "Algos.hpp"

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t vert_num = 0;
  size_t edge_num = 0;
  std::cin >> vert_num >> edge_num;
  Algos alg(vert_num, edge_num);
  graph::Graph<size_t> gph(vert_num, edge_num);

  graph::AdjacencyListGraph<size_t> grph(vert_num, edge_num);
  for (size_t i = 0; i < edge_num; ++i) {
    size_t x = 0;
    size_t y = 0;
    size_t z = 0;
    std::cin >> x >> y >> z;
    gph.AddEdge({z, {x - 1, y - 1}});
    grph.AddEdges({z, {x - 1, y - 1}});
  }
  std::cout << alg.Kruskal(gph).Weight() << std::endl;
  // std::cout << alg.Prim(grph).Weight()<<std::endl;
}
