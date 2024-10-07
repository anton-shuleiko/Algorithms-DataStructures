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
    char to_parent;
    bool is_terminal = false;

    Node() : link(this) {}
    Node(Node* prnt, char to_prnt) : parent(prnt), to_parent(to_prnt) {}
  };

  Node* root_;

 public:
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

  Node* GoTo(Node* vert, char character) {
    if (vert->to.find(character) == vert->to.end()) {
      if (vert->son.find(character) != vert->son.end()) {
        vert->to[character] = vert->son[character];
      } else if (vert == root_) {
        vert->to[character] = root_;
      } else {
        vert->to[character] = GoTo(GetLink(vert), character);
      }
    }
    return vert->to[character];
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
  }

  void Work() {
    root_ = new Node();
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
      txt += '1';
      if (!FindPatterns(txt + txt + txt)) {
        return true;
      }
    }
    if (GoTo(curr, '0')->parent != curr) {
      txt += '0';
      if (!FindPatterns(txt + txt + txt)) {
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

  bool FindPatterns(std::string text) {
    Node* curr = root_;
    for (const auto& symb : text) {
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