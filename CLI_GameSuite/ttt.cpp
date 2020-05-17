#include <iomanip>
#include <iostream>
using namespace std;

void greetAndInstruct() {
    cout << "\nWelcome to Tic-Tac-Toe! Can you beat the computer?" << endl;
    cout << "The board is numbered from 1 to 27 as per the following: " << endl;
    cout << "\n | 1 | 2 | 3 | \t | 10 | 11 | 12 | \t | 19 | 20 | 21 |" << endl;
    cout << " -------------\t ----------------\t ----------------";
    cout << "\n | 4 | 5 | 6 | \t | 13 | 14 | 15 | \t | 22 | 23 | 24 |" << endl;
    cout << " -------------\t ----------------\t ----------------";
    cout << "\n | 7 | 8 | 9 | \t | 16 | 17 | 18 | \t | 25 | 26 | 27 |" << endl;
    cout << "\nPlayer starts first. Input the number of the cell you want to select." << endl;
    cout << "Player is represented by X. Computer is represented by O" << endl;
    cout << "Start? (y/n)" << endl;

    /* 
    Since this is a static wall of text I didn't bother with io manipulation through setw.
    A tidier way, mostly due to necessitiy, is applied in the displayBoard() function.
    */

    string input;
    string no = "n";
    string yes = "y";
    cin >> input;

    if (input.compare(no) == 0) {
        cout << "Maybe next time!" << endl;
        exit(0);
    } else if (input.compare(yes) == 0) {
        cout << "Good luck! You'll need it :)" << endl;
    } else {
        cout << "Input not recognized." << endl;
        greetAndInstruct();
    }
    /*
    This can be expanded to make sure lowercase-uppercase distinction does not exist. Furthermore,
    although the user is explicityly told to input 'y' or 'n', one may also include variations of 
    "Yes" and "No".
    */
}

void displayBoard(char board[]) {
    /*
    While designing this method, I assumed that the board[] would always be of length 28.
    As an aside, I used 28 and not 27 because I'd rather leave the board[0] as "null" (not '\0') for the sake
    of readability, given that it's best if the number 27 corresponds to board[27].
    */
    string newBoard[28] = {"null"};
    for (int i = 1; i < 28; i++) {
        if (board[i] != '\0') {
            newBoard[i] = board[i];
        }
    }
    for (int i = 1; i < 28; i++) {
        if (newBoard[i].empty()) {
            string numerical = to_string(i);
            newBoard[i] = numerical;
        }
    }  // Merging a newly created empty board with the one that's fed in. Allows for the printing of numbers.
    cout << "\nCurrent board:" << endl;
    cout << "\n|" << setw(2) << newBoard[1] << " |" << setw(2) << newBoard[2] << " |" << setw(2) << newBoard[3] << " |" << setw(5) << " "
         << " | " << setw(2) << newBoard[10] << " | " << setw(2) << newBoard[11] << " | " << setw(2) << newBoard[12] << " | " << setw(5) << " "
         << "| " << setw(2) << newBoard[19] << " | " << setw(2) << newBoard[20] << " | " << setw(2) << newBoard[21] << " | " << endl;
    cout << setw(13) << "-------------" << setw(7) << " " << setw(13) << "---------------" << setw(7) << " " << setw(13) << "---------------";
    cout << "\n"
         << "|" << setw(2) << newBoard[4] << " |" << setw(2) << newBoard[5] << " |" << setw(2) << newBoard[6] << " |" << setw(5) << " "
         << " | " << setw(2) << newBoard[13] << " | " << setw(2) << newBoard[14] << " | " << setw(2) << newBoard[15] << " | " << setw(5) << " "
         << "| " << setw(2) << newBoard[22] << " | " << setw(2) << newBoard[23] << " | " << setw(2) << newBoard[24] << " | " << endl;
    cout << setw(13) << "-------------" << setw(7) << " " << setw(13) << "---------------" << setw(7) << " " << setw(13) << "---------------";
    cout << "\n"
         << "|" << setw(2) << newBoard[7] << " |" << setw(2) << newBoard[8] << " |" << setw(2) << newBoard[9] << " |" << setw(5) << " "
         << " | " << setw(2) << newBoard[16] << " | " << setw(2) << newBoard[17] << " | " << setw(2) << newBoard[18] << " | " << setw(5) << " "
         << "| " << setw(2) << newBoard[25] << " | " << setw(2) << newBoard[26] << " | " << setw(2) << newBoard[27] << " | \n"
         << endl;

    /*
    setw(2) is used to make sure that the double digit cell numbers and the 'X' and 'O's cover 
    the same amount of space. This makes it so that the board appears static with only the numbers
    changing. It also should make it monitor/resolution agnostic. This isn't used in the initial 
    introduction since only a static board is displayed.
    */
}

bool checkIfLegal(int cellNbre, char board[]) {
    if (cellNbre > 27 || cellNbre < 1) {
        cout << "\nIllegal move! That tile does not exist. Please input a valid move." << endl;
        return false;
    }
    if (board[cellNbre] != '\0') {
        cout << "\nIllegal move! That tile is occupied. Please input a valid move." << endl;
        return false;
    }
    return true;
}

