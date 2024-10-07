#include <iostream>
#include <string>
#include <vector>

typedef struct {
  std::vector<long long> elements;
  unsigned int size = 0;
} BinaryHeap;

void Insert(BinaryHeap* heap, long long value);
void Heapify(BinaryHeap* heap, unsigned int index);
long long ExtractMin(BinaryHeap* heap);
unsigned int FindMax(BinaryHeap* heap);
void Swap(BinaryHeap* heap, unsigned int one, unsigned int two);
void HeapIncreaseKey(BinaryHeap* heap, unsigned int index, long long key);

void Swap(BinaryHeap* heap, unsigned int one, unsigned int two) {
  std::swap(heap->elements[one], heap->elements[two]);
}
void HeapIncreaseKey(BinaryHeap* heap, unsigned int index, long long key) {
  heap->elements[index] = key;
  while (index > 0 && heap->elements[(index - 1) / 2] > heap->elements[index]) {
    Swap(heap, index, (index - 1) / 2);
    index = (index - 1) / 2;
  }
}
void Insert(BinaryHeap* heap, long long value) {
  heap->elements.push_back(0);
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
long long ExtractMin(BinaryHeap* heap) {
  long long min = heap->elements[0];
  heap->elements[0] = heap->elements[heap->size - 1];
  heap->elements.pop_back();
  heap->size--;
  Heapify(heap, 0);
  return min;
}
unsigned int FindMax(BinaryHeap* heap){
  long long max = heap->elements[0];
  unsigned int index = 0;
  for (unsigned int i = 0; i < heap->size; i++) {
    if (max < heap->elements[i]) {
      max = heap->elements[i];
      index = i;
    }
  }
  return index;
}
int main() {
  unsigned int num;
  unsigned int kindex;
  long long val, max;
  long long coeff1, coeff0;
  std::cin >> num >> kindex >> val >> coeff1 >> coeff0;
  BinaryHeap* heap = new BinaryHeap;
  max = val;
  for (unsigned int i = 0; i < num; i++) {
    val = (coeff1 * val + coeff0) % 1073741824;
    if (i < kindex) {
      if (max < val) {
        max = val;
      }
      Insert(heap, val);
    } else if (max > val) {
      HeapIncreaseKey(heap,FindMax(heap),val);
      max = heap->elements[FindMax(heap)];
    }
  }
  for (unsigned int i = 0; i < kindex; i++) {
    std::cout << ExtractMin(heap) << " ";
  }
  std::cout << std::endl;
  delete heap;
  return 0;
}