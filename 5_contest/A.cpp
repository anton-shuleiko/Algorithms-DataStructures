#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

float FindAngle(int x1, int y1, int x2, int y2) {
  float scalar = x1 * x2 + y1 * y2;
  float a = std::sqrt(x1 * x1 + y1 * y1);
  float b = std::sqrt(x2 * x2 + y2 * y2);
  float cos_x = scalar / (a * b);
  float angle = std::acos(cos_x) * (x1 * y2 - x2 * y1 > 0 ? 1 : -1);
  return angle;
}

int main() {
  int n;
  std::vector<int> x;
  std::vector<int> y;
  int xp;
  int yp;
  float res = 0;
  std::cin >> n >> xp >> yp;
  for (int i = 0; i < n; i++) {
    int x0;
    int y0;
    std::cin >> x0 >> y0;
    if (x0 == xp && y0 == yp) {
      std::cout << "YES" << std::endl;
      return 0;
    }
    x.push_back(x0);
    y.push_back(y0);
  }
  x.push_back(x[0]);
  y.push_back(y[0]);
  for (int i = 0; i < n; i++) {
    res += FindAngle(x[i] - xp, y[i] - yp, x[i + 1] - xp, y[i + 1] - yp);
  }
  res = std::round(res / (2 * M_PI));
  if (res == 0) {
    std::cout << "NO" << std::endl;
  } else {
    std::cout << "YES" << std::endl;
  }
  return 0;
}
