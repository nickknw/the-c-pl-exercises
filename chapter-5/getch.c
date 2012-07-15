#include <string.h>
#include <stdlib.h>
#include "getch.h"

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
    characters[count] = character;
    count--;
}

void setInput(int newCharacters[], int length)
{
    if (characters) {
        characters = realloc(characters, length * sizeof(int));
    } else {
        characters = malloc(length * sizeof(int));
    }
    memcpy(characters, newCharacters, length * sizeof(int));
    count = 0;
}

void freeInput()
{
    if (characters) {
        free(characters);
    }
}
