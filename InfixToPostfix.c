#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int precedence(const char operator){
    if(operator == '(' || operator == ')')
        return 1;
    else if(operator == '*' || operator == '/' || operator == '%')
        return 2;
    else if(operator == '+' || operator == '-')
        return 3;
    return -1;
}

void InfixToPostfix(char *expression){
    int number = 0;
    int prec = 0;
    char *walker = expression;
    Stack stack = newStack();
    while(*walker){
        if(isdigit(*walker)){
            number = atoi(walker);
            printf("%d ",number);
            walker += (int)log10(number);
        }else if((prec = precedence(*walker))){
            while(!isEmpty(stack) && stackTop(stack) != '(' && 
                (*walker == ')' || precedence(stackTop(stack)) <= prec))
                printf("%c ",pop(stack));
            if(!isEmpty(stack) && stackTop(stack) == '(')
                pop(stack);
            if(*walker != ')')
                push(stack,*walker);
        }
        walker++;
    }
    while(stack->top)
        printf("%c ",pop(stack));
    freeStack(stack);
    // printf("\nExit Success");
}

int validity(char *expression){ 
    if (*expression == '\0')  return -1;
    char *walker = expression;
    int count[4] = {0};
    int prev,curr;
    prev = curr = 3;
    int valid = 1;
    while(*walker){
        while(isspace(*walker))
            walker++;
        prev = curr;
        if(isdigit(*walker)){
            curr = 0;
            walker += (int)log10(atoi(walker));
        }else if(*walker == '(')
            curr = 1;
        else if(*walker == ')')
            curr = 2;
        else if(precedence(*walker) > 0)
            curr = 3;
        if(((prev != 1 || curr != 1) && (prev != 2 || curr != 2)) && 
            ((prev == 0 && curr == 0) || (prev == 3 && curr == 3) || 
            (prev == 2 && curr != 3) || (prev == 1 && curr != 0))){
            valid = -1;
            break;
        }
        count[curr]++;
        walker++;
    }
    if(count[0] != (count[3] + 1) || count[1] != count[2])
        valid = -1;
    return valid;
} 

int applyOp(int a, int b, char op){
    int res = 0;
	switch(op){
		case '+': res = a + b;
            break;
		case '-': res = a - b;
            break;
		case '*': res = a * b;
            break;
		case '/': res = a / b;
            break;
        case '%': res = a % b;
            break;
	}
    return res;
}

int evaluate(char *expression){
    char *walker = expression;
    Stack operator = newStack();
    Stack value = newStack();
    int number = 0;
    int a = 0;
    int b = 0;
    int result = 0;
    char op = '\0';
    while(*walker){
		if(*walker == '('){
			push(operator,*walker);
		} else if(isdigit(*walker)){
			number = atoi(walker);
			walker += (int)log10(number);
			push(value,number);
		} else if(*walker == ')'){ 
			while(!isEmpty(operator) && stackTop(operator) != '('){ 
				b = pop(value);
				a = pop(value);
				op = pop(operator);
				push(value,applyOp(a,b,op));
			} 
			if(!isEmpty(operator)) 
			    pop(operator);
		} else if(precedence(*walker) > 0){
			while(!isEmpty(operator) && stackTop(operator) != '(' &&
                precedence(stackTop(operator)) <= precedence(*walker)){
				b = pop(value);
				a = pop(value);
				op = pop(operator);
				push(value,applyOp(a,b,op));
			}
			push(operator,*walker);
		}
        walker++;
	}
	while(!isEmpty(operator)){
		b = pop(value);
		a = pop(value);
        op = pop(operator);
		push(value,applyOp(a,b,op));
	} 
	result = pop(value);
    freeStack(value);
    freeStack(operator);
	return result;
}