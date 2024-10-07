#include <cstdint>
#include <iostream>
#include <vector>
typedef struct {
  int64_t x;
  int64_t y;
} Point;
std::vector<int64_t> FindLine(Point p1, Point p2) {
  std::vector<int64_t> line;
  int64_t a = p2.y - p1.y;
  int64_t b = p1.x - p2.x;
  int64_t c = p2.x * p1.y - p1.x * p2.y;
  line.push_back(a);
  line.push_back(b);
  line.push_back(c);
  return line;
}
int main() {
  size_t n;
  std::cin >> n;
  Point p;
  std::vector<Point> points;
  size_t pntnum = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> p.x >> p.y;
    if (i != 0 && (p.x != points.back().x || p.y != points.back().y)) {
      pntnum++;
    }
    points.push_back(p);
  }
  if (pntnum < 2) {
    std::cout << "NO" << std::endl;
    return 0;
  }
  for (size_t i = 1; i < n; i++) {
    std::vector<int64_t> line = FindLine(points[i], points[(i + 1) % n]);
    int64_t side = line[0] * points[(i - 1) % n].x +
                       line[1] * points[(i - 1) % n].y + line[2];
    side *= line[0] * points[(i + 2) % n].x + line[1] * points[(i + 2) % n].y +
            line[2];
    if (side < 0) {
      std::cout << "NO" << std::endl;
      return 0;
    }
  }
  std::cout << "YES" << std::endl;
  return 0;
}