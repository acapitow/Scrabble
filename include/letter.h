#ifndef LETTER_H
#define LETTER_H

typedef struct t_letter {
    char value;
    int points;
} t_letter;

typedef enum { DOUBLEW, TRIPLEW, DOUBLEL, TRIPLEL, EMPTY } t_prime;

t_letter* createLetter(char value, int points);
void freeLetter(t_letter* letter);

#endif // LETTER_H
