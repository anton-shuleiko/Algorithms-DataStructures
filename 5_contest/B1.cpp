#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class point{
public:
  int64_t x;
  int64_t y;
};

int VectorMult(point p, point p1, point p2) {
  if ((p1.x - p.x) * (p2.y - p.y) - (p1.y - p.y) * (p2.x - p.x) > 0) {
    return 1;
  }
  if ((p1.x - p.x) * (p2.y - p.y) - (p1.y - p.y) * (p2.x - p.x) < 0) {
    return -1;
  }
  return 0;
}

int main() {
  size_t n;
  std::cin >> n;
  int64_t x;
  int64_t y;
  std::vector<point> pnts;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x >> y;
    pnts.push_back({x, y});
  }

  size_t plus = 0;
  size_t minus = 0;
  for (size_t i = 0; i < n; i++) {
    int curr = VectorMult(pnts[i], pnts[(i + 1) % n], pnts[(i + 2) % n]);
    if (curr > 0) {
      plus = 1;
    } else if (curr < 0) {
      minus = 1;
    }
  }
  if (plus + minus == 1) {
    std::cout << "YES" << std::endl;
    return 0;
  }
  std::cout << "NO" << std::endl;
  return 0;
}
