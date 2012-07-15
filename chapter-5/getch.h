#ifndef __getch_h__
#define __getch_h__

int getch(void);
void ungetch(int);

void setInput(int[], int);
void freeInput();

#endif
