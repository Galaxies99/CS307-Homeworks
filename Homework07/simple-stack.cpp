# include <iostream>
using namespace std;

struct StackNode {
  int data;
  StackNode *next;
  StackNode(int data, StackNode *next) : data(data), next(next) {}
};


void push(int input_data, StackNode **top) {
  StackNode *new_top = new StackNode(input_data, *top);
  *top = new_top;
}

int pop(StackNode **top) {
  int output_data = (*top) -> data;
  StackNode *old_top = *top; 
  *top = (*top) -> next;
  delete old_top;
  return output_data; 
}


int main() {    
  StackNode *top = NULL;
  
  /* perform push operations and pop operations */
  push(5, &top);
  push(10, &top);
  
  int value = pop(&top); cout << value << endl;
  value = pop(&top); cout << value << endl;
  push(15, &top);
  
  value = pop(&top); cout << value << endl;
  return 0;
}



