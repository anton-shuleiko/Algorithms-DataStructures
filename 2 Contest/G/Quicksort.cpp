#include <iostream>

void Quisort(int* arr, int lo, int hi);
void Swapthis(int* arr, int one, int two);
int Partition(int* arr, int low, int high);

void Quisort(int* arr, int lo, int hi) {
  if (lo < hi) {
    int p = Partition(arr, lo, hi);
    Quisort(arr, lo, p);
    Quisort(arr, p + 1, hi);
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
  std::cin >> num;
  int* arr = new int[num];
  for (int i = 0; i < num; i++) {
    std::cin >> arr[i];
  }
  Quisort(arr, 0, num - 1);
  for (int i = 0; i < num; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  delete[] arr;
  return 0;
}