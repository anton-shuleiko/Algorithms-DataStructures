#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

const std::vector<std::vector<size_t>> TARGET = {{1, 2, 2}, {3,5, 6}, {7,8,0}};
std::vector<std::vector<std::vector<size_t>>> matrix_set;

bool Find(std::vector<std::vector<size_t>> vec){
  for(const auto& k : matrix_set){
    if(k == vec){
      return true;
    }
  }
  return false;
}
std::pair<size_t, std::vector<char>> Algo(
    size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix);

std::pair<size_t, std::vector<char>> Right(
    size_t x, size_t y, size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix) {
  directions.push_back('R');
  count++;
  matrix[x][y - 1] += matrix[x][y];
  matrix[x][y] = matrix[x][y - 1] - matrix[x][y];
  matrix[x][y - 1] -= matrix[x][y];

  return Algo(count, directions, matrix);
}
std::pair<size_t, std::vector<char>> Left(
    size_t x, size_t y, size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix) {
  directions.push_back('L');
  count++;
  matrix[x][y + 1] += matrix[x][y];
  matrix[x][y] = matrix[x][y + 1] - matrix[x][y];
  matrix[x][y + 1] -= matrix[x][y];
  return Algo(count, directions, matrix);
}
std::pair<size_t, std::vector<char>> Down(
    size_t x, size_t y, size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix) {
  directions.push_back('D');
  count++;
  matrix[x - 1][y] += matrix[x][y];
  matrix[x][y] = matrix[x - 1][y] - matrix[x][y];
  matrix[x - 1][y] -= matrix[x][y];
  return Algo(count, directions, matrix);
}
std::pair<size_t, std::vector<char>> Up(
    size_t x, size_t y, size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix) {
  directions.push_back('U');
  count++;
  matrix[x + 1][y] += matrix[x][y];
  matrix[x][y] = matrix[x + 1][y] - matrix[x][y];
  matrix[x + 1][y] -= matrix[x][y];
  return Algo(count, directions, matrix);
}

std::pair<size_t, std::vector<char>> Algo(
    size_t count, std::vector<char> directions,
    std::vector<std::vector<size_t>> matrix) {
  if (matrix == TARGET) {
    return std::make_pair(count, directions);
  }
  if (Find(matrix)) {
    return {SIZE_MAX, directions};
  }
  matrix_set.push_back(matrix);
  size_t x = 0, y = 0;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      if (matrix[i][j] == 0) {
        x = i;
        y = j;
        break;
      }
    }
  }
  std::vector<std::pair<size_t, std::vector<char>>> results;
  if (x < 2 && (directions.empty() || directions.back() != 'D')) {
    results.push_back(Up(x, y, count, directions, matrix));
  }
  if (x > 0 && (directions.empty() || directions.back() != 'U')) {
    results.push_back(Down(x, y, count, directions, matrix));
  }

  if (y < 2 && (directions.empty() || directions.back() != 'R')) {
    results.push_back(Left(x, y, count, directions, matrix));
  }
  if (y > 0 && (directions.empty() || directions.back() != 'L')) {
    results.push_back(Right(x, y, count, directions, matrix));
  }
  size_t min = SIZE_MAX;
  std::pair<size_t, std::vector<char>> res;
  for (const auto& p : results) {
    if (p.first < min) {
      res = p;
    }
  }
  return res;
}

int main() {
  std::vector<std::vector<size_t>> matrix(3, std::vector<size_t>(3));
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      size_t elem;
      std::cin >> elem;
      matrix[i][j] = elem;
    }
  }
  std::pair<size_t, std::vector<char>> answer;
  size_t count = 0;
  std::vector<char> directions;
  answer = Algo(count, directions, matrix);
  std::cout << answer.first << std::endl;
  for (const auto& elem : answer.second) {
    std::cout << elem;
  }
}