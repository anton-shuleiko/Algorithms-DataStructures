#include <iostream>
#include <string>
const int kMin = -1000000001;
class Node {
 public:
  int t;      // Порядок Дерева
  int n;      // количество ключей
  int* key;   //ключи
  Node** c;   // дети
  bool leaf;  // являеться ли узел Листом или нет
  ///////////////////////////////////////////////
  //////////Constructors/////////////////////////
  Node(int nt, bool nleaf) {
    this->t = nt;
    this->leaf = nleaf;
    this->key = new int[2 * nt - 1];
    this->c = new Node*[2 * nt];
    for (int i = 0; i < 2 * nt; i++) {
      this->c[i] = nullptr;
    }
    this->n = 0;
  }
  ////////////Methods/////////////////////////////

  Node* SearchNodeKey(int k) {
    for (int i = 0; i < this->n; i++) {
      if (this->key[i] == k) {
        return this;
      }
      if (this->key[i] > k && !this->leaf) {
        return this->c[i]->SearchNodeKey(k);
      }
    }
    if (!this->leaf) {
      return this->c[this->n]->SearchNodeKey(k);
    }
    return nullptr;
  }
  //____________________________________________//
  //____________________________________________//
  //____________________________________________//
  int Next(int k) {
    for (int i = 0; i < this->n; i++) {
      if (this->key[i] > k &&
          (this->leaf ||
           (this->c[i]->key[this->c[i]->n - 1] < k && this->c[i]->leaf))) {
        return this->key[i];
      }
      if (this->key[i] > k && !this->leaf) {
        return this->c[i]->Next(k);
      }
    }
    if (!this->leaf) {
      return this->c[this->n]->Next(k);
    }
    return kMin;
  }
  //_________________________________________//
  //_________________________________________//
  //_________________________________________//
  int Prev(int k) {
    for (int i = this->n - 1; i >= 0; i--) {
      if (this->key[i] < k && (this->leaf || (this->c[i + 1]->key[0] > k &&
                                              this->c[i + 1]->leaf))) {
        return this->key[i];
      }
      if (this->key[i] < k && !this->leaf) {
        return this->c[i + 1]->Next(k);
      }
    }
    if (!this->leaf) {
      return this->c[0]->Next(k);
    }
    return kMin;
  }
  //_________________________________________//
  //_________________________________________//
  //_________________________________________//

  void SplitChild(int i) {  //разбиваем i-ого ребенка на 2 узла
    Node* y = this->c[i];  // находим i-ого ребенка
    Node* z = new Node(y->t, y->leaf);

    //передаем последние t-1 ключей узла Y узлу Z//
    for (int j = 0; j < y->t - 1; j++) {
      z->key[j] = y->key[j + t];
    }
    //если не является листом передаем последние t детей узла Y узлу Z//
    if (!y->leaf) {
      for (int j = 0; j < y->t; j++) {
        z->key[j] = y->key[j + t];
      }
    }
    //задаем количество ключей новых узлов//
    z->n = z->t - 1;
    y->n = y->t - 1;

    //Освобаждаем место нового полученного ребенка//
    for (int j = this->n; j >= i + 1; j--) {
      this->c[j + 1] = c[j];
    }
    //добавим нового ребенка
    this->c[i + 1] = z;
    //Освобождаем место для нового ключа//
    for (int j = this->n - 1; j >= i; j--) {
      this->key[j + 1] = this->key[j];
    }
    //добавим новый ключ//
    this->key[i] = y->key[y->n];
    this->n++;
  }
  //_________________________________________//
  //_________________________________________//
  //_________________________________________//
  void InsertNF(int k) {  // добавление в неполный узел
    int i = this->n - 1;
    if (this->leaf) {  //Если лист то находим место и ставим//
      while (i >= 0 && this->key[i] > k) {
        this->key[i + 1] = this->key[i];
        i--;
      }
      this->key[i + 1] = k;
      this->n++;
    } else {  //если не лист то переходим на нужного ребенка и пытаемся
              //поставить в него
      while (i >= 0 && this->key[i] > k) {
        i--;
      }
      //проверяем является ли данный ребенок полный и если да до делим на две
      //части
      if (this->c[i + 1]->n == 2 * this->t - 1) {
        this->SplitChild(i + 1);
        //потом находим уже нужного ребенка
        if (this->key[i + 1] < k) {
          i++;
        }
      }

      //пытаемся поставить в него
      this->c[i + 1]->InsertNF(k);
    }
  }
  //____________________________________________________//
  //____________________________________________________//
  //____________________________________________________//
  void Merge(int i) {
    Node* ch1 = this->c[i];
    Node* ch2 = this->c[i + 1];

    ch1->key[this->t - 1] = this->key[i];

    for (int j = 0; j < ch2->n; j++) {
      ch1->key[j + this->t] = ch2->key[j];
    }
    if (!ch1->leaf) {
      for (int j = 0; j <= ch2->n; j++) {
        ch1->c[j + this->t] = ch2->c[j];
      }
    }

    for (int j = i + 1; j < this->n - 1; j++) {
      this->key[j] = this->key[j + 1];
    }
    for (int j = i + 2; j <= this->n; j++) {
      this->c[j] = this->c[j + 1];
    }
    ch1->n += ch2->n + 1;
    this->n--;
    delete[] ch2->key;
    delete[] ch2->c;
    delete ch2;
  }
  //____________________________________________________//
  //____________________________________________________//
  //____________________________________________________//
  void Remove(int k) {
    if (this->n == 0) {
      return;
    }
    int index = 0;
    while (index < this->n && this->key[index] < k) {
      ++index;
    }
    if (index < this->n && this->key[index] == k) {
      if (this->leaf) {
        this->RemoveFromLeaf(index);
      } else {
        this->RemoveFromNonLeaf(index);
      }
    } else {
      bool flag = (index == this->n);

      if (this->c[index]->n < t) {
        this->fill(index);
      }

      if (flag && index > this->n) {
        this->c[index - 1]->Remove(k);
      } else {
        this->c[index]->Remove(k);
      }
    }
  }

