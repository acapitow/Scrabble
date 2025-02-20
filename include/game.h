#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <stdbool.h>

int placeWord(t_board board, t_easel* easel, t_action* action);
bool validateWord(t_board board, t_action* action);
int calculateScore(t_board board, t_action* action);

#endif // GAME_H
