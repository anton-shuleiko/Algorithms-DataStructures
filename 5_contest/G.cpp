#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <algorithm>

size_t FindSubsequence(size_t n, std::vector<int>& arr){
  std::vector<int> d(n,INT_MAX);
  d[0] = INT_MIN;
  for (int element: arr) {
    size_t j = static_cast<size_t>(std::upper_bound (d.begin(), d.end(), element) - d.begin());
    if (d[j-1] < element && element < d[j]){
      d[j] = element;
    }
  }

  return static_cast<size_t>(std::upper_bound (d.begin(), d.end(), INT_MAX - 1) - d.begin()) - 1;
}

int main(){
  size_t n = 0;
  std::cin >> n;
  std::vector<int> arr;
  for(size_t i = 0; i < n; i++){
    int power = 0;
    std::cin >> power;
    arr.push_back(power);
  }
  std::cout << FindSubsequence(n, arr) << std::endl;
}