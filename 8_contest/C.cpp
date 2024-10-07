#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

class Euristic {
 public:
  std::vector<size_t> parent;
  std::vector<size_t> power;
  size_t weight = 0;
  std::vector<std::pair<size_t,size_t>> mst;
  std::vector <std::pair<size_t,std::pair<size_t,size_t>>> graph;
  size_t size = 0;

  Euristic(size_t size) {
    parent.resize(size, 0);
    power.resize(size, 0);
    for (size_t i = 0; i < size; i++) {
      make_set(i);
    }
  }

  size_t find_set(size_t& v) {
    return (v == parent[v]) ? v : (parent[v] = find_set (parent[v]));;
  }

  void make_set(size_t v) {
    parent[v] = v;
    power[v] = 0;
  }

  void union_sets(size_t& a, size_t& b) {
    a = find_set(a);
    b = find_set(b);
    parent[a] = a!=b?b:parent[a];
  }

  void Cruscal(size_t requests){
    std::sort(graph.begin(),graph.end());
    for (size_t i=0; i<requests; ++i) {
      if (find_set(graph[i].second.first) != find_set(graph[i].second.second)) {
        weight += graph[i].first;
        mst.push_back(graph[i].second);
        union_sets(graph[i].second.first, graph[i].second.second);
      }
    }
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t size = 0;
  size_t requests = 0;
  std::cin >> size >> requests;
  Euristic trees(size);
  for (size_t i = 0; i < requests; ++i) {
    size_t x = 0;
    size_t y = 0;
    size_t z = 0;
    std::cin >> x >> y >> z;
    trees.graph.push_back({z,{x-1,y-1}});
  }
  trees.Cruscal(requests);
  std::cout << trees.weight<<std::endl;
  
}