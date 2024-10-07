#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

size_t PrefFunc(std::string s) {
  
  std::vector<size_t> pi(s.length());
  for (size_t i = 1; i < s.length(); ++i) {
    size_t j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) {
      ++j;
    }
    pi[i] = j;
  }
  return pi[pi.size() - 1];
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);  // flushes cout
  size_t num = 0;
  std::string str;
  std::string res;
  std::cin >> num;
  while (num-- > 0) {
    std::cin >> str;
    res += str.substr(PrefFunc(str + '#' + (res.size()>str.size()?res.substr(res.size()-str.size(),res.size()):res)), str.size());
  }
  std::cout << res;
  return 0;
}