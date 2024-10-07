#include <iostream>

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
  bool SearchNodeKey(int k) {
    for (int i = 0; i < this->n; i++) {
      if (this->key[i] == k) {
        return true;
      }
      if (this->key[i] > k && !this->leaf) {
        return this->c[i]->SearchNodeKey(k);
      }
    }
    if (!this->leaf) {
      return this->c[this->n]->SearchNodeKey(k);
    }
    return false;
  }
  //____________________________________________//
  //____________________________________________//
  //____________________________________________//
  int Next(int k) {
    for (int i = 0; i < this->n; i++) {
      if (this->key[i] == k) {
        return k;
      }
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
    return -1;
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
  BTree(int t) {
    this->t = t;
    this->root = nullptr;
  }
  ///////////Methods///////////////////
  int TNext(int k) {
    if (this->root == nullptr) {
      return -1;
    }
    return this->root->Next(k);
  }
  //_______________________________________//
  bool TSearch(int k) {
    if (this->root == nullptr) {
      return false;
    }
    return this->root->SearchNodeKey(k);
  }
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
  char oper;
  int key;
  int lastres;
  const int kMax = 1000000000;
  void DoIt(BTree* tree) {
    if (this->oper == '+') {
      tree->Insert((this->key + this->lastres) % kMax);
      this->lastres = 0;
    } else if (this->oper == '?') {
      this->lastres = tree->TNext(this->key);
      std::cout << this->lastres << std::endl;
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  BTree* tree = new BTree(263);
  Command* cmd = new Command;
  cmd->lastres = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> cmd->oper >> cmd->key;
    cmd->DoIt(tree);
  }
  tree->TDelete();
  delete tree;
  delete cmd;
}
