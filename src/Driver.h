#pragma once
#include <array>

// High-level state of a single round of Tic-Tac-Toe.
enum class GameState {
    RUNNING,
    HUMAN_WIN,
    CPU_WIN,
    TIE
};

// The TicTacToe class encapsulates board data, rules, and round/score logic.
class TicTacToe {
private:
    std::array<std::array<char, 3>, 3> board{}; // 'X','O',' ' (space)
    GameState state = GameState::RUNNING;
    char currentPlayer = 'X';                    // 'X' = human, 'O' = CPU
    int scoreHuman = 0;
    int scoreCPU   = 0;

public:
    TicTacToe();

    // Round lifecycle
    void resetGame();                  // clear board, set RUNNING, human starts
    void drawBoard() const;            // pretty-print 3x3 board

    // Core rules
    bool placeMark(int row, int col);
    void playerMove(int row, int col);
    void computerMove();
    GameState evaluateBoard() const;
    bool isAvailable(int row, int col) const;
    void switchTurn();

    // Output / feedback
    void printResult();
    void printScores() const;

    // Read current round state
    GameState getState() const { return state; }
};