#include <iostream>
#include "AbstractGraph.hpp"

namespace graph{
  template <typename Vertex = size_t, typename Edge = std::pair<Vertex, Vertex>>
  class Tree {
  public:
    Tree() {
      weight_ = 0;
    }
    Tree(size_t weight, std::vector<std::pair<Vertex,Vertex>> mst): weight_(weight),  mst_(mst){
    }
    void AddEdges(const Edge& edge) {
      mst_.push_back(edge);
    }
    size_t& Weight(){
      return weight_;
    }
  private:
    size_t weight_ = 0;
    std::vector<std::pair<Vertex,Vertex>> mst_;
  };
}