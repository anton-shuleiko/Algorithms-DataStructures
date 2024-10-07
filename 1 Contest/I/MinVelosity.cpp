#include <algorithm>
#include <iostream>

int metla_nums;

void MinVeloChecker(int* min, int* rev_min, int left, int right);
int FindMin(int* metl, int* min, int i);
int FindRevMin(int* metl, int* rev_min, int i);

int main() {
  int* metl = new int[100000];
  int* min = new int[100000];
  int* rev_min = new int[100000];
  int count;
  int left;
  int right;
  std::cin >> metla_nums;
  for (int i = 0; i < metla_nums; i++) {
    std::cin >> metl[i];
    min[i] = FindMin(metl, min, i);
  }
  for (int i = metla_nums - 1; i >= 0; i--) {
    rev_min[i] = FindRevMin(metl, rev_min, i);
  }
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    std::cin >> left >> right;
    MinVeloChecker(min, rev_min, left - 1, right - 1);
  }
  delete[] metl;
  delete[] min;
  delete[] rev_min;
  return 0;
}

void MinVeloChecker(int* min, int* rev_min, int left, int right) {
  if (min[left] == min[right]) {
    std::cout << min[metla_nums - 1] << std::endl;
  } else {
    if (min[right] != min[metla_nums - 1]) {
      std::cout << min[metla_nums - 1] << std::endl;
    } else {
      std::cout << std::min(min[left], rev_min[right]) << std::endl;
    }
  }
}

int FindRevMin(int* metl, int* rev_min, int i) {
  if (i == metla_nums - 1 || metl[i] < rev_min[i + 1]) {
    return metl[i];
  }
  return rev_min[i + 1];
}

int FindMin(int* metl, int* min, int i) {
  if (i == 0 || metl[i] < min[i - 1]) {
    return metl[i];
  }
  return min[i - 1];
}