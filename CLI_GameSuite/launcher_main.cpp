#include "blackjack_main.cpp"
#include "ttt_main.cpp"
#include <iostream>

int main() {

    cout << "Welcome to the CLI Game Suite." << endl;
    cout << "Press [1] for 3D TicTacToe or [2] for Blackjack." << endl;
    cout << "Press 'q' to exit." <<endl;
    
    char input;
    cin >> input;

    if (input == '1') {
        tttmain();
    } else if(input == '2') {
        blackjackmain();
    } else if(input == 'q') {
        cout << "Hope you enojyed your stay :)" << endl;
        return 0;
    } else {
        cout << "Input unkown. Try again." << endl;
    }
    return 0;
}