  void RemoveFromLeaf(int index) {
    for (int i = index + 1; i < this->n; ++i) {
      this->key[i - 1] = this->key[i];
    }
    this->n--;
  }

  void RemoveFromNonLeaf(int index) {
    int k = this->key[index];
    if (this->c[index]->n >= this->t) {
      int pred = this->getPred(index);
      this->key[index] = pred;
      this->c[index]->Remove(pred);
    } else if (this->c[index + 1]->n >= this->t) {
      int succ = this->getSucc(index);
      this->key[index] = succ;
      this->c[index + 1]->Remove(succ);
    } else {
      this->Merge(index);
      this->c[index]->Remove(k);
    }
  }

  int getPred(int index) {
    Node* cur = this->c[index];
    while (!cur->leaf) {
      cur = cur->c[cur->n];
    }
    return cur->key[cur->n - 1];
  }

  int getSucc(int index) {
    Node* cur = this->c[index + 1];
    while (!cur->leaf) {
      cur = cur->c[0];
    }
    return cur->key[0];
  }

  void fill(int index) {
    if (index != 0 && this->c[index - 1]->n >= this->t) {
      BorrowFromPrev(index);
    } else if (index != this->n && this->c[index + 1]->n >= this->t) {
      BorrowFromNext(index);
    } else {
      if (index != this->n)
        this->Merge(index);
      else
        this->Merge(index - 1);
    }
  }

