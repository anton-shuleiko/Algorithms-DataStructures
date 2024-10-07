#include <iostream>
#include <vector>

const size_t kMax = 30000;


class Graph {
 public:
  struct Vertex {
    private:
    size_t name_;
    size_t ancestor_;
    std::vector<size_t> related_;
    public:
    Vertex(size_t num) : name_(num), ancestor_(-1) {}

    void AddRelated(const size_t& v) { related_.push_back(v); }

    bool operator==(const Vertex& v) const { return name_ == v.name_; }
  };

    struct Edge {
        private:
        size_t first_;
        size_t second_;
        int len_;

        public:
        Edge(size_t first, size_t second, int weight)
            : first_(first), second_(second), len_(weight) {}

        int Length() { return len_; }
        size_t First() { return first_; }

        size_t Second() { return second_; }
    };
  std::vector<Edge> edges;
  size_t time = 0;
  std::vector<Vertex> list;

 
  Graph(size_t number) {
    for (size_t i = 0; i <= number; ++i) {
      list.emplace_back(i);
    }
  }

  size_t Size() const { return list.size() - 1; }

  void AddVertex(size_t first, size_t second) { list[first].AddRelated(second); }

  std::vector<Vertex>& GetList() { return list; }

  void Read(size_t size) {
    size_t first, second, weight;
    for (size_t i = 1; i <= size; ++i) {
      std::cin >> first >> second >> weight;
      AddVertex(first, second);
      edges.emplace_back(first, second, weight);
    }
  }

  friend void FordBellman(Graph& graph);
};

void FindMinAndPrint(Graph& graph, std::vector<std::vector<int>>& matrix){
  for (size_t i = 1; i <= graph.Size(); ++i) {
    int min = matrix[i][0];
    for (size_t j = 1; j <= graph.Size(); ++j) {
        min = ((min > matrix[i][j])? matrix[i][j] : min);
    }
    std::cout << min << ' ';
  }
  std::cout << '\n';
}

void FordBellman(Graph& graph) {
  
  std::vector<std::vector<int>> matrix(graph.Size() + 1,std::vector<int>(graph.Size() + 1, kMax));
  matrix[1][0] = 0;
  size_t i = 1;
  while(i <= graph.Size()){
    for (Graph::Edge elem : graph.edges) {
      if (matrix[elem.First()][i - 1] != kMax &&
          matrix[elem.Second()][i] >
              matrix[elem.First()][i - 1] + elem.Length()) {
        matrix[elem.Second()][i] =
            matrix[elem.First()][i - 1] + elem.Length();
      }
    }
    ++i;
  }

  FindMinAndPrint(graph,matrix);
}



int main() {
  size_t m = 0;
  size_t n = 0;
  std::cin >> m >> n;
  Graph graph(m);
  graph.Read(n);
  FordBellman(graph);
}
