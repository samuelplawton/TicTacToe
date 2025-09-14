
//driver.h

#pragma once                // Ensure this header is included only once per TU
#include <array>            // Fixed-size 2D array for the board
#include <utility>          // std::pair (used by CPU move)

// High-level state of a single round of Tic-Tac-Toe.
// We separate "round state" (who won / running / tie) from "running scores".
enum class GameState {
    RUNNING,    // The round is still in progress
    HUMAN_WIN,  // Human ('X') achieved 3-in-a-row
    CPU_WIN,    // Computer ('O') achieved 3-in-a-row
    TIE         // Board has no spaces left and no winner
};

// The TicTacToe class encapsulates board data, rules, and round/score logic.
class TicTacToe {
private:
    // 3x3 grid; each cell is 'X', 'O', or ' ' (space = empty).
    std::array<std::array<char, 3>, 3> board{};

    // Current outcome of the round; drives the main game loop.
    GameState state = GameState::RUNNING;

    // Whose turn is it? Human = 'X', CPU = 'O'.
    char currentPlayer = 'X';

    // Cumulative scores across multiple rounds in the same program run.
    int scoreHuman = 0;
    int scoreCPU = 0;

public:
    // Constructor: initializes scores and prepares the first round.
    TicTacToe();

    // ===== Round Lifecycle =====
    void resetGame();                  // Clear board, set RUNNING, human starts
    void drawBoard() const;            // Pretty-print the 3x3 grid

    // ===== Core Moves & Rules =====
    bool placeMark(int row, int col);  // Try to drop 'X' or 'O' at (row,col) if empty
    void playerMove(int row, int col); // Human move wrapper (validates + turn logic)
    void computerMove();               // CPU picks a random empty cell
    GameState evaluateBoard() const;   // Check rows/cols/diagonals for a winner; tie/full
    bool isAvailable(int row, int col) const; // Is (row,col) in-bounds and empty?
    void switchTurn();                 // Toggle 'X' <-> 'O'

    // ===== Output / Feedback =====
    void printResult();                // Announce winner/tie and update running scores
    void printScores() const;          // Show cumulative scores

    // Helper for the main loop to read the current round state.
    GameState getState() const { return state; }
};
