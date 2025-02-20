#include "../include/board.h"
#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>

t_board allocateBoard(int width, int height) {
    t_board board = (t_box***)malloc(width * sizeof(t_box**));
    for (int i = 0; i < width; i++) {
        board[i] = (t_box**)malloc(height * sizeof(t_box*));
        for (int j = 0; j < height; j++) {
            board[i][j] = (t_box*)malloc(sizeof(t_box));
            board[i][j]->letter = NULL;
            board[i][j]->content = EMPTY;
        }
    }
    return board;
}

void initBoard(t_board board, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            board[i][j]->letter = NULL;
            board[i][j]->content = EMPTY;
        }
    }
}

void initPrime(t_board board, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Initialisation par défaut à EMPTY
            board[i][j]->content = EMPTY;
        }
    }

    // Placement des primes TRIPLE WORD (rouge)
    int tripleWordPositions[][2] = {{0, 0}, {0, 7}, {0, 14}, {7, 0}, {7, 14}, {14, 0}, {14, 7}, {14, 14}};
    for (int k = 0; k < 8; k++) {
        board[tripleWordPositions[k][0]][tripleWordPositions[k][1]]->content = TRIPLEW;
    }

    // Placement des primes DOUBLE WORD (jaune) + le centre du plateau
    int doubleWordPositions[][2] = {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {13, 13}, {12, 12}, {11, 11}, {10, 10},
        {1, 13}, {2, 12}, {3, 11}, {4, 10}, {13, 1}, {12, 2}, {11, 3}, {10, 4},
        {7, 7} // Centre du plateau
    };
    for (int k = 0; k < 17; k++) { // Taille ajustée à 17
        board[doubleWordPositions[k][0]][doubleWordPositions[k][1]]->content = DOUBLEW;
    }

    // Placement des primes TRIPLE LETTER (bleu)
    int tripleLetterPositions[][2] = {
        {1, 5}, {1, 9}, {5, 1}, {5, 5}, {5, 9}, {5, 13},
        {9, 1}, {9, 5}, {9, 9}, {9, 13}, {13, 5}, {13, 9}
    };
    for (int k = 0; k < 12; k++) {
        board[tripleLetterPositions[k][0]][tripleLetterPositions[k][1]]->content = TRIPLEL;
    }

    // Placement des primes DOUBLE LETTER (bleu clair)
    int doubleLetterPositions[][2] = {
        {0, 3}, {0, 11}, {2, 6}, {2, 8}, {3, 0}, {3, 7}, {3, 14}, {6, 2}, {6, 6}, {6, 8}, {6, 12},
        {7, 3}, {7, 11}, {8, 2}, {8, 6}, {8, 8}, {8, 12}, {11, 0}, {11, 7}, {11, 14}, {12, 6}, {12, 8},
        {14, 3}, {14, 11}
    };
    for (int k = 0; k < 24; k++) {
        board[doubleLetterPositions[k][0]][doubleLetterPositions[k][1]]->content = DOUBLEL;
    }
}



void displayBoard(t_board board, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Vérifie si une lettre est présente
            if (board[i][j]->letter != NULL) {
                printf("| %c ", board[i][j]->letter->value);  // Affiche la lettre
            } else {
                // Affiche la prime avec la couleur correspondante
                switch (board[i][j]->content) {
                    case TRIPLEW:
                        printf("| %sT%s ", RED, RESET);  // Triple Word (Rouge)
                        break;
                    case DOUBLEW:
                        printf("| %sD%s ", YELLOW, RESET);  // Double Word (Jaune)
                        break;
                    case TRIPLEL:
                        printf("| %sT%s ", BLUE, RESET);  // Triple Letter (Bleu)
                        break;
                    case DOUBLEL:
                        printf("| %sD%s ", CYAN, RESET);  // Double Letter (Cyan)
                        break;
                    default:
                        printf("|   ");  // Case vide
                        break;
                }
            }
        }
        printf("|\n");
    }
}


void freeBoard(t_board board, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
}


void placeWordOnBoard(t_board board, t_action action) {
    int x = action.x;
    int y = action.y;
    t_letter *word = action.word;

    for (int i = 0; word[i].value != '\0'; i++) {
        if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT) {
            printf("Erreur : Placement hors du plateau.\n");
            return;
        }

        if (board[x][y]->letter != NULL) {
            printf("Erreur : Une lettre est déjà placée en (%d, %d).\n", x, y);
            return;
        }

        // Place la lettre sur le plateau
        board[x][y]->letter = (t_letter*)malloc(sizeof(t_letter));
        if (!board[x][y]->letter) {
            perror("Erreur d'allocation de mémoire pour la lettre");
            exit(EXIT_FAILURE);
        }

        board[x][y]->letter->value = word[i].value;
        board[x][y]->letter->points = word[i].points;

        // Avance selon la direction
        if (action.direction == 'H') {
            y++;
        } else if (action.direction == 'V') {
            x++;
        }
    }
}
