#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

typedef struct {
  std::vector<int> min_heap;
  std::vector<int> max_heap;
  int size = 0;
} Multiheap;
/////////////////////////////////////////
void Insert(Multiheap* mheap, int value);
void SwiftUpMin(std::vector<int>& min_heap, int index);
void SwiftUpMax(std::vector<int>& max_heap, int index);
void SwiftDownMax(std::vector<int>& max_heap, int index);
void SwiftDownMin(std::vector<int>& min_heap, int index);
int ExtractMin(Multiheap* mheap);
int ExtractMax(Multiheap* mheap);
void Clear(Multiheap* mheap);
/////////////////////////////////////////
void Insert(Multiheap* mheap, int value) {
  mheap->max_heap.push_back(value);
  mheap->min_heap.push_back(value);
  SwiftUpMax(mheap->max_heap, mheap->max_heap.size() - 1);
  SwiftUpMin(mheap->min_heap, mheap->min_heap.size() - 1);
  mheap->size++;
}
/////////////////////////////////////////
void SwiftUpMin(std::vector<int>& min_heap, int index) {
  int parent = (index - 1) / 2;
  if (min_heap[index] < min_heap[parent]) {
    std::swap(min_heap[index], min_heap[parent]);
    SwiftUpMin(min_heap, parent);
  }
}
/////////////////////////////////////////
void SwiftUpMax(std::vector<int>& max_heap, int index) {
  int parent = (index - 1) / 2;
  if (max_heap[index] > max_heap[parent]) {
    std::swap(max_heap[index], max_heap[parent]);
    SwiftUpMax(max_heap, parent);
  }
}
/////////////////////////////////////////
void SwiftDownMax(std::vector<int>& max_heap, int index) {
  int largest_element = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  if (left < (int)max_heap.size() &&
      max_heap[largest_element] < max_heap[left]) {
    largest_element = left;
  }
  if (right < (int)max_heap.size() &&
      max_heap[largest_element] < max_heap[right]) {
    largest_element = right;
  }
  if (index != largest_element) {
    std::swap(max_heap[index], max_heap[largest_element]);
    SwiftDownMax(max_heap, largest_element);
  }
}
/////////////////////////////////////////
void SwiftDownMin(std::vector<int>& min_heap, int index) {
  int smallest_element = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  if (left < (int)min_heap.size() &&
      min_heap[smallest_element] > min_heap[left]) {
    smallest_element = left;
  }
  if (right < (int)min_heap.size() &&
      min_heap[smallest_element] > min_heap[right]) {
    smallest_element = right;
  }
  if (index != smallest_element) {
    std::swap(min_heap[index], min_heap[smallest_element]);
    SwiftDownMin(min_heap, smallest_element);
  }
}
/////////////////////////////////////////
int ExtractMin(Multiheap* mheap) {
  int min = mheap->min_heap[0];
  mheap->min_heap[0] = mheap->min_heap[mheap->size - 1];
  mheap->min_heap.pop_back();
  SwiftDownMin(mheap->min_heap, 0);
  for (int i = (int)(mheap->max_heap.size() / 2);
       i < (int)mheap->max_heap.size(); i++) {
    if (mheap->max_heap[i] == min) {
      mheap->max_heap[i] = mheap->max_heap[mheap->size - 1];
      mheap->max_heap.pop_back();
      SwiftUpMax(mheap->max_heap, i);
      break;
    }
  }
  mheap->size--;
  return min;
}
/////////////////////////////////////////
int ExtractMax(Multiheap* mheap) {
  int max = mheap->max_heap[0];
  mheap->max_heap[0] = mheap->max_heap[mheap->size - 1];
  mheap->max_heap.pop_back();
  SwiftDownMax(mheap->max_heap, 0);
  for (int i = (int)(mheap->min_heap.size() / 2);
       i < (int)mheap->min_heap.size(); i++) {
    if (mheap->min_heap[i] == max) {
      mheap->min_heap[i] = mheap->min_heap[mheap->size - 1];
      mheap->min_heap.pop_back();
      SwiftUpMin(mheap->min_heap, i);
      break;
    }
  }
  mheap->size--;
  return max;
}
/////////////////////////////////////////
void Clear(Multiheap* mheap) {
  mheap->max_heap.clear();
  mheap->min_heap.clear();
  mheap->size = 0;
}
/////////////////////////////////////////
void Command(Multiheap* mheap, std::string req) {
  if (req == "insert") {
    std::cout << "ok" << std::endl;
    int val;
    std::cin >> val;
    Insert(mheap, val);
  } else if (req == "clear") {
    std::cout << "ok" << std::endl;
    Clear(mheap);
  } else if (req == "size") {
    std::cout << mheap->size << std::endl;
  } else if (mheap->size == 0) {
    std::cout << "error" << std::endl;
  } else if (req == "get_min") {
    std::cout << mheap->min_heap[0] << std::endl;
  } else if (req == "get_max") {
    std::cout << mheap->max_heap[0] << std::endl;
  } else if (req == "extract_max") {
    std::cout << ExtractMax(mheap) << std::endl;
  } else if (req == "extract_min") {
    std::cout << ExtractMin(mheap) << std::endl;
  }
}
/////////////////////////////////////////
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int count;
  Multiheap* mheap = new Multiheap;
  std::cin >> count;
  std::string request;
  for (int i = 0; i < count; i++) {
    std::cin >> request;
    Command(mheap, request);
  }
  delete mheap;
  return 0;
}