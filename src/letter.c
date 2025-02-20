#include "../include/letter.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction pour créer une lettre
t_letter* createLetter(char value, int points) {
    t_letter* newLetter = (t_letter*)malloc(sizeof(t_letter));
    if (newLetter == NULL) {
        perror("Erreur d'allocation mémoire pour une lettre");
        return NULL;
    }
    newLetter->value = value;
    newLetter->points = points;
    return newLetter;
}

// Fonction pour libérer une lettre
void freeLetter(t_letter* letter) {
    if (letter != NULL) {
        free(letter);
    }
}
