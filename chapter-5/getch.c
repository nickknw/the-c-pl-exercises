#include <string.h>
#include <stdlib.h>
#include "getch.h"
#include "dbg.h"

static int *characters;
static int count;

int getch(void) 
{
    int value = characters[count];
    count++;
    return value;
}

void ungetch(int character)
{
    count--;
    characters[count] = character;
}

void setInput(int newCharacters[], int length)
{
    characters = malloc(length * sizeof(int));

    memcpy(characters, newCharacters, length * sizeof(int));
    count = 0;
}

void freeInput()
{
    if (characters) {
        free(characters);
    }
}
