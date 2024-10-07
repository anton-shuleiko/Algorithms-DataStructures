#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

class Point {
 public:
  int64_t x;
  int64_t y;
  Point() : x(0), y(0) {}
  Point(int64_t x, int64_t y) {
    this->x = x;
    this->y = y;
  }
  Point(const Point& pnt) {
    this->x = pnt.x;
    this->y = pnt.y;
  }
  Point& operator=(const Point& pnt) {
    this->x = pnt.x;
    this->y = pnt.y;
    return *this;
  }
  bool operator==(const Point& pnt) {
    return (this->x == pnt.x && this->y == pnt.y);
  }
  bool operator!=(const Point& pnt) { return !(*this == pnt); }
  bool operator<(const Point& pnt) {
    return x < pnt.x || (x == pnt.x && y < pnt.y);
  }

  Point operator+(const Point& pt) const { return {x + pt.x, y + pt.y}; }
  Point operator-(const Point& pt) const { return {x - pt.x, y - pt.y}; }
  int64_t VectorMultiplication(const Point& pt) const { return x * pt.y - y * pt.x; }
  int64_t ManhLen() const { return llabs(x) + llabs(y); }
};

int64_t Orientation(Point p1, Point p2, Point p3) {
  int64_t val = (p2 - p1).VectorMultiplication(p3 - p1);
  if (val == 0) { return 0; }     // collinear
  return (val > 0) ? 1 : -1;  // clock or counterclock wise
}

size_t FindLeftLow(std::vector<Point> points) {
  size_t leftlow = 0;
  for (size_t i = 1; i < points.size(); i++) {
    if (points[i] < points[leftlow]) { leftlow = i; }
  }
  return leftlow;
}

class Compare {
 private:
  Point base_;
 public:
  Compare(Point pt) : base_(pt) {}
  bool operator()(const Point& left, const Point& right) {
    int64_t ori = Orientation(base_, left, right);
    int64_t left_len = (left - base_).ManhLen();
    int64_t right_len = (right - base_).ManhLen();
    return (ori == -1 || (ori == 0 && left_len < right_len));
  }
};

std::vector<Point> Shell(std::vector<Point> points) {
  std::vector<Point> shell;
  size_t leftlow = FindLeftLow(points);
  std::sort(points.begin(), points.end(), Compare(points[leftlow]));
  for (Point pt : points) {
    while (shell.size() >= 2) {
      Point curr = shell.back();
      Point prev = *std::next(shell.rbegin());
      if (Orientation(prev, curr, pt) > -1){
        shell.pop_back();
      }else{
        break;
      }
    }
    shell.push_back(pt);
  }

  return shell;
}

int64_t ShellArea(std::vector<Point>& shell) {
  int64_t area = 0;
  for (size_t i = 0; i < shell.size(); i++) {
    if (i != 0) {
      area += (shell[i - 1].x - shell[i].x) * (shell[i - 1].y + shell[i].y);
    } else {
      area += (shell.back().x - shell[i].x) * (shell.back().y + shell[i].y);
    }
  }
  return llabs(area);
}

int main() {
  size_t num;
  std::cin >> num;
  std::vector<Point> points;
  for (size_t i = 0; i < num; i++) {
    int64_t x;
    int64_t y;
    std::cin >> x >> y;
    points.push_back(Point(x, y));
  }
  std::vector<Point> shell = Shell(points);
  std::cout << shell.size() << std::endl;
  for (size_t i = 0; i < shell.size(); i++) {
    std::cout << shell[i].x << " " << shell[i].y
              << std::endl;
  }
  std::cout.precision(2);
  std::cout.setf(std::ios::scientific);
  int64_t area = ShellArea(shell);
  std::cout << (area / 2) << (area % 2 == 0 ? ".0" : ".5");

}