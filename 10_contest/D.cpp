#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
class Trie{
  public:
    class Node{
     public:
      std::unordered_map<char,Node*> children;
      bool is_terminal = false;
      int index = -1;
      Node()=default;
    };

    Node* root;
  
    Trie(): root(new Node()){}
    
    
    void AddString(std::string word, int index){
      Node* node = root;
      for(auto chr: word) {
          if(node->children.find(chr) == node->children.end()){
            node->children [ chr ] = new Node();
          }
              
          node = node->children [ chr ];
      }
      node->is_terminal = true;
      node->index = index;
    }

    std::pair<bool, int> search(std::string word){
      Node* node = root;
      for(auto chr: word) {
        if(node->children.find(chr) == node->children.end()){
          return {false,-1};
        }
        node = node->children[chr];
      }
      return {node->is_terminal,node->index};
    }

};
bool isPalindrome(const std::string& str) {
    int i = 0, j = str.length() - 1;
    while (i < j) {
        if (str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

void PairPolindrome(std::vector<std::string> words){
  Trie tri = Trie();
  for(int i = 0 ;i < words.size();++i) {
    tri.AddString(words[i],i);
  }
  std::set<std::pair<int,int>> valid_pals;
  for(int i = 0 ;i < words.size();++i) {
    size_t m = words[i].length();
    for(int k=0; k <= m ;++k){
      std::string prefix = words[i].substr(0,k);
      std::string suffix = words[i].substr(k);
      std::string reversed_suffix = suffix;
      std::reverse(reversed_suffix.begin(),reversed_suffix.end());
      std::string reversed_prefix = prefix;
      std::reverse(reversed_prefix.begin(),reversed_prefix.end());
      if(isPalindrome(prefix)){
        std::pair<bool,int> search_index = tri.search(reversed_suffix);
        if(search_index.first && search_index.second != i){
          valid_pals.insert({search_index.second,i});
        }
      }
      if(k!=m && isPalindrome(suffix)){
        std::pair<bool,int> search_index = tri.search(reversed_prefix);
        if(search_index.first && search_index.second != i){
          valid_pals.insert({i,search_index.second});
        }
      }
    }
  }
  std::cout << valid_pals.size()<<std::endl;
  
  for(auto& valp: valid_pals){
    std::cout << valp.first+1 << " " <<valp.second+1<<std::endl;
  }
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin  >> n;
  std::vector<std::string> words(n);
  for(size_t i = 0 ;i < n ;++i){
    std::cin >> words[i];
  }
  PairPolindrome(words);
}