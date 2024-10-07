#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>


  
  std::vector<std::vector<std::pair<int16_t, int16_t>>> list;

 
  bool MaxFlowBFS(int16_t st, int16_t tgt, int16_t vsize, std::vector<int16_t>& parent) {
    std::vector<bool> used(vsize, false);
    std::queue<int16_t> queue;
    queue.push(st);
    used[st] = true;
    parent[st] = -1;

    while (!queue.empty()) {
      int16_t from = queue.front();
      queue.pop();
      for(size_t i = 0; i < list[from].size();++i) {
        int16_t to = list[from][i].first;
        int16_t capacity = list[from][i].second;

        if (!used[to] && capacity > 0) {
          used[to] = true;
          parent[to] = from;
          queue.push(to);
        }
      }
    }

    return used[tgt];
  }

  int16_t MaxFlow(int16_t vsize) {
    int16_t st = 0;
    int16_t tgt = vsize - 1;
    int16_t max_flow = 0;
    std::vector<int16_t> parent(vsize);

    while (MaxFlowBFS(st, tgt, vsize,parent)) {
      int16_t path_flow = INT16_MAX;
      for (int16_t to = tgt; to != st;
           to = parent[to]) {
        int16_t from = parent[to];
        for(size_t i = 0; i < list[from].size(); ++i) {
          if (list[from][i].first == to) {
            path_flow = std::min(path_flow, list[from][i].second);
            list[from][i].second -= path_flow;
            break;
          }
        }

        bool edge_exists = false;
        for(size_t i = 0; i < list[to].size(); ++i) {
          if (list[to][i].first == from) {
            list[to][i].second += path_flow;
            edge_exists = true;
            break;
          }
        }

        if (!edge_exists) {
          list[to].push_back({from, path_flow});
        }
      }
      max_flow += path_flow;
    }

    return max_flow;
  }

  void WorkInLoop(int16_t i, int16_t j, int16_t vsize,int16_t nnum, std::vector<std::string>& board){
    int16_t index = i * nnum + j + 1;
        if ((j > 0) && (board[i][j - 1] == '*')) {
          if((i + j) % 2 == 1) {
            list[index].push_back({index - 1, 1});
          } else {
            list[index - 1].push_back({index, 1});
          }
                            
          
        }

        if ((i > 0) && (board[i - 1][j] == '*')) {
          if((i + j) % 2 == 1){
            list[index].push_back({index - nnum, 1});
          }else{
            list[index - nnum].push_back({index, 1});
          } 
        }

        if((i + j) % 2 == 1){
          list[0].push_back({index, 1});
        } else {
          list[index].push_back({vsize - 1, 1});
        }
           
  }

  void OutPut(int16_t vsize,int16_t stcount,int16_t f_cap,int16_t s_cap) {
    int16_t res = 0;
    res = MaxFlow(vsize);

    if (f_cap < 2 * s_cap) {
      std::cout << res * f_cap +
                       (stcount - 2 * res) * s_cap;
    } else {
      std::cout << stcount * s_cap;
    }
  }

  void StartWork() {
    std::vector<std::string> board;
    int16_t vsize = 0;
    int16_t f_cap = 0;
    int16_t s_cap = 0;
    int16_t mnum = 0;
    int16_t nnum = 0;
    std::cin >> mnum >> nnum >> f_cap >> s_cap;
    int16_t stcount = 0;
    list.resize(mnum * nnum + 2);

    board.assign(mnum, std::string(nnum, 'x'));

    for (int16_t i = 0; i < mnum; ++i) {
      for (int16_t j = 0; j < nnum; ++j) {
        std::cin >> board[i][j];
        if (board[i][j] == '.') {
          continue;
        }
        ++stcount;
        WorkInLoop(i,j,mnum * nnum + 2,nnum,board);
      }
    }
    OutPut(mnum * nnum + 2,stcount,f_cap,s_cap);
  }

  
int main() {

  StartWork();
  return 0;
}
