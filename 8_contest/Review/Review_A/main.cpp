#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdio.h>

template<typename Vertrex = size_t, typename EdgeLen = size_t>
class Euristic {
 public:
  std::unordered_map<Vertrex, Vertrex> parent;
  std::unordered_map<Vertrex, EdgeLen> power;

  Euristic(size_t size) {
    for (size_t i = 0; i < size; i++) {
      make_set(i);
    }
  }

  size_t find_set(size_t& v) {
    size_t root = v;
    while (root != parent[root]) {
      root = parent[root];
    }
    while (v != root) {
      size_t p = parent[v];
      parent[v] = root;
      v = p;
    }
    return root;
  }

  void make_set(size_t v) {
    parent[v] = v;
    power[v] = 0;
  }

  void union_sets(size_t& a, size_t& b, size_t& pow) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (power[a] < power[b]) std::swap(a, b);
      parent[b] = a;
      power[a] += power[b] + pow;
      if (power[a] == power[b]) {
        power[a]+=pow;
      }
    } else {
      power[a] += pow;
    }
  }
};
template <typename Vertex = size_t, typename EdgeLen = size_t>
void Work(Euristic<Vertex,EdgeLen>& trees,size_t requests){
  for (size_t i = 0; i < requests; ++i) {
    size_t first = 0;
    std::cin >> first;
    if (first == 1) {
      size_t x = 0;
      size_t y = 0;
      size_t z = 0;
      std::cin >> x >> y >> z;
      x--;
      y--;
      trees.union_sets(x, y, z);
    } else {
      size_t x = 0;
      std::cin >> x;
      x--;
      printf("%zu\n", trees.power[trees.find_set(x)]);
    }
  }
}

void InputAndWork(){
  size_t size = 0;
  size_t requests = 0;
  std::cin >> size >> requests;
  Euristic trees(size);
  Work(trees,requests);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  InputAndWork();
}
