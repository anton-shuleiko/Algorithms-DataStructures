#include <iostream>
#include <string>
#include <vector>

typedef struct {
  std::vector<long long> elements;
  std::vector<unsigned long> requests;
  unsigned int size = 0;
} BinaryHeap;

void Command(BinaryHeap* heap, unsigned int requestnum, std::string request);
void Insert(BinaryHeap* heap, unsigned int reqindex, long long value);
void Heapify(BinaryHeap* heap, unsigned int index);
void DeacreaseKey(BinaryHeap* heap, unsigned int requestnum, long long delta);
void ExtractMin(BinaryHeap* heap);
void Swap(BinaryHeap* heap, unsigned int one, unsigned int two);
void HeapIncreaseKey(BinaryHeap* heap, unsigned int index, long long key);

void Swap(BinaryHeap* heap, unsigned int one, unsigned int two) {
  std::swap(heap->elements[one], heap->elements[two]);
  std::swap(heap->requests[one], heap->requests[two]);
}
void HeapIncreaseKey(BinaryHeap* heap, unsigned int index, long long key) {
  heap->elements[index] = key;
  while (index > 0 && heap->elements[(index - 1) / 2] > heap->elements[index]) {
    Swap(heap, index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}
void Insert(BinaryHeap* heap, unsigned int reqindex, long long value) {
  heap->elements.push_back(0);
  heap->requests.push_back(reqindex);
  heap->size++;
  HeapIncreaseKey(heap, heap->size - 1, value);
}
void Heapify(BinaryHeap* heap, unsigned int index) {
  unsigned int left_child = 2 * index + 1;
  unsigned int right_child = 2 * index + 2;
  unsigned int smallest_child = index;
  if (left_child < heap->size &&
      heap->elements[left_child] < heap->elements[smallest_child]) {
    smallest_child = left_child;
  }
  if (right_child < heap->size &&
      heap->elements[right_child] < heap->elements[smallest_child]) {
    smallest_child = right_child;
  }
  if (index != smallest_child) {
    Swap(heap, index, smallest_child);
    Heapify(heap, smallest_child);
  }
}
void ExtractMin(BinaryHeap* heap) {
  heap->elements[0] = heap->elements[heap->size - 1];
  heap->requests[0] = heap->requests[heap->size - 1];
  heap->elements.pop_back();
  heap->requests.pop_back();
  heap->size--;
  Heapify(heap, 0);
}
void DeacreaseKey(BinaryHeap* heap, unsigned int requestnum, long long delta) {
  for (unsigned int i = 0; i < heap->size; i++) {
    if (heap->requests[i] == requestnum) {
      HeapIncreaseKey(heap, i, heap->elements[i] - delta);
      break;
    }
  }
}
void Command(BinaryHeap* heap, unsigned int requestnum, std::string request) {
  switch (request[0]) {
    case 'i':
      long long value;
      std::cin >> value;
      Insert(heap, requestnum, value);
      break;
    case 'g':
      std::cout << heap->elements[0] << std::endl;
      break;
    case 'e':
      ExtractMin(heap);
      break;
    case 'd':
      unsigned int reqnum;
      long long delta;
      std::cin >> reqnum >> delta;
      DeacreaseKey(heap, reqnum - 1, delta);
      break;
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  unsigned int num;
  BinaryHeap heap;
  std::string request;
  std::cin >> num;
  for (unsigned int i = 0; i < num; i++) {
    std::cin >> request;
    Command(&heap, i, request);
  }
}