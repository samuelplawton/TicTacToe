#include "Interface.h"
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;

int Interface::run() {
    do {
        game.resetGame();

        while (game.getState() == GameState::RUNNING) {
            draw();

            auto [row, col] = promptMove();
            if (row < 0) continue;

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

std::pair<int,int> Interface::promptMove() const {
    int row, col;
    cout << "Enter row and col (0-2): ";
    if (!(cin >> row >> col)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter two integers from 0 to 2.\n";
        return {-1, -1};
    }
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        cout << "Out of range. Use 0, 1, or 2.\n";
        return {-1, -1};
    }
    return {row, col};
}

bool Interface::promptPlayAgain() const {
    char choice;
    cout << "Play again? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void Interface::draw() const {
    game.drawBoard();
}