bool checkWinner(char board[]) {
    /*This style of win checking is also used for the computerMove().
    This basically covers all (hopefully, unless I made a mistake) win conditions across
    single and multiple boards. It is a bit cumbersome but given that all conditions are checked
    individually and they are all commented, it shouldn't be too hard to debug.
    */
    for (int i = 1; i < 27; i++) {
        if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks single board side to side wins.
            }
        }
        if (i == 1 || i == 10 || i == 19) {
            if (board[i] == board[i + 4] && board[i + 4] == board[i + 8] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks single board top left to bottom right.
            }
        }
        if (i == 3 || i == 12 || i == 21) {
            if (board[i] == board[i + 2] && board[i + 2] == board[i + 4] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks single board top right to bottom left
            }
        }
        if (i == 1 || i == 2 || i == 3 || i == 10 || i == 11 || i == 12 || i == 19 || i == 20 || i == 21) {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks single board top to bottom
            }
        }
        if (i == 1 || i == 4 || i == 7) {
            if (board[i] == board[i + 10] && board[i + 10] == board[i + 20] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks 3D straight
            }
        }
        if (i == 1 || i == 2 || i == 3) {
            if (board[i] == board[i + 12] && board[i + 12] == board[i + 24] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks 3D top to bottom
            }
        }
        if (i == 1) {
            if (board[i] == board[i + 13] && board[i + 13] == board[i + 26] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks 3D top left to bottom right
            }
        }
        if (i == 7) {
            if (board[i] == board[i + 7] && board[i + 7] == board[i + 14] && board[i] != '\0') {
                displayBoard(board);
                cout << "We have a winner! Congratulations to Team " << board[i] << " for winning the game!" << endl;
                return true;  // Checks 3D bottom left to top rigth.
            }
        }
    }
    for (int i = 1; i < 28; i++) {
        if (board[i] == '\0') {
            return false;
        }
    }
    cout << "All tiles are full! The game is drawn." << endl;
    return true;
}

