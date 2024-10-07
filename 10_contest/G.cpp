#include <iostream>
#include <string>
#include <vector>

class Trie {
 private:
  class Node {
   public:
    Node* son[2];
    Node* to[2];
    Node* parent = nullptr;
    Node* link = nullptr;
    char to_parent;
    bool is_terminal = false;

    Node() : link(this) {

    }
    Node(Node* prnt, char to_prnt) : parent(prnt), to_parent(to_prnt) {

    }
  };

  Node* root_;
  std::vector<Node*> nodes;

 public:
  ~Trie(){
    for(auto& x: nodes){
      delete x;
    }
  }
  std::vector<std::string> patterns;
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

  Node* GoTo(Node* vert, const char& symb) {
    if (vert->to[symb-'0'] == nullptr) {
      if (vert->son[symb-'0'] != nullptr) {
        vert->to[symb-'0'] = vert->son[symb-'0'];
      } else if (vert == root_) {
        vert->to[symb-'0'] = root_;
      } else {
        vert->to[symb-'0'] = GoTo(GetLink(vert), symb);
      }
    }
    return vert->to[symb-'0'];
  }

  void AddString(std::string& str, int index) {
    Node* curr = root_;
    for (auto symb : str) {
      if (curr->son[symb - '0'] == nullptr) {
        curr->son[symb - '0'] = new Node(curr, symb);
        nodes.push_back(curr->son[symb - '0']);
      }
      curr = curr->son[symb-'0'];
    }
    curr->is_terminal = true;
  }

  void Work() {
    root_ = new Node();
    nodes.push_back(root_);
    int i = 0;
    for (auto str : patterns) {
      AddString(str, i++);
    }
    if (Check(root_, "")) {
      std::cout << "TAK" << std::endl;
      return;
    }
    std::cout << "NIE" << std::endl;
  }
  bool Check(Node* curr, std::string txt) {
    int k = 0;
    if (GoTo(curr, '1')->parent != curr) {
      if (!FindPatterns((txt +'1')+ (txt +'1')+(txt +'1'))) {
        return true;
      }
      
    }
    if (GoTo(curr, '0')->parent != curr) {
      if (!FindPatterns((txt +'0')+ (txt +'0')+(txt +'0'))) {
        return true;
      }
    }
    if (!GoTo(curr, '0')->is_terminal) {
      if (Check(GoTo(curr, '0'), txt + '0')) {
        return true;
      }
    }
    if (!GoTo(curr, '1')->is_terminal) {
      if (Check(GoTo(curr, '1'), txt + '1')) {
        return true;
      }
    }

    return false;
  }

  bool FindPatterns(const std::string& text) {
    Node* curr = root_;
    for (auto& symb : text) {
      curr = GoTo(curr, symb);
      if (curr->is_terminal) {
        return true;
      }
    }
    return false;
  }
};

int main() {
  int16_t num;
  std::cin >> num;
  Trie tree;
  for (int16_t i = 0; i < num; ++i) {
    std::string pattern;
    std::cin >> pattern;
    tree.patterns.push_back(pattern);
  }
  tree.Work();
}