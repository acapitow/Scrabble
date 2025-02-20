#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include "easel.h"
#include "action.h"

// Dimensions du plateau de jeu
#define BOARD_WIDTH 15
#define BOARD_HEIGHT 15

// Couleurs pour l'affichage des primes
#define RESET   "\033[0m"
#define RED     "\033[31m"  // Triple Word
#define YELLOW  "\033[33m"  // Double Word
#define BLUE    "\033[34m"  // Triple Letter
#define CYAN    "\033[36m"  // Double Letter

// Définition du type pour le plateau
typedef struct t_box {
    t_prime content;
    t_letter* letter;
} t_box;

typedef struct t_box** *t_board;

// Fonctions de gestion du plateau
t_board allocateBoard(int width, int height);
void initBoard(t_board board, int width, int height);
void initPrime(t_board board, int width, int height);
void displayBoard(t_board board, int width, int height);
void freeBoard(t_board board, int width, int height);
void placeWordOnBoard(t_board board, t_action action);

#endif // BOARD_H
