#ifndef UTILS_H
#define UTILS_H

#include "letter.h"

t_letter** generateLetterBag();
t_letter* drawLetter(t_letter** bag);
int isBagEmpty(t_letter **bag);

#endif // UTILS_H
