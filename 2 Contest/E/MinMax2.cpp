#include <iostream>
#include <string>
#include <vector>

void Quisort(std::vector<int32_t>& arr, int32_t lo, int32_t hi);
int32_t Partition(std::vector<int32_t>& arr, int32_t low, int32_t high);
void Command(std::vector<int32_t>& arr, std::string req);
void Insert(std::vector<int32_t>& arr, int32_t value);

void Quisort(std::vector<int32_t>& arr, int32_t lo, int32_t hi) {
  if (lo < hi) {
    int32_t p = Partition(arr, lo, hi);
    Quisort(arr, lo, p);
    Quisort(arr, p + 1, hi);
  }
}

int32_t Partition(std::vector<int32_t>& arr, int32_t low, int32_t high) {
  int32_t pivot = arr[(low + high) / 2];
  int32_t i = low;
  int32_t j = high;
  while (true) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i >= j) {
      return j;
    }
    std::swap(arr[i++], arr[j--]);
  }
}

void Insert(std::vector<int32_t>& arr, int32_t value) {
  arr.push_back(value);
  Quisort(arr,0,arr.size() - 1);
}

void Command(std::vector<int32_t>& arr, std::string req) {
  if (req == "insert") {
    std::cout << "ok" << std::endl;
    int32_t val;
    std::cin >> val;
    Insert(arr, val);
  } else if (req == "clear") {
    std::cout << "ok" << std::endl;
    arr.clear();
  } else if (req == "size") {
    std::cout << arr.size() << std::endl;
  } else if (arr.empty()) {
    std::cout << "error" << std::endl;
  } else if (req == "get_min") {
    std::cout << arr[0] << std::endl;
  } else if (req == "get_max") {
    std::cout << arr[arr.size()-1] << std::endl;
  } else if (req == "extract_max") {
    std::cout << arr[arr.size()-1] << std::endl;
    arr.pop_back();
  } else if (req == "extract_min") {
    std::cout << arr[0] << std::endl;
    arr.erase(arr.begin());
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t count;
  std::vector<int32_t> arr;
  std::cin >> count;
  std::string request;
  for (int32_t i = 0; i < count; i++) {
    std::cin >> request;
    Command(arr, request);
  }
  return 0;
}