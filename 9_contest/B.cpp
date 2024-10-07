#include <iostream>
#include <vector>


const int MAXN = 255;

std::vector<std::vector<int>> graph(MAXN);
std::vector<int> match(MAXN, -1);
std::vector<bool> used(MAXN);

bool dfs(int vert) {
  used[vert] = true;
  for (int i = 0; i < graph[vert].size(); i++) {
    int temp_vert = graph[vert][i];
    int wght = match[temp_vert];
    if (wght == -1 || (!used[wght] && dfs(wght))) {
      match[temp_vert] = vert;
      return true;
    }
  }
  return false;
}
void Work() {
  int english, chinese;
  std::cin >> english >> chinese;

  for (int i = 1; i <= english; i++) {
    int input_val;
    std::cin >> input_val;
    while (input_val != 0) {
      graph[i].push_back(input_val);
      std::cin >> input_val;
    }
  }

  int cnt = 0;
  for (int i = 1; i <= english; i++) {
    used.assign(MAXN, false);
    if (dfs(i)) {
      cnt++;
    }
  }

  std::cout << cnt << std::endl;
  for (int i = 1; i <= chinese; i++) {
    if (match[i] != -1) {
      std::cout << match[i] << " " << i << std::endl;
    }
  }
}
int main() {
  Work();

  return 0;
}
