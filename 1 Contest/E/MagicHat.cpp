#include <iostream>

#include <algorithm>

#include <string>

void Push(int value, struct Stack* stck);
int Pop(struct Stack* stck);
void Back(struct Queue* que);
void Clear(struct Stack* stck);
void Command(std::string cmmnd, struct Queue* que);
void Enqueue(int value, struct Queue* que);
int Dequeue(struct Queue* que);

struct Queue {
  struct Stack* st1;
  struct Stack* st2;
};

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
  struct Stack* st1 = new struct Stack;
  struct Stack* st2 = new struct Stack;
  Queue* que = new Queue;
  que->st1 = st1;
  que->st2 = st2;
  std::cin >> cmmndsize;
  for (int iter = 0; iter < cmmndsize; iter++) {
    std::cin >> commands;
    Command(commands, que);
  }
  Clear(st1);
  Clear(st2);
  delete st1;
  delete st2;
  delete que;
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
}

int Pop(struct Stack* stck) {
  struct box* pop_element = stck->first_element;
  int val = pop_element->value;
  stck->first_element = pop_element->next;
  stck->size--;
  delete pop_element;
  return val;
}

void Clear(struct Stack* stck) {
  while (stck->size > 0) {
    Pop(stck);
  }
}

void Command(std::string cmmnd, struct Queue* que) {
  if (cmmnd == "enqueue") {
    int n;
    std::cin >> n;
    Enqueue(n, que);
    std::cout << "ok" << std::endl;
  } else if (cmmnd == "size") {
    std::cout << que->st1->size + que->st2->size << std::endl;
  } else if (cmmnd == "clear") {
    Clear(que->st1);
    Clear(que->st2);
    std::cout << "ok" << std::endl;
  } else if (que->st1->size + que->st2->size == 0) {
    std::cout << "error" << std::endl;
  } else if (cmmnd == "dequeue") {
    std::cout << Dequeue(que) << std::endl;
  } else if (cmmnd == "front") {
    Back(que);
  } else if (cmmnd == "min") {
    if (que->st1->size == 0) {
      std::cout << (que->st2->first_element->mini) << std::endl;
    } else if (que->st2->size == 0) {
      std::cout << (que->st1->first_element->mini) << std::endl;
    } else {
      std::cout << std::min((que->st1->first_element->mini),
                            (que->st2->first_element->mini))
                << std::endl;
    }
  }
}

void Enqueue(int value, struct Queue* que) { Push(value, que->st1); }

int Dequeue(struct Queue* que) {
  if (que->st2->size == 0) {
    while (que->st1->size > 0) {
      Push(Pop(que->st1), que->st2);
    }
  }
  return Pop(que->st2);
}

void Back(struct Queue* que) {
  if (que->st2->size == 0) {
    while (que->st1->size > 0) {
      Push(Pop(que->st1), que->st2);
    }
  }
  std::cout << que->st2->first_element->value << std::endl;
}