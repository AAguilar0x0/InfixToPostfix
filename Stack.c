#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack newStack() {
	Stack stack;
	stack = (Stack) malloc(sizeof(STACK_HEAD));
	stack->count = 0;
	stack->top = NULL;
	return stack;
}

void freeStack(Stack stack) {
	Nodeptr temp;
    while(stack->top != NULL) {
		temp = stack->top->next;
		free(stack->top);
		stack->top = temp;
	}
    free(stack);
}

Nodeptr createNode(int item) {
	Nodeptr ptr;
	ptr = (Nodeptr) malloc(sizeof(STACK_NODE));
	ptr->data = item;
	ptr->next = NULL;
	return ptr;
}

void push(Stack stack, stackItem item) {
	if(stack == NULL) return;
	Nodeptr temp = createNode(item);
	temp->next = stack->top;
	stack->top = temp;
	stack->count++;
}

stackItem pop(Stack stack) {
	Nodeptr temp;
	stackItem item = stack->top->data;
	temp = stack->top;
	stack->top = temp->next;
	temp->next = NULL;
	free(temp);
	stack->count--;
	return item;
}

void display(Stack stack) {
	Nodeptr ptr = stack->top;
    int i = 0;
	while(ptr != NULL) {
		printf("%c%s",ptr->data,
            i < stack->count - 1 ? "->" : "");
		ptr = ptr->next;
        i++;
	}
}

int isEmpty(Stack stack) {
	return stack->top == NULL;
}

stackItem stackTop(Stack stack) {
    return stack->top->data;
}
