#include <iostream>
#include <vector>

std::vector<int> MergeArrays(std::vector<std::vector<int> >& arr,int* a);
std::vector<int> Merge2Arrays(std::vector<int>& first, std::vector<int>& second,int* a);
std::vector<std::vector<int> > SetArrays(std::vector<int>& arr,int* a);


std::vector<int> Merge2Arrays(std::vector<int>& first, std::vector<int>& second,int* a) {
  std::vector<int> ret;
  int f_in = 0, s_in = 0;
  while (f_in < first.size() && s_in < second.size()) {
      if (s_in < second.size() && first[f_in] > second[s_in]) {
          ret.push_back(second[s_in]);
          s_in++;
          a[first[f_in]]++;
      }else {
        ret.push_back(second[f_in]);
        f_in++;
      }
  }
  return ret;
}

std::vector<int> MergeArrays(std::vector<std::vector<int> >& arr,int* a) {
  std::vector<int> count(arr.size());
  std::vector<std::vector<int> > arr_s;
  while (arr.size() != 1) {
    arr_s.clear();
    for (int i = 0; i < arr.size(); i += 2) {
      if (i == arr.size() - 1)
        arr_s.push_back(arr[i]);
      else
        arr_s.push_back(Merge2Arrays(arr[i+1], arr[i], a));
    }
    arr = arr_s;
  }
  return arr[0];
}

std::vector<std::vector<int> > SetArrays(std::vector<int>& arr){
  std::vector<std::vector<int> > arrs;
  for(int i = 0;i < arr.size(); i++){
    std::vector<int> a;
    a.push_back(arr[i]);
    arrs.push_back(a);
  }
  return arrs;
}
int main(){
  int n;
  std::cin >> n;
  std::vector<int> arr;
  int* acount = new int[1000000000];
  std::vector<std::vector<int>> arrs;
  int val;
  for(int i = 0 ; i < n ; i++){
    std::cin >> val;
    arr.push_back(val);
  }
  arrs = SetArrays(arr);
  MergeArrays(arrs,acount);
  for(int i = 0;i<n;i++){
   std::cout<<acount[arr[i]]<<std::endl;
  }
  return 0;
}
