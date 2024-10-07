#include <cctype>
#include <iostream>

struct Digit SignCheck(const char* letter, struct Digit nums);
struct Digit {
  int* digits = new int[1000000000];
  ;
  bool added;
};

int main() {
  char* letters = new char[1000000000];
  struct Digit nums;
  nums.added = false;
  std::cin.getline(letters, 10000000000);
  char* letter = letters;
  int* dig = nums.digits;
  while (*letter != '\0') {
    nums = SignCheck(letter, nums);
    letter++;
  }
  std::cout << *(nums.digits) << std::endl;
  delete[] dig;
  delete[] letters;
  return 0;
}

struct Digit SignCheck(const char* letter, struct Digit nums) {
  if (*letter == ' ') {
    nums.digits++;
    nums.added = false;
  } else if (*letter == '+') {
    nums.digits -= 2;
    *nums.digits += *(nums.digits + 1);
  } else if (*letter == '-') {
    nums.digits -= 2;
    *nums.digits -= *(nums.digits + 1);
  } else if (*letter == '*') {
    nums.digits -= 2;
    *nums.digits *= *(nums.digits + 1);
  } else if (std::isdigit(*letter) != 0) {
    if (!nums.added) {
      nums.added = true;
      *nums.digits = *letter - '0';
    } else {
      nums.digits[0] *= 10;
      nums.digits[0] += (*letter - '0');
    }
  }
  return nums;
}
