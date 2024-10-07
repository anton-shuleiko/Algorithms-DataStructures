#include <algorithm>
#include <iostream>

bool IsLenRight(const int* points, int num, int count, int len);
int GetLen(const int* points, int num, int count);

int main() {
  int num;
  int count;
  int iter;
  std::cin >> num >> count;
  int* points = new int[num];
  for (iter = 0; iter < num; iter++) {
    std::cin >> points[iter];
  }
  std::sort(points, points + num);
  std::cout << GetLen(points, num, count) << std::endl;
  delete[] points;
  return 0;
}

bool IsLenRight(const int* points, int num, int count, int len) {
  int end = points[0] + len;
  count--;
  for (int i = 0; i < num; i++) {
    if (end < points[i]) {
      count--;
      end = points[i] + len;
      if (count < 0) {
        return false;
      }
    }
  }
  return true;
}

int GetLen(const int* points, int num, int count) {
  if (count >= num - 1) {
    return 0;
  }
  int min_point = 0;
  int max_point = points[num - 1] - points[0];

  while (min_point != max_point) {
    int mid_point = min_point + (max_point - min_point) / 2;
    if (mid_point == max_point || mid_point == min_point) {
      return max_point;
    }

    if (IsLenRight(points, num, count, mid_point)) {
      max_point = mid_point;
    } else {
      min_point = mid_point;
    }
  }
  return max_point;
}