  void BorrowFromPrev(int index) {
    Node* child = c[index];
    Node* sibling = c[index - 1];

    for (int i = child->n - 1; i >= 0; --i) {
      child->key[i + 1] = child->key[i];
    }
    if (!child->leaf) {
      for (int i = child->n; i >= 0; --i) child->c[i + 1] = child->c[i];
    }
    child->key[0] = this->key[index - 1];
    if (!child->leaf) {
      child->c[0] = sibling->c[sibling->n];
    }
    this->key[index - 1] = sibling->key[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
  }
  void BorrowFromNext(int index) {
    Node* child = c[index];
    Node* sibling = c[index + 1];
    child->key[(child->n)] = this->key[index];
    if (!(child->leaf)) {
      child->c[(child->n) + 1] = sibling->c[0];
    }
    this->key[index] = sibling->key[0];
    for (int i = 1; i < sibling->n; ++i) {
      sibling->key[i - 1] = sibling->key[i];
    }
    if (!sibling->leaf) {
      for (int i = 1; i <= sibling->n; ++i) sibling->c[i - 1] = sibling->c[i];
    }
    child->n += 1;
    sibling->n -= 1;
  }
};

/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class BTree {
 public:
  int t;       // Порядок Дерева
  Node* root;  // Корень Дерева
  //////////////////////////////////////
  ///////////Constructors///////////////
  BTree(int nt) {
    this->t = nt;
    this->root = nullptr;
  }
  ///////////Methods///////////////////
  int TNext(int k) {
    if (this->root == nullptr) {
      return kMin;
    }
    return this->root->Next(k);
  }
  int TPrev(int k) {
    if (this->root == nullptr) {
      return kMin;
    }
    return this->root->Prev(k);
  }
  //_______________________________________//
  bool TSearch(int k) {
    if (this->root == nullptr) {
      return false;
    }
    return this->root->SearchNodeKey(k) != nullptr;
  }
  //_______________________________________//
  void Insert(int k) {
    // если нету корня создаем и даем первый ключ k
    if (this->root == nullptr) {
      this->root = new Node(this->t, true);
      this->root->key[0] = k;
      this->root->n = 1;
    } else if (!this->TSearch(k)) {  // если есть корень и нету ключа равному k

      //проверяем если корень полон (т.е. дерево полно уже)
      if (this->root->n == 2 * this->t - 1) {
        Node* s = new Node(this->t, false);
        s->c[0] = root;  // предидущий корень сын нового
        //то делим старый корень на 2 части и создаем новый корень с 2
        //детьми которые произашли из предыдущего корня
        s->SplitChild(0);
        if (s->key[0] < k) {
          s->c[1]->InsertNF(k);
        } else {
          s->c[0]->InsertNF(k);
        }
        this->root = s;
      } else {
        this->root->InsertNF(k);  //если корень не полон ставим в искомое дерево
      }
    }
  }

  //____________________________________________________//
  void DeleteNode(Node* node) {
    if (node != nullptr) {
      if (!node->leaf) {
        for (int i = 0; i <= node->n; i++) {
          DeleteNode(node->c[i]);
        }
      }
      delete[] node->key;
      delete[] node->c;
      delete node;
    }
  }
  //____________________________________________________//
  //____________________________________________________//
  //____________________________________________________//
  void TDelete() { DeleteNode(this->root); }

  //____________________________________________________//
  //____________________________________________________//
  //____________________________________________________//
  int KthStatistics(int k) {
    if (this->root == nullptr) {
      return kMin;
    }
    Node* curr = this->root;
    while (!curr->leaf) {
      curr = curr->c[0];
    }
    int result = curr->key[0];
    for (int i = 0; i < k; i++) {
      result = this->TNext(result);
    }
    return result;
  }
  //____________________________________________________//
  //____________________________________________________//
  //____________________________________________________//
  /*void Print(Node* node){
    if(node!=nullptr ){
      for(int i = 0; i < node->n; i++){
        std::cout << node->key[i] << " ";
      }
      std::cout<<std::endl;
      if(!node->leaf){
        for(int i = 0; i <= node->n; i++){
          Print(node->c[i]);
        }
      }
    }
  }*/
};
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class Command {
 public:
  std::string oper;
  int key;
  int res;
  const int kMax = 1000000000;
  void DoIt(BTree* tree) {
    if (this->oper == "insert") {
      tree->Insert(this->key);
    } else if (this->oper == "next") {
      this->res = tree->TNext(this->key);
      if (res == kMin) {
        std::cout << "none" << std::endl;
      } else {
        std::cout << this->res << std::endl;
      }
    } else if (this->oper == "prev") {
      this->res = tree->TPrev(this->key);
      if (res == kMin) {
        std::cout << "none" << std::endl;
      } else {
        std::cout << this->res << std::endl;
      }
    } else if (this->oper == "delete") {
      if (tree->root != nullptr) {
        tree->root->Remove(key);
      }
    } else if (this->oper == "exists") {
      if (tree->TSearch(key)) {
        std::cout << "true" << std::endl;
      } else {
        std::cout << "false" << std::endl;
      }
    } else if (this->oper == "kth") {
      res = tree->KthStatistics(key);
      if (res == kMin) {
        std::cout << "none" << std::endl;
      } else {
        std::cout << this->res << std::endl;
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  BTree* tree = new BTree(4999);
  Command* cmd = new Command;
  cmd->res = 0;
  while (std::cin >> cmd->oper) {
    std::cin >> cmd->key;
    cmd->DoIt(tree);
  }
  tree->TDelete();
  delete tree;
  delete cmd;
}
