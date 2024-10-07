#include <iostream>
#include <vector>
#include <algorithm>
std::vector<std::vector<int16_t>> adj_matr;
std::vector<std::vector<int16_t>> between;
std::vector<int16_t> games;
std::vector<int16_t> wins;
std::vector<bool> visited;
int16_t num_vertex;
int16_t num_edge;
int16_t sum = 0;
int16_t res = 0;

int16_t DFS(int16_t start, int16_t target, int16_t mflow = INT16_MAX) {
  if (start == target) {
    return mflow;
  }
  visited[start] = true;
  for (int16_t vert = 0; vert < num_vertex + 2; ++vert) {
    if (!visited[vert] && adj_matr[start][vert] > 0) {
      int16_t flow = DFS(vert, target, std::min(mflow, adj_matr[start][vert]));
      if (flow > 0) {
        adj_matr[vert][start] += flow;
        adj_matr[start][vert] -= flow;
        return flow;
      }
    }
  }
  return 0;
}

int16_t MaxFlow(int16_t start, int16_t target) {
  visited.assign(visited.size(), false);
  int16_t flow = DFS(start - 1, target - 1);
  if (flow != 0) {
    MaxFlow(start, target);
  }
  res += flow;

  return res;
}
void Input() {
  std::cin >> num_vertex;

  for (int16_t i = 0; i < num_vertex; ++i) {
    int16_t win;
    std::cin >> win;
    wins.push_back(win);
  }
  for (int16_t i = 0; i < num_vertex; ++i) {
    int16_t game;
    std::cin >> game;
    sum+=game;
    games.push_back(game);
  }
  between.resize(num_vertex, std::vector<int16_t>(num_vertex, 0));
  for (int16_t i = 0; i < num_vertex; ++i) {
    for (int16_t j = 0; j < num_vertex; ++j) {
      int16_t btw;
      std::cin >> btw;
      between[i][j] = btw;
    }
  }
}

void CreateNetwork() {
  adj_matr.resize(num_vertex + 2, std::vector<int16_t>(num_vertex + 2, 0));
  visited.resize(num_vertex + 2, false);
  int16_t start = 0;
  int16_t target = num_vertex + 1;
  for (int16_t i = 1; i <= num_vertex; i++) {
    for (int16_t j = 1; j <= num_vertex; j++) {
      if (between[i - 1][j - 1] != 0) {
        adj_matr[i][j] += between[i - 1][j - 1];
      }
    }
    if(i == 1){
      adj_matr[start][i] = INT16_MAX;
    }else{
      adj_matr[start][i] += std::max(0, wins[1] - wins[i - 1]);
    }
    adj_matr[i][target] = games[i];
  }
  for (int16_t i = 1; i <= num_vertex; i++) {
    adj_matr[i][target] += wins[1] + games[1] - wins[i - 1];
  }
}
int main() {
  Input();
  CreateNetwork();

  if (MaxFlow(1, num_vertex + 2) == sum) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }

  return 0;
}