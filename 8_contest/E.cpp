#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

class Euristic {
 public:
  std::vector<int> parent;
  std::vector<int> power;
  std::vector<bool> used;
    
  int weight = 0;
  std::vector<std::vector<std::pair<int,int>>> mst;
  std::vector <std::pair<int,std::pair<int,int>>> graph;
  int size = 0;

  Euristic(int size) {
    parent.resize(size, 0);
    power.resize(size, 0);
    mst.resize(size);
    used.resize(size, false);
    for (int i = 0; i < size; i++) {
      make_set(i);
    }
  }

  int find_set(int& v) {
    return (v == parent[v]) ? v : (parent[v] = find_set (parent[v]));;
  }

  void make_set(int v) {
    parent[v] = v;
    power[v] = 0;
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    parent[a] = a!=b?b:parent[a];
  }

  void AddMstEdge(std::pair<int,int> edge, int len){
    mst[edge.first].push_back({len, edge.second});
    mst[edge.second].push_back({len, edge.first});
  }
  void Cruscal(int requests){
    std::sort(graph.begin(),graph.end());
    for (int i=0; i<requests; ++i) {
      if (find_set(graph[i].second.first) != find_set(graph[i].second.second)) {
        weight += graph[i].first;
        AddMstEdge(graph[i].second,-graph[i].first);
        union_sets(graph[i].second.first, graph[i].second.second);
      }
    }
  }

  int FindWay(int start,int finish, int cost){
    if(start == finish){
      return cost;
    }
    
    used[start] = true;
    int res = 0;
    for(const auto& v: mst[start]){
      if(!used[v.second]){
        res = FindWay(v.second,finish,std::min(cost,v.first));
        if(res > 0){
          return std::min(res,cost);
        }
        
      }
    }
    return res;
  }
};

int main() {
  int vert_num = 0;
  int edge_num = 0;
  int req_num = 0;
  std::cin >> vert_num >> edge_num >> req_num;
  Euristic grph(vert_num);
  for(int i = 0; i < edge_num; ++i){
    int first, second, len;
    std::cin >> first >> second >> len;
    grph.graph.push_back({-len,{first-1,second-1}});
  }
  grph.Cruscal(edge_num);
  std::cout  << -grph.weight <<std::endl;
  for(int i = 0; i < req_num; ++i){
    int start, finish;
    std::cin >>start>>finish;
    grph.used.assign(vert_num,false);
    std::cout << grph.FindWay(start-1,finish-1,INT32_MAX) <<std::endl;
  }
  return 0;
}