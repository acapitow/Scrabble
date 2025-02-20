#include "../include/easel.h"
#include <stdio.h>
#include <stdlib.h>


// Fonction pour allouer un chevalet
t_easel* allocateEasel(int maxLetters) {
    // Allocation mémoire pour le chevalet
    t_easel* easel = (t_easel*)malloc(sizeof(t_easel));
    if (easel == NULL) {
        perror("Erreur d'allocation mémoire pour le chevalet");
        return NULL;
    }
    // Allocation mémoire pour les lettres
    easel->letters = (t_letter**)malloc(maxLetters * sizeof(t_letter*));
    if (easel->letters == NULL) {
        perror("Erreur d'allocation mémoire pour les lettres du chevalet");
        free(easel);
        return NULL;
    }
    // Initialisation des champs
    easel->totalPoints = 0;
    easel->letterCount = 0;
    return easel;
}

// Fonction pour ajouter une lettre au chevalet
void addLetterToEasel(t_easel* easel, t_letter* letter) {
    if (easel == NULL || letter == NULL) {
        return;
    }
    // Ajout de la lettre et mise à jour des points
    easel->letters[easel->letterCount] = letter;
    easel->letterCount++;
}

// Fonction pour afficher le contenu du chevalet
void displayEasel(t_easel* easel) {
    if (easel == NULL) {
        printf("Chevalet vide.\n");
        return;
    }
    printf("Chevalet : ");
    for (int i = 0; i < easel->letterCount; i++) {
        printf("%c ", easel->letters[i]->value);
    }
    printf("\nPoints totaux : %d\n", easel->totalPoints);
}

// Fonction pour libérer la mémoire associée au chevalet
void freeEasel(t_easel* easel) {
    if (easel != NULL) {
        for (int i = 0; i < easel->letterCount; i++) {
            freeLetter(easel->letters[i]);
        }
        free(easel->letters);
        free(easel);
    }
}
