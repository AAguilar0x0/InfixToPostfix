#include <stdio.h>
#include <windows.h>
#include "InfixToPostfix.h"
#include "myTools.h"

int getExpression(char **ptr, int lim, char echo){
	CONSOLE_SCREEN_BUFFER_INFO info;
    int count = 0, size = 1;
    char inpt;

    if(*ptr == NULL)
        *ptr = malloc(sizeof(char));
    do{
        fflush(stdin);
        inpt = tolower(getch());
        if(inpt == 8 && count > 0){
            printf("%c %c",inpt,inpt);
            *(*ptr + (--count)) = '\0';
            *ptr = realloc(*ptr, (size = count + 1) * sizeof(char));
        }else if((isdigit(inpt) && count < lim) ||
            (count == 0 && inpt == 's') || precedence(inpt) > 0){
            *ptr = realloc(*ptr, (size = ++count + 1) * sizeof(char));
            *(*ptr + (count - 1)) = inpt;
            *(*ptr + count) = '\0';
            if(**ptr == 's'){
                printf("Stop");
                getch();
                fflush(stdin);
                break;
            }else
                printf("%c",(!echo) ? inpt : echo);
        }
    }while(inpt != '\r' || count == 0);
    
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    return info.dwCursorPosition.X;
}

int main(){
    printf("\t\tInfix To Postfix and Evaluation");
    char buffer = 'y';
    char *expression;
    CONSOLE_SCREEN_BUFFER_INFO info;
    while(buffer != 'n'){
        gotoxy(0,2);
        printf("\tExpression: ");
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
        getExpression(&expression,info.dwSize.X - info.dwCursorPosition.X - 13,'\0');
        gotoxy(20,2);
        delline(10);
        gotoxy(0,4);
        if(validity(expression) < 0){
            buffer == 'y';
            printf("\tInvalid Arithmetic Expression\n\n");
        }else{
            printf("\tInfix:\t\t%s\n",expression);
            printf("\tPostfix:\t");
            InfixToPostfix(expression);
            printf("\n\tResult:\t\t%d\n\n",evaluate(expression));
        }
        free(expression);
        expression = NULL;
        printf("\tPress 'n' to stop and any key to run again... ");
        buffer = getch();
    }
}