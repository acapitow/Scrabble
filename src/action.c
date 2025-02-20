#include "../include/action.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// **Allocation d'une action**
t_action* allocateAction(int x, int y, char direction, const char* word) {
    t_action* action = (t_action*)malloc(sizeof(t_action));
    if (!action) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'action\n");
        return NULL;
    }

    action->x = x;
    action->y = y;
    action->direction = direction;

    // Allocation du mot principal
    int len = strlen(word);
    action->word = (t_letter*)malloc((len + 1) * sizeof(t_letter));
    if (!action->word) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le mot principal\n");
        free(action);
        return NULL;
    }

    // Initialisation du mot principal
    for (int i = 0; i < len; i++) {
        action->word[i].value = word[i];
        action->word[i].points = word[i] - 'A' + 1;  // Exemple simple pour la valeur des points
    }

    // Allocation pour stocker les mots adjacents
    action->words = (t_letter**)malloc(sizeof(t_letter*) * (len + 1));  // Maximum len mots
    if (!action->words) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les mots adjacents\n");
        free(action->word);
        free(action);
        return NULL;
    }

    for (int i = 0; i < len + 1; i++) {
        action->words[i] = NULL;  // Initialisation des entrées à NULL
    }

    return action;
}

// **Libération d'une action**
void freeAction(t_action* action) {
    if (!action) return;

    // Libération du mot principal
    free(action->word);

    // Libération des mots adjacents
    if (action->words) {
        for (int i = 0; action->words[i] != NULL; i++) {
            free(action->words[i]);
        }
        free(action->words);
    }

    free(action);
}