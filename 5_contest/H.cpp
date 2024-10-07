#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<size_t>> GetMatrix(
    std::vector<int>& first, std::vector<int>& second) {
  std::vector<std::vector<size_t>> matrix(
      first.size() + 1, std::vector<size_t>(second.size() + 1, 0));
  for (size_t i = 0; i < first.size(); i++) {
    for (size_t j = 0; j < second.size(); j++) {
      if (first[i] == second[j]) {
        matrix[i + 1][j + 1] = matrix[i][j] + 1;
      } else {
        matrix[i + 1][j + 1] = std::max(matrix[i][j + 1], matrix[i + 1][j]);
      }
    }
  }
  return matrix;
}

std::vector<int> GetLSC(std::vector<int>& first, std::vector<int>& second){
  std::vector<std::vector<size_t>> matrix = GetMatrix(first, second);
  std::vector<int> lsc;
  int findex = static_cast<int>(first.size() - 1);
  int sindex = static_cast<int>(second.size() - 1);
  while(findex >= 0  && sindex >= 0){
    if(first[findex] == second[sindex]){
      lsc.push_back(first[findex]);
      findex--;
      sindex--;
    }else if(matrix[findex][sindex + 1] > matrix[findex + 1][sindex]){
      findex--;
    }else{
      sindex--;
    }
  }
  return lsc;
}

void Output(std::vector<int> lsc){
  while(!lsc.empty()){
    std::cout << lsc.back()<<" ";
    lsc.pop_back();
  }
}
int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int> first(n, 0);
  for (size_t i = 0; i < n; i++) {
    std::cin >> first[i];
  }
  std::cin >> n;
  std::vector<int> second(n, 0);
  for (size_t i = 0; i < n; i++) {
    std::cin >> second[i];
  }
  Output(GetLSC(first, second));
}