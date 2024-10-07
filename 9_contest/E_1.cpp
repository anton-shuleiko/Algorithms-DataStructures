#include <cstdio>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::string str;
  std::string alpabet = {"abcdefghijklmnopqrstuvwxyz"};
  std::getline(std::cin, str);
  for (auto to : alpabet) {
    auto pos = str.find_first_of(tolower(to));
    if (pos != std::string::npos) {
      printf("%c : %ld\n", to, pos + 1);
    }
  }
  return 0;
}