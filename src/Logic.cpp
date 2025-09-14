#include "driver.h"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using std::cout;

TicTacToe::TicTacToe()
    : state(GameState::RUNNING), currentPlayer('X'), scoreHuman(0), scoreCPU(0) {
    resetGame();
}

void TicTacToe::resetGame() {
    for (auto& row : board) row.fill(' ');
    state = GameState::RUNNING;
    currentPlayer = 'X'; // human first
}

void TicTacToe::drawBoard() const {
    cout << "\n    0   1   2\n";
    for (int r = 0; r < 3; ++r) {
        cout << "  -------------\n";
        cout << r << " |";
        for (int c = 0; c < 3; ++c) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n";
    }
    cout << "  -------------\n\n";
}

bool TicTacToe::isAvailable(int row, int col) const {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    return board[row][col] == ' ';
}

bool TicTacToe::placeMark(int row, int col) {
    if (!isAvailable(row, col)) return false;
    board[row][col] = currentPlayer;
    return true;
}

void TicTacToe::switchTurn() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

GameState TicTacToe::evaluateBoard() const {
    auto threeEqual = [&](char a, char b, char c, char who) {
        return (a == who && b == who && c == who);
    };

    for (int i = 0; i < 3; ++i) {
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'X')) return GameState::HUMAN_WIN;
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'O')) return GameState::CPU_WIN;

        if (threeEqual(board[0][i], board[1][i], board[2][i], 'X')) return GameState::HUMAN_WIN;
        if (threeEqual(board[0][i], board[1][i], board[2][i], 'O')) return GameState::CPU_WIN;
    }

    if (threeEqual(board[0][0], board[1][1], board[2][2], 'X')) return GameState::HUMAN_WIN;
    if (threeEqual(board[0][0], board[1][1], board[2][2], 'O')) return GameState::CPU_WIN;
    if (threeEqual(board[0][2], board[1][1], board[2][0], 'X')) return GameState::HUMAN_WIN;
    if (threeEqual(board[0][2], board[1][1], board[2][0], 'O')) return GameState::CPU_WIN;

    for (const auto& row : board)
        for (char cell : row)
            if (cell == ' ') return GameState::RUNNING;

    return GameState::TIE;
}

void TicTacToe::playerMove(int row, int col) {
    if (state != GameState::RUNNING) return;
    if (placeMark(row, col)) {
        state = evaluateBoard();
        if (state == GameState::RUNNING) switchTurn();
    } else {
        std::cout << "Invalid move. Cell is taken or out of range.\n";
    }
}

void TicTacToe::computerMove() {
    if (state != GameState::RUNNING) return;

    std::vector<std::pair<int, int>> empty;
    empty.reserve(9);
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == ' ') empty.emplace_back(r, c);

    if (empty.empty()) return;

    static std::mt19937 rng(
        static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, static_cast<int>(empty.size()) - 1);

    auto [row, col] = empty[dist(rng)];
    placeMark(row, col);

    state = evaluateBoard();
    if (state == GameState::RUNNING) switchTurn();
}

void TicTacToe::printResult() {
    switch (state) {
    case GameState::HUMAN_WIN:
        std::cout << "Human wins!\n"; ++scoreHuman; break;
    case GameState::CPU_WIN:
        std::cout << "Computer wins!\n"; ++scoreCPU; break;
    case GameState::TIE:
        std::cout << "It's a tie!\n"; break;
    default: break;
    }
}

void TicTacToe::printScores() const {
    std::cout << "Human Score: " << scoreHuman
              << " | Computer Score: " << scoreCPU << "\n";
}