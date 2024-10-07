#include <iostream>
#include <string>

class Node {
 public:
  std::string first;
  std::string second;
  Node* left;
  Node* right;
};
class Tree {
 public:
  Node* root;
  void Delete(Node* node) {
    if (node != nullptr) {
      Delete(node->left);
      Delete(node->right);
      delete node;
    }
  }
  Node* Add(std::string first, std::string second) {
    Node* node = new Node;
    node->first = first;
    node->second = second;
    node->left = nullptr;
    node->right = nullptr;
    return node;
  }
  Node* RRotate(Node* node) {
    Node* swp = node->left;
    node->left = swp->right;
    swp->right = node;
    return swp;
  }
  Node* LRotate(Node* node) {
    Node* swp = node->right;
    node->right = swp->left;
    swp->left = node;
    return swp;
  }
  Node* Splay(Node* node, std::string key) {
    if (node == nullptr || node->first == key) {
      return node;
    }
    if (node->first > key) {
      if (node->left == nullptr) {
        return node;
      }
      if (node->left->first > key) {
        node->left->left = Splay(node->left->left, key);
        node = RRotate(node);
      } else if (node->left->first < key) {
        node->left->right = Splay(node->left->right, key);
        if (node->left->right != nullptr) {
          node->left = LRotate(node->left);
        }
      }
      if (node->left == nullptr) {
        return node;
      }
      return RRotate(node);
    }
    if (node->right == nullptr) {
      return node;
    }
    if (node->right->first > key) {
      node->right->left = Splay(node->right->left, key);
      if (node->right->left != nullptr) {
        node->right = RRotate(node->right);
      }
    } else if (node->right->first < key) {
      node->right->right = Splay(node->right->right, key);
      node = LRotate(node);
    }
    if (node->right == nullptr) {
      return node;
    }
    return LRotate(node);
  }
  Node* Insert(Node* node, std::string first, std::string second) {
    if (node == nullptr) {
      return Add(first, second);
    }
    node = Splay(node, first);
    if (node->first == first) {
      return node;
    }
    Node* newnode = Add(first, second);
    if (node->first > first) {
      newnode->right = node;
      newnode->left = node->left;
      node->left = nullptr;
    } else {
      newnode->left = node;
      newnode->right = node->right;
      node->right = nullptr;
    }
    return newnode;
  }
};
int main() {
  Tree tree;
  int num;
  int count;
  std::cin >> num;
  std::string first;
  std::string second;
  std::string qst;
  std::cin >> first >> second;

  tree.root = tree.Add(first, second);
  tree.root = tree.Insert(tree.root, second, first);
  for (int i = 1; i < num; i++) {
    std::cin >> first >> second;
    tree.root = tree.Insert(tree.root, first, second);
    tree.root = tree.Insert(tree.root, second, first);
  }
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    std::cin >> qst;
    tree.root = tree.Splay(tree.root, qst);
    std::cout << tree.root->second << "\n";
  }
  tree.Delete(tree.root);
  return 0;
}
