#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
// **Placement d'un mot sur le plateau**
int placeWord(t_board board, t_easel* easel, t_action* action) {
    int x = action->x;
    int y = action->y;
    int len = strlen((char*)action->word);

    // Vérification de la validité du placement
    if (!validateWord(board, action)) {
        printf("Placement invalide !\n");
        return 0;
    }

    // Placement des lettres sur le plateau
    for (int i = 0; i < len; i++) {
        board[x][y]->letter = &action->word[i];

        // Déplacement selon la direction
        if (action->direction == 'H') {
            y++;
        } else if (action->direction == 'V') {
            x++;
        }
    }

    return calculateScore(board, action);
}
*/

// **Vérification de la validité du mot sur le plateau**
bool validateWord(t_board board, t_action* action) {
    int x = action->x;
    int y = action->y;
    int len = strlen((char*)action->word);

    // Vérifier que le mot reste dans les limites du plateau
    if ((action->direction == 'H' && y + len > BOARD_WIDTH) ||
        (action->direction == 'V' && x + len > BOARD_HEIGHT)) {
        return false;
    }

    // Vérifier qu'il n'y a pas de conflits de placement
    for (int i = 0; i < len; i++) {
        if (board[x][y]->letter != NULL && board[x][y]->letter->value != action->word[i].value) {
            return false;
        }

        // Déplacement selon la direction
        if (action->direction == 'H') {
            y++;
        } else if (action->direction == 'V') {
            x++;
        }
    }

    return true;
}

// **Calcul du score d'une action (mot principal + mots adjacents)**
int calculateScore(t_board board, t_action* action) {
    int score = 0;
    int wordMultiplier = 1;

    int x = action->x;
    int y = action->y;
    int len = strlen((char*)action->word);

    for (int i = 0; i < len; i++) {
        t_box* box = board[x][y];
        if (box->letter != NULL) {
            score += box->letter->points;
        }

        // Application des primes
        if (box->content == DOUBLEL) {
            score += box->letter->points;  // Double de la lettre
        } else if (box->content == TRIPLEL) {
            score += 2 * box->letter->points;  // Triple de la lettre
        } else if (box->content == DOUBLEW) {
            wordMultiplier *= 2;  // Double du mot
        } else if (box->content == TRIPLEW) {
            wordMultiplier *= 3;  // Triple du mot
        }

        // Déplacement selon la direction
        if (action->direction == 'H') {
            y++;
        } else if (action->direction == 'V') {
            x++;
        }
    }

    // Calcul des scores des mots adjacents (sans primes)
    for (int i = 0; action->words[i] != NULL; i++) {
        t_letter* adjacentWord = action->words[i];
        int adjLen = strlen((char*)adjacentWord);
        for (int j = 0; j < adjLen; j++) {
            score += adjacentWord[j].points;
        }
    }

    return score * wordMultiplier;
}
