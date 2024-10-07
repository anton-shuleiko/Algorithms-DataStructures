#include <iostream>

void Push(char value, struct Stack* stck);
char Pop(struct Stack* stck);
int CheckSkob(struct Stack* stck, char skob);
void Clear(struct Stack* stck);

struct Stack {
  int size = 0;
  struct box* first_element;
};

struct box {
  char value;
  struct box* next;
};

int main() {
  char* skobki = new char[100000];
  struct Stack* stck = new struct Stack;
  std::cin.getline(skobki, 1000000);
  char* sk = skobki;
  while(*sk != '\0'){
    if(CheckSkob(stck, *sk) == 0) {
      std::cout << "NO" << std::endl;
      delete[] skobki;
      Clear(stck);
      delete stck;
      return 0;
    }
    sk++;
  }
  if(stck->size == 0) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  delete[] skobki;
  Clear(stck);
  delete stck;
  return 0;
}

void Clear(struct Stack* stck) {
  while (stck->size > 0) {
    Pop(stck);
  }
}

void Push(char value, struct Stack* stck) {
  struct box* new_element = new struct box;
  new_element->value = value;
  new_element->next = stck->first_element;
  stck->first_element = new_element;
  stck->size++;
}

char Pop(struct Stack* stck) {
  if(stck->size == 0) {
    return 'X';
  }
  struct box* pop_element = stck->first_element;
  char val = pop_element->value;
  stck->first_element = pop_element->next;
  stck->size--;
  delete pop_element;
  return val;
}

int CheckSkob(struct Stack* stck, char skob) {
  if(skob == '{' || skob == '(' || skob == '['){
    Push(skob, stck);
    return 1;
  } 
  switch(skob) {
    case '}':
      if(Pop(stck) != '{'){
        return 0;
      }
      break;
    case ']':
      if(Pop(stck) != '['){
        return 0;
      }
      break;
    case ')':
      if(Pop(stck) != '('){
        return 0;
      }
      break;
  }
  return 1;
}