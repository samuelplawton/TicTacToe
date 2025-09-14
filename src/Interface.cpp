#include <iostream>
#include <vector>
using namespace std;

// Draws the TicTacToe board
void displayBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i];
        if (i % 3 != 2) cout << " |";
        if (i % 3 == 2 && i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n\n";
}

// Ask player for a move
int getPlayerMove(char player) {
    int move;
    cout << "Player " << player << ", enter your move (1-9): ";
    cin >> move;
    return move - 1; // convert to 0-based index
}
