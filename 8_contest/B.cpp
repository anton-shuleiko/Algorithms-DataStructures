#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

class Euristic {
 public:
  std::vector<size_t> parent;
  std::vector<size_t> power;
  size_t size;

  Euristic(size_t size) {
    parent.resize(size, 0);
    power.resize(size, 0);
    for (size_t i = 0; i < size; i++) {
      make_set(i);
    }
  }

  size_t find_set(size_t& v) {
    size_t root = v;
    while (root != parent[root]) root = parent[root];
    while (v != root) {
      size_t p = parent[v];
      parent[v] = root;
      v = p;
    }
    return root;
  }

  void make_set(size_t v) {
    parent[v] = v;
    power[v] = 0;
  }

  void union_sets(size_t& a, size_t& b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (power[a] < power[b]) std::swap(a, b);
      parent[b] = a;
      power[a] += power[b]+1;
      if (power[a] == power[b]) {
        power[a]++;
      }
    } else {
      power[a] ++;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t size = 0;
  size_t esize = 0;
  size_t reqsize = 0;
  std::vector<std::pair<std::string,std::pair<size_t,size_t>>> requests;
  std::cin >> size >> esize >> reqsize;
  Euristic trees(size);
  for(size_t i = 0 ; i < esize; ++i){
    size_t x,y;
    std::cin >> x >> y;
  }  
  for(size_t i = 0 ; i < reqsize; ++i){
    std::string req;
    size_t x,y;
    std::cin >>req >> x >> y;
    requests.push_back({req,{x-1,y-1}});
  } 
  std::vector<bool> answer;
  for(size_t i = reqsize; i > 0; --i){
    if(requests[i-1].first == "cut"){
      trees.union_sets(requests[i-1].second.first,requests[i-1].second.second);
    }else{
      if(trees.find_set(requests[i-1].second.first) == trees.find_set(requests[i-1].second.second)){
        answer.push_back(true);
      }else{
        answer.push_back(false);
      }
    }
  }
  for(size_t i = answer.size(); i > 0; --i){
    answer[i-1] ? std::cout << "YES\n" : std::cout << "NO\n";
  }
}