#include<windows.h>
int getDigit(char **ptr, int lim, char echo);

/* 
* Set the cursor in the
* specified coordinates.
*/
void gotoxy(int x, int y);

/* 
* Delete the number of lines
* specified, starting from
* the origin of the cursor.
*/
void delline(unsigned int lines);

/* 
* Prints the given text in the center of the
* console. And automatically add or subract
* 1 so that the polygon is symetrical
*/
int centerOutString(int y, const char *format, ...);

/* 
* Prints the given text in the
* specified inputed coordinates.
*/
int outString(int x, int y, const char *format, ...);

/* 
* Draw a single line quadrilatiral polygon,
* given two coordinates.
*/
void drawSBox(int x1, int y1, int x2, int y2);

/* 
* Draw a double line quadrilatiral polygon,
* given two coordinates.
*/
void drawDBox(int x1, int y1, int x2, int y2);

/* 
* Draw a centered single line quadrilatiral
* polygon in the center. Given the width and
* two y coordinates. The function automatically
* add or subract 1 so that the polygon is symetrical
*/
int drawCSBox(int width, int y1, int y2);

/* 
* Draw a centered double line quadrilatiral
* polygon in the center. Given the width and
* two y coordinates. The function automatically
* add or subract 1 so that the polygon is symetrical
*/
int drawCDBox(int width,int y1, int y2);
