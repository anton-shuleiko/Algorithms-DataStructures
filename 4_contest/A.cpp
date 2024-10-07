#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
void Add(std::vector<std::pair<uint16_t, size_t>>& elements,std::vector<bool>& used, uint16_t val, size_t index);
std::vector<std::pair<uint16_t, size_t>> elements;
std::vector<bool> used(100000,0);

void Add(std::vector<std::pair<uint16_t, size_t>>& elements,std::vector<bool>& used, uint16_t val, size_t index){
  if(!used[index]){
    elements.push_back(std::pair(val,index));
  }else{
    for(int i = 0; i < elements.size(); i++){
      if(elements[i].second == index){
        elements[i].first = val;
        break;
      }
    }
    used[index] = true;
  }
  std::sort(elements.begin(), elements.end());
}

double Checkout(std::vector<std::pair<uint16_t, size_t>>& elements,std::vector<bool>& used, size_t index){
  if(elements.size() == 1 && )
  for(size_t i = 0; i < elements.size();i++){
    if(elements[i].second == index){
      size_t j = i - 1;
      while(elements[j].first == elements[i].first && j != 0){
        j--;
      }
      if(j == 0 && elements[j].first == elements[i].first){
        return 0;
      }
    }
  }
}
