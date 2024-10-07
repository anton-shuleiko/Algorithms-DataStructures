#include <iostream>

#include <string>

void Push(int value, struct Stack* stck);
int Pop(struct Stack* stck);
void Back(struct Stack* stck);
void Clear(struct Stack* stck);
void Command(std::string cmmnd, struct Stack* stck);
int Minim(struct Stack* stck);

struct Stack {
  int size = 0;
  struct box* first_element;
};

struct box {
  int value;
  int mini;
  struct box* next;
};

int main() {
  int cmmndsize;
  std::string commands;
  struct Stack* stck = new struct Stack;
  std::cin >> cmmndsize;
  for (int iter = 0; iter < cmmndsize; iter++) {
    std::cin >> commands;
    Command(commands, stck);
  }
  Clear(stck);
  delete stck;
  return 0;
}

void Push(int value, struct Stack* stck) {
  struct box* new_element = new struct box;
  if ((stck->size == 0) || (stck->first_element->mini > value)) {
    new_element->mini = value;
  } else {
    new_element->mini = stck->first_element->mini;
  }
  new_element->value = value;
  new_element->next = stck->first_element;
  stck->first_element = new_element;
  stck->size++;
  std::cout << "ok" << std::endl;
}

int Pop(struct Stack* stck) {
  struct box* pop_element = stck->first_element;
  int val = pop_element->value;
  stck->first_element = pop_element->next;
  stck->size--;
  delete pop_element;
  return val;
}

void Back(struct Stack* stck) {
  std::cout << stck->first_element->value << std::endl;
}

void Clear(struct Stack* stck) {
  while (stck->size > 0) {
    Pop(stck);
  }
}

void Command(std::string cmmnd, struct Stack* stck) {
  if (cmmnd == "push") {
    int n;
    std::cin >> n;
    Push(n, stck);
  } else if (cmmnd == "size") {
    std::cout << stck->size << std::endl;
  } else if (cmmnd == "clear") {
    Clear(stck);
    std::cout << "ok" << std::endl;
  } else if (stck->size == 0) {
    std::cout << "error" << std::endl;
  } else if (cmmnd == "pop") {
    std::cout << Pop(stck) << std::endl;
  } else if (cmmnd == "back") {
    Back(stck);
  } else if (cmmnd == "min") {
    std::cout << stck->first_element->mini << std::endl;
  }
}