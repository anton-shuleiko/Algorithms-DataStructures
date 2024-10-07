#include <iostream>

int FindOrderStatistic(int* arr, int k, int num);
void Swapthis(int* arr, int one, int two);
int Partition(int* arr, int low, int high);

int FindOrderStatistic(int* arr, int k, int num) {
  int left = 0;
  int right = num - 1;
  while (true) {
    int mid = Partition(arr, left, right);

    if (mid == k) {
      return arr[mid];
    }
    if (k < mid) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
}
void Swapthis(int* arr, int one, int two) {
  int smth = *(arr + one);
  *(arr + one) = *(arr + two);
  *(arr + two) = smth;
}
int Partition(int* arr, int low, int high) {
  int pivot = arr[(low + high) / 2];
  int i = low;
  int j = high;
  while (true) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i >= j) {
      return j;
    }
    Swapthis(arr, i++, j--);
  }
}
int main() {
  int num;
  int k;
  std::cin >> num >> k;
  int* arr = new int[num];
  std::cin >> arr[0] >> arr[1];
  for (int i = 2; i < num; i++) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % (10000000 + 4321);
  }
  std::cout << FindOrderStatistic(arr, k - 1, num) << std::endl;
  delete[] arr;
  return 0;
}