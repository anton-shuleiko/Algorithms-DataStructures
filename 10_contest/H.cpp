#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

class Trie {
 private:
  class Node {
   public:
    std::map<char, Node*> son;
    std::map<char, Node*> to;
    Node* parent = nullptr;
    Node* link = nullptr;
    Node* comp = nullptr;
    char to_parent;
    bool is_terminal = false;
    std::vector<int> pattern_number;

    Node() : link(this), comp(this) {}
    Node(Node* prnt, char to_prnt) : parent(prnt), to_parent(to_prnt) {}
  };

  Node* root_;
  std::queue<Node*> que_;

 public:
  std::vector<std::string> patterns;
  std::vector<std::vector<size_t>> res;

  Node* GetLink(Node* vert) {
    if (vert->link == nullptr) {
      if (vert == root_ || vert->parent == root_) {
        vert->link = root_;
      } else {
        vert->link = GoTo(GetLink(vert->parent), vert->to_parent);
      }
    }
    return vert->link;
  }

  Node* GoTo(Node* vert, char character) {
    if (vert->to.find(character) == vert->to.end()) {
      if (vert->son.find(character) != vert->son.end()) {
        vert->to[character] = vert->son[character];
      } else if (vert == root_) {
        vert->to[character] = root_;
      } else {
        vert->to[character] = GoTo(
            (vert->link == nullptr ? GetLink(vert) : vert->link), character);
      }
    }
    return vert->to[character];
  }

  Node* GetComp(Node* vert) {
    if (vert->comp == nullptr) {
      if (GetLink(vert)->is_terminal || GetLink(vert) == root_) {
        vert->comp = GetLink(vert);
      } else {
        vert->comp = GetComp(GetLink(vert));
      }
    }
    return vert->comp;
  }

  void AddString(std::string str, int index) {
    Node* curr = root_;
    for (auto symb : str) {
      if (curr->son.find(symb) == curr->son.end()) {
        curr->son[symb] = new Node(curr, symb);
      }
      curr = curr->son[symb];
    }
    curr->is_terminal = true;
    curr->pattern_number.push_back(index);
  }

  void CreateTrie() {
    root_ = new Node();
    int i = 0;
    for (auto str : patterns) {
      AddString(str, i++);
    }
    Node* curr = root_;
    que_.push(root_);
    while (!curr->son.empty()) {
      curr = que_.front();
      que_.pop();
      for (const auto& temp : curr->son) {
        if (temp.second->link == nullptr) {
          GetLink(temp.second);
          que_.push(temp.second);
        }
      }
    }
  }

  void FindPatterns(std::string text) {
    CreateTrie();
    res.resize(patterns.size());
    Node* curr = root_;
    size_t index = 1;
    for (const auto& symb : text) {
      curr = GoTo(curr, symb);
      if (curr->is_terminal) {
        for (const auto& ind : curr->pattern_number) {
          res[ind].push_back(index);
        }
      }
      Node* temp = curr;
      while (GetComp(temp) != root_) {
        temp = temp->comp;
        for (auto ind : temp->pattern_number) {
          res[ind].push_back(index);
        }
      }
      ++index;
    }
  }
};

int main() {
  std::string str;
  size_t pat_num;
  std::string pattern;
  std::cin >> str >> pat_num;
  Trie tree;
  std::vector<size_t> pattern_size;
  for(size_t i = 0; i < pat_num;++i){
    std::cin >> pattern;
    tree.patterns.push_back(pattern);
    pattern_size.push_back(pattern.size());
  }
  tree.FindPatterns(str);
  size_t ind = 0;
  for (const auto& x : tree.res) {
    std::cout << x.size() << " ";
    for(const auto y: x){
      std::cout << y  + 1 - pattern_size[ind]<< " ";
    }
    ind++;
    std::cout <<std::endl;
  }
}