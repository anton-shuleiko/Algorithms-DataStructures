#include <cstdint>
#include <iostream>
#include <vector>

size_t GetByte(uint64_t val, int byte);
void LsdSort(std::vector<uint64_t>& arr);

size_t GetByte(uint64_t val, int byte) {
  return (size_t)(val >> (8 * byte) & 0xFF);
}

void LsdSort(std::vector<uint64_t>& arr) {
  for (int byte = 0; byte < 8; byte++) {
    std::vector<uint64_t> count[256];
    while (!arr.empty()) {
      count[GetByte(arr.back(), byte)].push_back(arr.back());
      arr.pop_back();
    }
    size_t j = 255;
    while (true) {
      while (!count[j].empty()) {
        arr.push_back(count[j].back());
        count[j].pop_back();
      }
      if (j == 0) {
        break;
      }
      j--;
    }
  }
}

int main() {
  size_t n;
  std::vector<uint64_t> arr;
  uint64_t val;
  std::cin >> n;
  for (size_t i = 0; i < n; i++) {
    std::cin >> val;
    arr.push_back(val);
  }
  LsdSort(arr);
  std::ios_base::sync_with_stdio(false);
  for (size_t i = n - 1;; i--) {
    printf("%lu\n", arr[i]);
    if (i == 0) {
      break;
    }
  }
  return 0;
}