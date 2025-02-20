#ifndef EASEL_H
#define EASEL_H

#include "letter.h"

typedef struct t_easel {
    t_letter** letters;
    int totalPoints;
    int letterCount;
} t_easel;

t_easel* allocateEasel(int maxLetters);
void addLetterToEasel(t_easel* easel, t_letter* letter);
void displayEasel(t_easel* easel);
void freeEasel(t_easel* easel);

#endif // EASEL_H
