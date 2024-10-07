#include <iostream>
#include <list>

typedef struct {
  int left;
  int right;
} Minus;

void Quisort(Minus* minarr, int lo, int hi);
void Swapthis(Minus* minarr, int one, int two);
int Partition(Minus* minarr, int low, int high);
void Outputlists(std::list<int> startlist, std::list<int> endlist);
void SetAndOutLists(Minus* minarr, std::list<int> startlist,
                    std::list<int> endlist, int num);

void Quisort(Minus* minarr, int lo, int hi) {
  if (lo < hi) {
    int p = Partition(minarr, lo, hi);
    Quisort(minarr, lo, p);
    Quisort(minarr, p + 1, hi);
  }
}
void Swapthis(Minus* minarr, int one, int two) {
  Minus smth = *(minarr + one);
  *(minarr + one) = *(minarr + two);
  *(minarr + two) = smth;
}
int Partition(Minus* minarr, int low, int high) {
  int pivot = (minarr + (low + high) / 2)->left;
  int i = low;
  int j = high;
  while (true) {
    while ((minarr + i)->left < pivot) {
      i++;
    }
    while ((minarr + j)->left > pivot) {
      j--;
    }
    if (i >= j) {
      return j;
    }
    Swapthis(minarr, i++, j--);
  }
}

void SetAndOutLists(Minus* minarr, std::list<int> startlist,
                    std::list<int> endlist, int num) {
  int start = minarr[0].left;
  int end = minarr[0].right;
  for (int i = 0; i < num; i++) {
    if (minarr[i].left > end) {
      startlist.push_back(start);
      endlist.push_back(end);
      start = minarr[i].left;
      end = minarr[i].right;
    } else {
      if (minarr[i].right > end) {
        end = minarr[i].right;
      }
    }
  }
  startlist.push_back(start);
  endlist.push_back(end);
  Outputlists(startlist, endlist);
}
void Outputlists(std::list<int> startlist, std::list<int> endlist) {
  std::cout << startlist.size() << std::endl;
  while (!startlist.empty()) {
    std::cout << startlist.front() << " " << endlist.front() << std::endl;
    startlist.pop_front();
    endlist.pop_front();
  }
}
int main() {
  int num;
  std::cin >> num;
  Minus* minarr = new Minus[num];
  for (int i = 0; i < num; i++) {
    std::cin >> minarr[i].left >> minarr[i].right;
  }
  Quisort(minarr, 0, num - 1);
  std::list<int> startlist;
  std::list<int> endlist;
  SetAndOutLists(minarr, startlist, endlist, num);

  delete[] minarr;
  return 0;
}