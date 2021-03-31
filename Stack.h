typedef struct node* Nodeptr;

typedef int stackItem;

typedef struct node{
	stackItem data;
	Nodeptr next;
}STACK_NODE;

typedef struct{
	int count;
	Nodeptr top;
}STACK_HEAD;

typedef STACK_HEAD* Stack;

Stack newStack();
void freeStack(Stack s);
void push(Stack s,stackItem item);
stackItem pop(Stack s);
void display(Stack s);
int isEmpty(Stack s);
stackItem stackTop(Stack s);