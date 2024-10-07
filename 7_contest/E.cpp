#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>
const int  kSome = 100000;
class Graph {
 public:
  Graph(int num_point) {
    neighbours_ = std::vector<std::vector<std::pair<int, int>>>(num_point);
    num_ = num_point;
    ancestor_ = std::vector<int>(num_point, -1);
    distance_ = std::vector<int>(num_point, 0);
  }
  std::vector<int>& GetPoints(){
    return pnt_;
  }
  std::vector<std::pair<int, int>>& GetNeighb(int pnt){
    return neighbours_[pnt];
  }
  int GetNum(){
    return num_;
  }
  void Loop() {
    int flag = -1;
    int i = 0;
    while ( i < num_) {
      flag = -1;
      for (int k : pnt_) {
        for (const auto& neighb : neighbours_[k]) {
          if (distance_[neighb.first] > distance_[k] + neighb.second) {
            distance_[neighb.first] =
                std::max(distance_[k] + neighb.second, INT32_MIN);
            ancestor_[neighb.first] = k;
            flag = neighb.first;
          }
        }
      }
      ++i;
    }
    Output(flag);
  }

  void Output(int flag) {
    int pnt;
    if (flag == -1) {
      std::cout << "NO";
      return;
    }
    pnt = flag;
    int i = 0;
    while (i < num_) {
      pnt = ancestor_[pnt];
      ++i;
    }
    int vertex = pnt;
    while (vertex != pnt || answer_.size() <= 1) {
      answer_.push_back(vertex);
      vertex = ancestor_[vertex];
    }
    answer_.push_back(vertex);
    std::cout << "YES\n" << answer_.size() << '\n';
    std::reverse(answer_.begin(), answer_.end());
    for (const auto& ans : answer_) {
      std::cout << ans + 1 << " ";
    }
  }

 private:
  std::vector<int> answer_;
  std::vector<int> distance_;
  int num_ = 0;
  std::vector<std::vector<std::pair<int, int>>> neighbours_;
  std::vector<int> pnt_;
  std::vector<int> ancestor_;
};

bool Init(Graph& graph){
  int len = 0;
  for (int i = 0; i < graph.GetNum(); ++i) {
    for (int j = 0; j < graph.GetNum(); ++j) {
      std::cin >> len;
      if (len != kSome) {
        graph.GetPoints().push_back(i);
        graph.GetNeighb(i).push_back(std::make_pair(j, len));
        if (i == j && len < 0) {
          std::cout << "YES" <<std::endl;
          std::cout << 2 <<std::endl; 
          std::cout << i + 1 << " " << i + 1;
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  int num = 0;
  std::cin >> num;
  Graph graph(num);
  if(Init(graph)){
    return 0;
  }
  graph.Loop();
  return 0;
}