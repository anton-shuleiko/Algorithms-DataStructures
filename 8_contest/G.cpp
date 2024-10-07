#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace sdt {
template <typename T>
using matrix = std::vector<std::vector<T>>;
};

class Graph {
 private:
  int64_t size_ = 0;
  int64_t sum_ = 0;
  sdt::matrix<int64_t> adj_;
  int64_t timer_ = 0;
  std::vector<int64_t> tout_;
  std::vector<int64_t> tin_;
  sdt::matrix<int64_t> up_;
  std::vector<int64_t> height_;
  int64_t len_ = 0;
  void DFS(int64_t v, int64_t p = 0) {
    tin_[v] = ++timer_;
    up_[v][0] = p;
    height_[v] = height_[p] + 1;
    for (int64_t i = 1; i <= len_; ++i) {
      up_[v][i] = up_[up_[v][i - 1]][i - 1];
    }
    for (auto u : adj_[v]) {
      if (u == p) {
        continue;
      }
      DFS(u, v);
    }
    tout_[v] = ++timer_;
  }
  bool ancestor(int64_t u, int64_t v) {
    return (tin_[u] <= tin_[v]) && (tout_[u] >= tout_[v]);
  }
  int Lca(int v, int u) {
    if (ancestor(v, u)) return v;
    if (ancestor(u, v)) return u;
    for (int l = len_; l >= 0; --l)
      if (!ancestor(up_[v][l], u)) v = up_[v][l];
    return up_[v][0];
  }
  int64_t lca(int64_t a, int64_t b) {
    if (height_[a] < height_[b]) std::swap(a, b);
    int diff = height_[a] - height_[b];
    for (int64_t i = len_ - 1; i >= 0; --i) {
      if ((1 << i) <= diff) {
        a = up_[a][i];
        diff -= (1 << i);
      }
    }
    if (a == b) {
      return a;
    }
    for (int64_t i = len_ - 1; i >= 0; --i) {
      if (up_[a][i] != up_[b][i]) {
        a = up_[a][i];
        b = up_[b][i];
      }
    }
    return up_[a][0];
  }

 public:
  int64_t member(int64_t x, int64_t y, int64_t z, int64_t a1, int64_t a2) {
    return (x * a1 + y * a2 + z) % size_;
  }
  void Compute() {
    int64_t a1, a2, x, y, z;
    std::cin >> a1 >> a2;
    std::cin >> x >> y >> z;
    sum_ = 0;
    sum_ += lca(a1, a2);
    int64_t prev = sum_;
    for (int i = 1; i < edge_count_; ++i) {
      a1 = member(x, y, z, a1, a2);
      a2 = member(x, y, z, a2, a1);
      int64_t ans = lca((a1 + prev) % size_, a2);
      prev = ans;
      sum_ += ans;
    }
    std::cout << sum_ << "\n";
  }
  void prepare() {
    tin_.resize(size_);
    tout_.resize(size_);
    height_.assign(size_, 0);
    timer_ = 0;
    len_ = 1;
    len_ = std::__lg(size_);
    // while ((1 << len_) <= size_) ++len_;
    up_.assign(size_, std::vector<int64_t>(len_ + 1));
    DFS(0);
  }
  Graph(int64_t size, const sdt::matrix<int64_t>& adj, int64_t edge) {
    adj_ = adj;
    size_ = size;
    prepare();
    edge_count_ = edge;
  }

 private:
  int64_t edge_count_ = 0;
};

void Requests() {
  int64_t n = 0, m = 0;
  std::cin >> n >> m;
  sdt::matrix<int64_t> adj(n);
  for (int64_t i = 1; i < n; ++i) {
    int64_t m;
    std::cin >> m;
    adj[i].push_back(m);
    adj[m].push_back(i);
  }
  Graph graph(n, adj, m);
  graph.Compute();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Requests();
  return 0;
}