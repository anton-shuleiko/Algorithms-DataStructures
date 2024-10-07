#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int gipo_num;
  int count;
  int first;
  int last;
  long double gipo_sound[3000000];
  std::cin >> gipo_num;
  for (int i = 0; i < gipo_num; i++) {
    std::cin.precision(2);
    std::cin >> gipo_sound[i];
    gipo_sound[i] = powl(gipo_sound[i], 1.0 / 10000.0);
    if (i != 0) {
      gipo_sound[i] *= gipo_sound[i - 1];
    }
  }
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    std::cin >> first >> last;
    std::cout << std::fixed;
    if (first != 0) {
      std::cout << powl(gipo_sound[last] / gipo_sound[first - 1],
                        10000.0 / (last - first + 1))
                << std::endl;
    } else {
      std::cout << powl(gipo_sound[last], 10000.0 / (last - first + 1)) << std::endl;
    }
  }
  return 0;
}