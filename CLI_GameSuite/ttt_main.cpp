#include "ttt.h"

int tttmain() {
    char board[28] = {'n'};
    greetAndInstruct();
    playTTT(board);
    return 0;
}