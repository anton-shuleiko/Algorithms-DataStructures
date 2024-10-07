#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

void Dijkstra(int start, std::vector<std::vector<std::pair<size_t,int>>>& g, std::vector<int>& d,int up, int down) {
    d[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >,
                        std::greater<std::pair<int, int> > >
        queue;  // dist, vertex
    size_t curr;
    queue.push(std::make_pair(d[start], start));

    while (!queue.empty()) {
      curr = queue.top().second;
      queue.pop();
      
      for (const auto& edge : g[curr]) {
        if (d[edge.first] > d[curr] + edge.second) {
          d[edge.first] = d[curr] + edge.second;
          queue.push(std::make_pair(d[edge.first], edge.first));
        }
      }
      if(curr < 999999){
        if (d[curr+1] > d[curr] + up) {
          d[curr+1] = d[curr] + up;
          queue.push(std::make_pair(d[curr+1], curr+1));
        }
        if(curr > 0){
          if (d[curr-1] > d[curr] + down) {
            d[curr-1] = d[curr] + down;
            queue.push(std::make_pair(d[curr-1], curr-1));
            }
        }

      }
      
    }
  }

int Find(std::vector<std::vector<std::pair<size_t,int>>> ship, size_t f1, size_t f2){
  for(size_t i = 0 ;i< ship[f1].size();++i){
    if(ship[f1][i].first == f2){
      return i;
    }
  }
  return -1;
}
int main(){
  size_t num,up,down,in,out,teleports;
  std::cin >> num >> up>> down >> in>> out>> teleports;
  std::vector<std::vector<std::pair<size_t,int>>> ship(1000000+teleports);
  for(size_t i = 0 ; i < teleports; ++i){
    size_t knum;
    std::cin >> knum;
    for(size_t j = 0; j < knum; ++j){
      size_t x = 0;
      std::cin >> x;
      ship[i+1000000].push_back({x-1,in});
      ship[x-1].push_back({1000000+i,out});
    }
    

  }
  std::vector<int> d(1000000+teleports,INT32_MAX);
  Dijkstra(0, ship, d,up,down);
  std::cout << d[num-1];
}