#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


/////////////////////////////////////////
void Insert(std::vector<int>& heap, int value);
void SwiftUpMin(std::vector<int>& min_heap, int index);
void SwiftDownMin(std::vector<int>& min_heap, int index);
int ExtractMin(std::vector<int>& heap);
/////////////////////////////////////////
void Insert(std::vector<int>& heap, int value) {
  heap.push_back(value);
  SwiftUpMin(heap, (int)(heap.size() - 1));
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
int ExtractMin(std::vector<int>& heap) {
  int min = heap[0];
  heap[0] = heap[heap.size() - 1];
  heap.pop_back();
  SwiftDownMin(heap, 0);
  return min;
}
/////////////////////////////////////////
std::vector<int> Merge2Heaps(std::vector<int> first, std::vector<int> second) {
  std::vector<int> merge;
    int i = 0, j = 0;
    while (i + j < (int)(first.size() + second.size())) {
        if (i != (int)first.size() && (j == (int)second.size() || first[i] < second[j])) {
            Insert(merge, first[i]);
            i++;
        }
        else {
            Insert(merge, second[j]);
            j++;
        }
    }
    
    return merge;
}
//////////////////////////////////////////////////////
std::vector<int> MergeHeaps(std::vector<std::vector<int> > heaparr) {
    std::vector<std::vector<int> > arr_s;
    while (heaparr.size() != 1) {
        arr_s.clear();
        for (int i = 0; i < (int)heaparr.size(); i += 2) {
            if (i == (int)heaparr.size() - 1){
                arr_s.push_back(heaparr[i]);
            } else {
                arr_s.push_back(Merge2Heaps(heaparr[i], heaparr[i + 1]));
            }
        }
        heaparr = arr_s;
    }
    return heaparr[0];
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int k;
  std::cin >> k;
  std::vector<std::vector<int>> heaparr;
  for (int i = 0; i < k; i++) {
      int n;
      std::cin >> n;
      std::vector<int> heap;
      for (int j = 0; j < n; ++j) {
          int var;
          std::cin >> var;
          Insert(heap, var);
      }
      heaparr.push_back(heap);
  }

  std::vector<int> output = MergeHeaps(heaparr);
  while(!output.empty()){
    std::cout << ExtractMin(output) << " ";
  }
  std::cout << std::endl;
  return 0;
}