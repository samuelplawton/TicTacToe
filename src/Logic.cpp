#include <iostream>
#include <vector>
#include "Driver.h"
using namespace std;

extern void displayBoard(const vector<char>& board);
extern int getPlayerMove(char player);

bool isWin(const vector<char>& board, char player) {
    int winPatterns[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diagonals
    };
    for (auto& pattern : winPatterns) {
        if (board[pattern[0]] == player &&
            board[pattern[1]] == player &&
            board[pattern[2]] == player) {
            return true;
        }
    }
    return false;
}

bool isDraw(const vector<char>& board) {
    for (char c : board) {
        if (c == ' ') return false;
    }
    return true;
}

void playGame() {
    vector<char> board(9, ' ');
    char currentPlayer = 'X';
    bool gameOver = false;

    while (!gameOver) {
        displayBoard(board);

        int move = getPlayerMove(currentPlayer);
        if (move < 0 || move >= 9 || board[move] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[move] = currentPlayer;

        if (isWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameOver = true;
        }
        else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}