void computerMove(char board[]) {
    /*
    This is quite a long function. The computer will start by picking a random empty cell. This will
    be its default action given none of the 'priority conditions' are fulfilled. These are based on 
    achieving 2/3 winning cells in any winning condition. The computer does not differentiate between
    preventing the player from winning and winning itself. It just tries to put an X whenever the last
    cell in a winning combination is empty.
    */
    bool played = false;
    for (int i = 1; i < 28; i++) {
        if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19 || i == 22 || i == 25) {
            if (board[i] != '\0' && board[i] == board[i + 1]) {
                if (board[i + 2] == '\0') {
                    board[i + 2] = 'X';
                    played = true;
                    cout << i + 2 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 2]) {
                if (board[i + 1] == '\0') {
                    board[i + 1] = 'X';
                    played = true;
                    cout << i + 1 << endl;
                    break;
                }

            } else if (board[i + 1] != '\0' && board[i + 1] == board[i + 2]) {
                if (board[i] == '\0') {
                    board[i] = 'X';

                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Combination of straight wins. Single board.
        }
        if (i == 1 || i == 2 || i == 3 || i == 10 || i == 11 || i == 12 || i == 19 || i == 20 || i == 21) {
            if (board[i] != '\0' && board[i] == board[i + 3]) {
                if (board[i + 6] == '\0') {
                    board[i + 6] = 'X';
                    played = true;
                    cout << i + 6 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 6]) {
                if (board[i + 3] == '\0') {
                    board[i + 3] = 'X';
                    played = true;
                    cout << i + 3 << endl;
                    break;
                }

            } else if (board[i + 3] != '\0' && board[i + 3] == board[i + 6]) {
                if (board[i] == '\0') {
                    board[i] = 'X';
                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Combination of vertical wins. Single board.
        }
        if (i == 1 || i == 10 || i == 19) {
            if (board[i] != '\0' && board[i] == board[i + 4]) {
                if (board[i + 8] == '\0') {
                    board[i + 8] = 'X';
                    played = true;
                    cout << i + 8 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 8]) {
                if (board[i + 4] == '\0') {
                    board[i + 4] = 'X';
                    played = true;
                    cout << i + 4 << endl;
                    break;
                }

            } else if (board[i + 4] != '\0' && board[i + 4] == board[i + 8]) {
                if (board[i] == '\0') {
                    board[i] = 'X';
                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Combination of top left - bottom right wins. Single board.
        }
        if (i == 3 || i == 12 || i == 21) {
            if (board[i] != '\0' && board[i] == board[i + 2]) {
                if (board[i + 4] == '\0') {
                    board[i + 4] = 'X';
                    played = true;
                    cout << i + 4 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 4]) {
                if (board[i + 2] == '\0') {
                    board[i + 2] = 'X';
                    played = true;
                    cout << i + 2 << endl;
                    break;
                }

            } else if (board[i + 2] != '\0' && board[i + 2] == board[i + 4]) {
                if (board[i] == '\0') {
                    board[i] = 'X';
                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Combination of top right - bottom left wins. Single board.
        }
        if (i == 1 || i == 4 || i == 7) {
            if (board[i] != '\0' && board[i] == board[i + 10]) {
                if (board[i + 20] == '\0') {
                    board[i + 20] = 'X';
                    played = true;
                    cout << i + 20 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 20]) {
                if (board[i + 10] == '\0') {
                    board[i + 10] = 'X';
                    played = true;
                    cout << i + 10 << endl;
                    break;
                }

            } else if (board[i + 10] != '\0' && board[i + 10] == board[i + 20]) {
                if (board[i] == '\0') {
                    board[i] = 'X';
                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Straight – Multi board.
        }
        if (i == 1 || i == 2 || i == 3) {
            if (board[i] != '\0' && board[i] == board[i + 12]) {
                if (board[i + 24] == '\0') {
                    board[i + 24] = 'X';
                    played = true;
                    cout << i + 24 << endl;
                    break;
                }

            } else if (board[i] != '\0' && board[i] == board[i + 24]) {
                if (board[i + 12] == '\0') {
                    board[i + 12] = 'X';
                    played = true;
                    cout << i + 12 << endl;
                    break;
                }

            } else if (board[i + 12] != '\0' && board[i + 12] == board[i + 24]) {
                if (board[i] == '\0') {
                    board[i] = 'X';
                    played = true;
                    cout << i << endl;
                    break;
                }

            }  // Vertical – Multi board.
            if (i == 1) {
                if (board[i] != '\0' && board[i] == board[i + 13]) {
                    if (board[i + 26] == '\0') {
                        board[i + 26] = 'X';
                        played = true;
                        cout << i + 26 << endl;
                        break;
                    }

                } else if (board[i] != '\0' && board[i] == board[i + 26]) {
                    if (board[i + 13] == '\0') {
                        board[i + 13] = 'X';
                        played = true;
                        cout << i + 13 << endl;
                        break;
                    }

                } else if (board[i + 13] != '\0' && board[i + 13] == board[i + 26]) {
                    if (board[i] == '\0') {
                        board[i] = 'X';
                        played = true;
                        cout << i << endl;
                        break;
                    }

                }  // Top left - bottom rigth -- Multi board.
            }
            if (i == 7) {
                if (board[i] != '\0' && board[i] == board[i + 7]) {
                    if (board[i + 14] == '\0') {
                        board[i + 14] = 'X';
                        played = true;
                        cout << i + 14 << endl;
                        break;
                    }

                } else if (board[i] != '\0' && board[i] == board[i + 14]) {
                    if (board[i + 7] == '\0') {
                        board[i + 7] = 'X';
                        played = true;
                        cout << i + 7 << endl;
                        break;
                    }

                } else if (board[i + 7] != '\0' && board[i + 7] == board[i + 14]) {
                    if (board[i] == '\0') {
                        board[i] = 'X';
                        played = true;
                        cout << i << endl;
                        break;
                    }

                }  // Bottom left - top rigth -- Multi board.
            }
        }
        /* 
        I know there is a frequent trick where the player checks 1-7 (or corresponding tiles in other boards) and
        goes for 9, winning the game by having 2 winning options. I've decided to hard code a counter to this. This
        will replace the random move. Thus, it should be able to increase the AI difficulty significantly.
        */
        if (i == 7 || i == 16 || i == 25) {
            if (board[i - 6] != '\0' && board[i] == '\0') {
                board[i] = 'X';
                played = true;
                cout << i << endl;
                break;
            } else if (board[i] != '\0' && board[i + 2] == '\0') {
                board[i + 2] = 'X';
                played = true;
                cout << i << endl;
                break;
            }
        }
    }
    if (!played) {
        int randomMove = rand() % 27 + 1;
        while (board[randomMove] != '\0') {
            randomMove = rand() % 27 + 1;
        }
        board[randomMove] = 'X';
        cout << randomMove << endl;
    }

    // Default move is randomized as long as the tile is empty. Makes for a competent opponent!
}

void playTTT(char board[]) {
    /*Basic game loop. Displays board with the instructions.
    Checks if the input is valid.
    Checks if the player won.
    If not, the computer moves.
    Checks if the computer won.
    If not, starts again with the modified board.
    */
    while (true) {
        displayBoard(board);
        string input;
        cout << "Input 'q' to exit the game. Your progress will be lost." << endl;
        cout << "What's your next move? Input a number corresponding to an empty tile.\n"
             << endl;
        cin >> input;
        if (input == "q") {
            break;
        }
        try {
            int move = stoi(input);
        } catch (const invalid_argument) {
            cout << "\nError! Please input a valid number" << endl;
            continue;
        }
        int move = stoi(input);

        if (checkIfLegal(move, board)) {
            board[move] = 'O';
        }
        if (checkWinner(board)) {
            exit(0);
        }
        computerMove(board);
        if (checkWinner(board)) {
            exit(0);
        }
    }
}
