#include <iostream>
#include "blackjack.h"
using namespace std;

int blackjackmain() {
    cout << "Welcome to the COMP322 Blackjack game!" << endl
         << endl;
    BlackJackGame game;

    bool playAgain = true;
    char answer = 'y';
    while (playAgain) {
        game.play();

        cout << "Would you like to play another round? (y/n): ";
        cin >> answer;
        cout << endl
             << endl;
        playAgain = (answer == 'y' ? true : false);
    }
    cout << "Game over!" << endl;
    return 0;
}