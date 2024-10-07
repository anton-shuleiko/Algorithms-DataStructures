#include <iostream>
#include <vector>

std::vector<int> LAS(std::vector<int>& arr) {
    std::vector<int> las;
    if(arr.empty()){
      return las;
    }
    size_t flag_up = 1;
    size_t flag_down = 1;
    las.push_back(arr[0]);
    for (size_t i = 1; i < arr.size(); i++) {
 
        if (arr[i] > arr[i - 1]) {
          if(flag_up == flag_down + 1){
            las.pop_back();
          }
          flag_up = flag_down + 1;
          las.push_back(arr[i]);
        } else if (arr[i] < arr[i - 1]) {
          if(flag_up == flag_down-1){
            las.pop_back();
          }
          flag_down = flag_up + 1;
          las.push_back(arr[i]);
        }
    }
    return las;
}
int main(){
  size_t n = 0;
  std::cin >> n;
  std::vector<int> arr(n,0);
  for(size_t i = 0; i < n;i++){
    std::cin >> arr[i];
  }
  std::vector<int> las = LAS(arr);
  std::cout << las.size() << std::endl;
  for(int elem: las){
    std::cout << elem << " ";
  }
}