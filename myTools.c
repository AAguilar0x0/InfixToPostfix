#include<conio.h>
#include<stdio.h>
#include<windows.h>

int getDigit(char **ptr, int lim, char echo){
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
            (count == 0 && inpt == 's')
        ){
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

void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	
	return;
}

void delline(unsigned int lines) {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;

	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X - (coord.X - 1) + (info.dwSize.X * (lines == 0 ? 0:(lines - 1))), coord, &written);
	gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

int centerOutString(int y, const char *format, ...){
	va_list arg;
	int x;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	x = (info.dwSize.X / 2) - (strlen(format) - (strlen(format)) / 2) + ((info.dwSize.X % 2) ? 1 : 0);
	gotoxy(x,y);
	va_start (arg, format);
	vfprintf (stdout, format, arg);
	va_end (arg);

	return x;
}

int outString(int x, int y, const char *format, ...){
   va_list arg;
   int done;

   gotoxy(x,y);
   va_start (arg, format);
   done = vfprintf (stdout, format, arg);
   va_end (arg);

   return done;
}

void drawSBox(int x1,int y1,int x2,int y2){
    int i = 0;

    for(i=x1;i<=x2;i++){
        gotoxy(i,y1);
        printf("%c",196);
        gotoxy(i,y2);
        printf("%c",196);
    }
    for(i=y1;i<=y2;i++){
        gotoxy(x1,i);
        printf("%c",179);
        gotoxy(x2,i);
        printf("%c",179);
    }
    gotoxy(x1,y1);
    printf("%c",218);
    gotoxy(x1,y2);
    printf("%c",192);
    gotoxy(x2,y1);
    printf("%c",191);
    gotoxy(x2,y2);
    printf("%c",217);

    return;
}

void drawDBox(int x1, int y1, int x2, int y2){
    int i = 0;
    for(i=x1;i<=x2;i++){
        gotoxy(i,y1);
        printf("%c",205);
        gotoxy(i,y2);
        printf("%c",205);
    }
    for(i=y1;i<=y2;i++){
        gotoxy(x1,i);
        printf("%c",186);
        gotoxy(x2,i);
        printf("%c",186);
    }
    gotoxy(x1,y1);
    printf("%c",201);
    gotoxy(x1,y2);
    printf("%c",200);
    gotoxy(x2,y1);
    printf("%c",187);
    gotoxy(x2,y2);
    printf("%c",188);
    	
	return;
}

int drawCSBox(int width,int y1,int y2){
	int x1, x2;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	x1 = (info.dwSize.X / 2) - (width - width / 2) + ((info.dwSize.X % 2) ? 1 : 0);
    x2 = (info.dwSize.X / 2) + (width - width / 2) - 1 + ((info.dwSize.X % 2) ? 1 : 0);

    drawSBox(x1,y1,x2,y2);

    /* for(i=x1;i<x2;i++){
        gotoxy(i,y1);
        printf("%c",196);
        gotoxy(i,y2);
        printf("%c",196);
    }
    for(i=y1;i<=y2;i++){
        gotoxy(x1,i);
        printf("%c",179);
        gotoxy(x2,i);
        printf("%c",179);
    }
    gotoxy(x1,y1);
    printf("%c",218);
    gotoxy(x1,y2);
    printf("%c",192);
    gotoxy(x2,y1);
    printf("%c",191);
    gotoxy(x2,y2);
    printf("%c",217); */

    return x1;
}

int drawCDBox(int width,int y1,int y2){
	int x1, x2;
	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	x1 = (info.dwSize.X / 2) - (width - width / 2) + ((info.dwSize.X % 2) ? 1 : 0);
    x2 = (info.dwSize.X / 2) + (width - width / 2) - 1 + ((info.dwSize.X % 2) ? 1 : 0);

    drawDBox(x1,y1,x2,y2);

    /* for(i=x1;i<x2;i++){
        gotoxy(i,y1);
        printf("%c",205);
        gotoxy(i,y2);
        printf("%c",205);
    }
    for(i=y1;i<=y2;i++){
        gotoxy(x1,i);
        printf("%c",186);
        gotoxy(x2,i);
        printf("%c",186);
    }
    gotoxy(x1,y1);
    printf("%c",201);
    gotoxy(x1,y2);
    printf("%c",200);
    gotoxy(x2,y1);
    printf("%c",187);
    gotoxy(x2,y2);
    printf("%c",188); */
    	
	return x1;
}
