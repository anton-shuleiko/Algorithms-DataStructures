#include <iostream>
#include <limits>
#include <set>
#include <vector>

const int64_t kInf = std::numeric_limits<int64_t>::max();
class Graph {
  std::vector<std::vector<std::pair<int64_t, int64_t>>> neighbour_;
  std::vector<bool> ill_vertex_;
  std::vector<bool> is_visited_;
  std::vector<int64_t> virusarr_;
  std::vector<int64_t> distances_;
  int64_t size_ = 0;

 public:
  Graph(int64_t vnum) {
    neighbour_.resize(vnum + 1);
    size_ = vnum;
    for (int64_t i = 0; i <= vnum; ++i) {
      distances_.push_back(kInf);
      ill_vertex_.push_back(false);
      is_visited_.push_back(false);
    }
  }
  bool IsVisited(int64_t vertex) { return is_visited_[vertex]; }
  std::vector<bool>& GetIllVertices() { return ill_vertex_; }
  std::vector<int64_t>& GetVirus() { return virusarr_; }
  std::vector<std::pair<int64_t, int64_t>>& GetNeighbours(int64_t vertex) {
    return neighbour_[vertex];
  }

  int64_t Dijsktra(int64_t start, int64_t target) {
    std::vector<int64_t> dist(size_ + 1, kInf);
    dist[start] = 0;
    std::set<std::pair<int64_t, int64_t>> setpnt;
    setpnt.insert(std::make_pair(0, start));
    while (!setpnt.empty()) {
      int64_t temp_vert = setpnt.begin()->second;
      setpnt.erase(setpnt.begin());
      for (const auto& neighb : neighbour_[temp_vert]) {
        if (!ill_vertex_[neighb.first] &&
            dist[temp_vert] + neighb.second < dist[neighb.first]) {
          setpnt.erase(std::make_pair(dist[neighb.first], neighb.first));
          dist[neighb.first] = dist[temp_vert] + neighb.second;
          setpnt.insert(std::make_pair(dist[neighb.first], neighb.first));
        }
      }
    }
    return dist[target];
  }
  int64_t VirusDijsktra(int64_t start, int64_t target) {
    is_visited_[start] = true;
    distances_[start] = 0;
    std::set<std::pair<int64_t, int64_t>> setpnt;
    setpnt.insert(std::make_pair(0, start));
    while (!setpnt.empty()) {
      int64_t temp_vert = setpnt.begin()->second;
      if (ill_vertex_[temp_vert] && temp_vert != start) {
        is_visited_[start] = true;
        start = temp_vert;
      }
      setpnt.erase(setpnt.begin());
      for (const auto& neighb : neighbour_[temp_vert]) {
        if (distances_[temp_vert] + neighb.second < distances_[neighb.first]) {
          setpnt.erase(std::make_pair(distances_[neighb.first], neighb.first));
          distances_[neighb.first] = distances_[temp_vert] + neighb.second;
          setpnt.insert(std::make_pair(distances_[neighb.first], neighb.first));
        }
      }
    }
    return distances_[target];
  }
};

void Work(Graph& graph, int64_t virnum, int64_t start, int64_t target) {
  int64_t distances = graph.Dijsktra(start, target);
  if (distances == kInf) {
    std::cout << -1;
    return;
  }
  int64_t i = virnum;
  while ((--i) >= 0) {
    if (!graph.IsVisited(i)) {
      int64_t virus_dist = graph.VirusDijsktra(graph.GetVirus()[i], target);
      if (virus_dist <= distances) {
        std::cout << -1;
        return;
      }
    }
  }
  std::cout << distances;
}

void InitAndWork(Graph& graph, int64_t ednum, int64_t virnum) {
  for (int64_t i = 0; i < virnum; ++i) {
    int64_t virus;
    std::cin >> virus;
    graph.GetVirus().push_back(virus);
    graph.GetIllVertices()[virus] = true;
  }
  int64_t first = 0, second = 0, len = 0;
  for (int64_t i = 0; i < ednum; ++i) {
    std::cin >> first >> second >> len;
    graph.GetNeighbours(first).push_back(std::make_pair(second, len));
    graph.GetNeighbours(second).push_back(std::make_pair(first, len));
  }
  int64_t start = 0, target = 0;
  std::cin >> start >> target;
  Work(graph, virnum, start, target);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t vnum, ednum, virnum;
  std::cin >> vnum >> ednum >> virnum;

  Graph graph(vnum);
  InitAndWork(graph, ednum, virnum);
}