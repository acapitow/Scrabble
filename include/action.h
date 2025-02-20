#ifndef ACTION_H
#define ACTION_H

#include "letter.h"
#include <stdlib.h>
#include <string.h>

// Définition d'une action du joueur
typedef struct t_action {
    int x, y;            // Position de départ sur le plateau
    char direction;      // 'H' pour horizontal, 'V' pour vertical
    t_letter* word;      // Mot joué sous forme de lettres
    t_letter** words;    // Liste des mots adjacents générés
} t_action;

// Fonctions de gestion des actions
t_action* allocateAction(int x, int y, char direction, const char* word);
void freeAction(t_action* action);

#endif // ACTION_H
