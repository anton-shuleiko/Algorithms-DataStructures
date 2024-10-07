#include <iostream>

int main() {
  int count;
  int min = 0;
  int max;
  int mid;
  std::cin >> count;
  int* num = new int[count];
  for (int i = 0; i < count; i++) {
    std::cin >> num[i];
  }
  max = count - 1;
  mid = (min + max) / 2;
  if (num[min] < num[max]) {
    std::cout << 0 << std::endl;
  } else {
    while (mid != max) {
      if (num[mid] > num[mid + 1]) {
        break;
      }
      if (num[mid] <= num[max]) {
        max = mid;
      } else {
        min = mid;
      }
      mid = (min + max) / 2;
    }
    std::cout << mid + 1 << std::endl;
  }
  delete[] num;
  return 0;
}