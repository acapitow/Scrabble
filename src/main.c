#include "../include/game.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS 7  // Nombre de lettres maximum par chevalet

void gameLoop(t_board board, t_letter **letterBag);

int main() {
    // Allocation du plateau
    t_board board = allocateBoard(BOARD_WIDTH, BOARD_HEIGHT);
    initBoard(board, BOARD_WIDTH, BOARD_HEIGHT);
    initPrime(board, BOARD_WIDTH, BOARD_HEIGHT);

    // Génération du sac de lettres
    t_letter **letterBag = generateLetterBag();
    if (letterBag == NULL || letterBag[0] == NULL) {
        printf("Erreur : Le sac de lettres est vide !\n");
        freeBoard(board, BOARD_WIDTH, BOARD_HEIGHT);
        return 1;
    }

    // Lancement de la boucle de jeu
    gameLoop(board, letterBag);

    // Libération de la mémoire
    freeBoard(board, BOARD_WIDTH, BOARD_HEIGHT);
    free(letterBag);

    return 0;
}

void gameLoop(t_board board, t_letter **letterBag) {
    // Création des chevalets pour deux joueurs
    t_easel *player1 = allocateEasel(MAX_LETTERS);
    t_easel *player2 = allocateEasel(MAX_LETTERS);

    // Tirage initial des lettres
    for (int i = 0; i < MAX_LETTERS; i++) {
        addLetterToEasel(player1, drawLetter(letterBag));
        addLetterToEasel(player2, drawLetter(letterBag));
    }

    int turn = 0; // Alternance des tours (0: Joueur 1, 1: Joueur 2)

    while (!isBagEmpty(letterBag)) { // Tant qu'il reste des lettres à tirer

        // Effacer l'écran selon l'OS
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Détermination du joueur actif
        t_easel *currentPlayer = (turn % 2 == 0) ? player1 : player2;
        printf("\nTour du Joueur %d\n", (turn % 2) + 1);

        // Affichage du plateau et du chevalet du joueur
        displayBoard(board, BOARD_WIDTH, BOARD_HEIGHT);
        printf("\nLettres disponibles : ");
        displayEasel(currentPlayer);

        // Saisie de l'action
        printf("\nEntrez une action (ex: PLACE mot X Y H): ");
        fflush(stdout);

        char command[10], word[20], direction;
        int x, y;
        if (scanf("%s %s %d %d %c", command, word, &x, &y, &direction) != 5) {
            printf("Entrée invalide. Essayez à nouveau.\n");
            while (getchar() != '\n'); // Nettoyer l'entrée
            continue;
        }

        // Traitement de la commande
        if (strcmp(command, "PLACE") == 0) {
            t_action *action = allocateAction(x, y, direction, word);

            // Vérifier si le joueur possède les lettres du mot
            int validPlacement = 1;
            for (size_t i = 0; i < strlen(word); i++) {
                int found = 0;
                for (int j = 0; j < currentPlayer->letterCount; j++) {
                    if (currentPlayer->letters[j] != NULL && currentPlayer->letters[j]->value == word[i]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    validPlacement = 0;
                    break;
                }
            }

            if (validPlacement) {
                // Placement du mot sur le plateau
                placeWordOnBoard(board, *action);
                int score = calculateScore(board, action);
                currentPlayer->totalPoints += score;
                printf("Mot placé ! Score gagné : %d\n", score);

                // Suppression des lettres utilisées du chevalet
                for (size_t i = 0; i < strlen(word); i++) {
                    for (int j = 0; j < currentPlayer->letterCount; j++) {
                        if (currentPlayer->letters[j] != NULL && currentPlayer->letters[j]->value == word[i]) {
                            free(currentPlayer->letters[j]);  // Libérer la mémoire de la lettre jouée
                            currentPlayer->letters[j] = NULL;
                            break;
                        }
                    }
                }

                // Décalage des lettres restantes
                int index = 0;
                for (int i = 0; i < MAX_LETTERS; i++) {
                    if (currentPlayer->letters[i] != NULL) {
                        currentPlayer->letters[index++] = currentPlayer->letters[i];
                    }
                }
                currentPlayer->letterCount = index;

                // Remplissage du chevalet avec de nouvelles lettres
                while (currentPlayer->letterCount < MAX_LETTERS && letterBag[0] != NULL) {
                    addLetterToEasel(currentPlayer, drawLetter(letterBag));
                }
            } else {
                printf("Erreur : Vous ne possédez pas toutes les lettres nécessaires.\n");
            }

            freeAction(action);
        } else {
            printf("Commande invalide. Essayez à nouveau.\n");
        }

        turn++;  // Passage au tour suivant

        // Pause pour affichage
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
        getchar();
    }

    // Fin du jeu
    printf("\nFin du jeu ! Scores finaux :\n");
    printf("Joueur 1: %d points\n", player1->totalPoints);
    printf("Joueur 2: %d points\n", player2->totalPoints);

    // Libération de la mémoire
    freeEasel(player1);
    freeEasel(player2);
}
