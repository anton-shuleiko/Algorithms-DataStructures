#include <iostream>

int main() {
  int num;
  int curr_var = 0;
  int new_var = 0;
  int ite = 0;
  std::cin >> num;
  bool printed = false;
  for (ite = 0; ite < num; ite++) {
    std::cin >> new_var;
    if (ite == 0 || new_var > curr_var) {
      curr_var = new_var;
    }
    if (new_var < curr_var && !printed) {
      std::cout << ite << std::endl;
      printed = true;
    }
  }
  if (curr_var == new_var) {
    std::cout << 0 << std::endl;
  }
  return 0;
}