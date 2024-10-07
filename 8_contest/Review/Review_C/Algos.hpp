#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "Graph.hpp"
#include "GraphAdjacency.hpp"
#include "Tree.hpp"

template <typename Vertex = size_t>
class Algos {
 public:
  std::unordered_map<Vertex, Vertex> parent;
  std::unordered_map<Vertex, size_t> power;

  size_t vert_num = 0;

  Algos(size_t vert_num, size_t edge_num) {
    for (size_t i = 0; i < vert_num; ++i) {
      make_set(i);
    }
  }

  size_t find_set(Vertex vert) {
    return (vert == parent[vert]) ? vert
                                  : (parent[vert] = find_set(parent[vert]));
    ;
  }

  void make_set(Vertex vert) {
    parent[vert] = vert;
    power[vert] = 0;
  }

  void union_sets(Vertex a, Vertex b) {
    a = find_set(a);
    b = find_set(b);
    parent[a] = a != b ? b : parent[a];
  }

  graph::Tree<Vertex> Kruskal(graph::Graph<Vertex> grph) {
    graph::Tree<Vertex> mst;
    grph.Sort();
    for (size_t i = 0; i < grph.GetEdgesNumber(); ++i) {
      if (find_set(grph.First(i)) != find_set(grph.Second(i))) {
        mst.Weight() += grph.Len(i);
        mst.AddEdges(grph.Both(i));
        union_sets(grph.First(i), grph.Second(i));
      }
    }
    return mst;
  }

  graph::Tree<Vertex> Prim(graph::AdjacencyListGraph<Vertex> grph) {
    graph::Tree<Vertex> mst;
    std::unordered_map<Vertex, bool> used;
    std::priority_queue<std::pair<size_t, Vertex>,
                        std::vector<std::pair<size_t, Vertex>>,
                        std::greater<std::pair<size_t, Vertex>>>
        set;
    set.push(std::make_pair(0, 0));
    Vertex vertex = set.top().second;
    size_t weight = set.top().first;
    while (!set.empty()) {
      set.pop();
      if (used[vertex]) continue;
      mst.Weight() += weight;
      used[vertex] = true;
      for (auto to : grph.GetEdges(vertex)) {
        if (!used[to.first]) {
          set.push(std::make_pair(to.second, to.first));
        }
      }
      if (set.top().second != vertex) {
        mst.AddEdges({set.top().second, vertex});
      }

      vertex = set.top().second;
      weight = set.top().first;
    }
    return mst;
  }
};