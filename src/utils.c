#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour générer un sac de lettres
t_letter** generateLetterBag() {
    // Initialisation du sac
    int totalLetters = 100;  // Par exemple, 100 lettres dans le sac
    t_letter** bag = (t_letter**)malloc(totalLetters * sizeof(t_letter*));
    if (bag == NULL) {
        perror("Erreur d'allocation mémoire pour le sac de lettres");
        return NULL;
    }

    // Distribution des lettres (par exemple, fréquence typique en Scrabble)
    char letters[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    int points[] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
    };
    int frequencies[] = {
        9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2,
        6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1
    };

    // Remplissage du sac avec des lettres
    int index = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < frequencies[i]; j++) {
            bag[index] = createLetter(letters[i], points[i]);
            index++;
        }
    }

    // Mélange des lettres dans le sac
    srand((unsigned int)time(NULL));
    for (int i = totalLetters - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        t_letter* temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
    }

    return bag;
}

// Fonction pour tirer une lettre du sac
t_letter* drawLetter(t_letter **bag) {
    if (bag[0] == NULL) return NULL;

    t_letter* drawnLetter = bag[0];

    // Décaler les lettres restantes
    for (int i = 0; i < 99; i++) {
        bag[i] = bag[i + 1];
    }
    bag[99] = NULL;  // La dernière case devient NULL

    return drawnLetter;
}


int isBagEmpty(t_letter **bag) {
    for (int i = 0; i < 100; i++) { // 100 étant le nombre total de lettres possibles
        if (bag[i] != NULL) return 0;  // Une lettre est encore disponible
    }
    return 1;  // Plus aucune lettre
}
