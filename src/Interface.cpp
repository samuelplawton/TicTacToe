#include "Interface.h" // Interface declarations
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

// Main loop to run the Tic Tac Toe game interface
int Interface::run() {
    do {
        game.resetGame();

        while (game.getState() == GameState::RUNNING) {
            draw();

            auto [row, col] = promptMove();
            if (row < 0) continue; // invalid input; reprompt

            game.playerMove(row, col);

            if (game.getState() == GameState::RUNNING) {
                game.computerMove();
            }
        }

        draw();
        game.printResult();
        game.printScores();

        if (!promptPlayAgain()) break;

    } while (true);

    cout << "Thanks for playing!\n";
    return 0;
}

// Prompt the user for their move and validate the input
std::pair<int,int> Interface::promptMove() const {
    char rowChar;
    int colNum;
    cout << "Enter row (A-C) and column (1-3), e.g. B 2: ";
    if (!(cin >> rowChar >> colNum)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a row letter (A-C) and a column number (1-3).\n";
        return {-1, -1};
    }
    // Normalize to uppercase
    if (rowChar >= 'a' && rowChar <= 'z') rowChar = char(rowChar - 'a' + 'A');

    int row = TicTacToe::rowIndexFromLabel(rowChar);
    int col = TicTacToe::colIndexFromLabel(colNum);
    if (row < 0 || col < 0) {
        cout << "Out of range. Use rows A, B, C and columns 1, 2, 3.\n";
        return {-1, -1};
    }
    return {row, col};
}

// Ask the user if they want to play again
bool Interface::promptPlayAgain() const {
    char choice;
    cout << "Play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

// Draw the current state of the game board
void Interface::draw() const {
    game.drawBoard();
}