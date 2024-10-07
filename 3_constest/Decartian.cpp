#include <iostream>
#include <vector>

typedef struct Node {
  int key;
  int number;
  int prior;
  Node* parent;
  Node* right;
  Node* left;
  Node(int ky, int pr, int num) {
    this->key = ky;
    this->number = num;
    this->prior = pr;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
  }
} Node;

Node* Insert(Node* node, int x, int y, int num);
void Print(std::vector<Node*>& nodes);
void PrintNode(Node* node);
void Clear(std::vector<Node*>& vec);


Node* Insert(Node* node, int x, int y, int num) {
  if (node == nullptr) {
    node = new Node(x, y, num);
    return node;
  }
  if (y > node->prior) {
    Node* nd = new Node(x, y, num);
    nd->left = node->right;
    if (node->right != nullptr) {
      node->right->parent = nd;
    }
    nd->parent = node;
    node->right = nd;
    return nd;
  }  
  if (node->parent == nullptr) {
    node->parent = new Node(x, y, num);
    node->parent->left = node;
    return node->parent;
  }
  return Insert(node->parent, x, y, num);
}  

void Clear(std::vector<Node*>& vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    delete vec[i];
  }
}

void PrintNode(Node* node) {
  if (node == nullptr) {
    std::cout << 0;
  } else {
    std::cout << node->number;
  }
}
void Print(std::vector<Node*>& nodes) {
  for (size_t i = 0; i < nodes.size(); i++) {
    PrintNode(nodes[i]->parent);
    std::cout << " ";
    PrintNode(nodes[i]->left);
    std::cout << " ";
    PrintNode(nodes[i]->right);
    std::cout << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  int k, p;
  Node* node = nullptr;
  std::vector<Node*> nodes;
  for (int i = 0; i < n; i++) {
    std::cin >> k >> p;
    node = Insert(node, k, p, i + 1);
    nodes.push_back(node);
  }
  std::cout << "YES" << std::endl;
  Print(nodes);
  Clear(nodes);
}
//
