#include <iostream>
#include <vector>

void MergeArrays(std::vector<int>& arr, int* ans, int low, int high, int mid);
void MergeSort(std::vector<int>& arr, int* ans, int low, int high);
int main() {
  std::vector<int> arr;
  int num;
  int ans;
  std::cin >> num;
  for (int i = 0; i < num; i++) {
    std::cin >> ans;
    arr.push_back(ans);
  }
  ans = 0;
  MergeSort(arr, &ans, 0, num - 1);
  std::cout << ans;
}
void MergeSort(std::vector<int>& arr, int* ans, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    MergeSort(arr, ans, low, mid);
    MergeSort(arr, ans, mid + 1, high);
    MergeArrays(arr, ans, low, high, mid + 1);
  }
}
void MergeArrays(std::vector<int>& arr,  int* ans, int low, int high, int mid) {
  std::vector<int> temp;
  int left = low;
  int middle_index = mid;
  while (left < mid && middle_index <= high) {
    if (arr[left] <= arr[middle_index]) {
      temp.push_back(arr[left++]);
    } else {
      temp.push_back(arr[middle_index++]);
      *ans += mid - left;
    }
  }
  while (left < mid) {
    temp.push_back(arr[left++]);
  }
  while (middle_index <= high) {
    temp.push_back(arr[middle_index++]);
  }
  arr = temp;
}