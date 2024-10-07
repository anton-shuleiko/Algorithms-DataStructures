#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target);

int main() {
  int mass_length;
  int func_calls_num;
  int ite;
  int begin;
  int end;
  int target;
  std::cin >> mass_length;
  int* arr = new int[mass_length];
  for (ite = 0; ite < mass_length; ite++) {
    std::cin >> arr[ite];
  }
  std::cin >> func_calls_num;
  for (ite = 0; ite < func_calls_num; ite++) {
    std::cin >> begin >> end >> target;
    if (BinarySearch(arr + begin, arr + end, target)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  delete[] arr;
  return 0;
}
bool BinarySearch(const int* begin, const int* end, int target) {
  int difference;
  const int* pntr;
  if (begin != end - 1) {
    difference = (end - begin) / 2;
    pntr = begin + difference;
    if (*pntr == target) {
      return true;
    }
    if (*pntr < target) {
      return BinarySearch(pntr, end, target);
    }
    if (*pntr > target) {
      return BinarySearch(begin, pntr, target);
    }
  }
  return *begin == target;
}