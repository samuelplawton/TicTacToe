#pragma once // Ensures the header is included only once during compilation
#include <array> // Include the array header for std::array usage

// High-level state of a single round of Tic-Tac-Toe.
enum class GameState {
    RUNNING,    // The game is currently ongoing
    HUMAN_WIN,  // The human player has won the game
    CPU_WIN,    // The CPU player has won the game
    TIE         // The game ended in a tie
};

// The TicTacToe class encapsulates board data, rules, and round/score logic.
class TicTacToe {
private:
    std::array<std::array<char, 3>, 3> board{}; // 3x3 board holding 'X', 'O', or ' ' (space) for empty
    GameState state = GameState::RUNNING;       // Current state of the game (RUNNING, HUMAN_WIN, etc.)
    char currentPlayer = 'X';                   // Current player: 'X' for human, 'O' for CPU
    int scoreHuman = 0;                         // Accumulated score for the human player
    int scoreCPU   = 0;                         // Accumulated score for the CPU player

public:
    TicTacToe();                                // Constructor to initialize the game

    // Round lifecycle
    void resetGame();                           // Reset the board, set state to RUNNING, and set human as starter
    void drawBoard() const;                     // Display the current state of the 3x3 board

    // Core rules
    bool placeMark(int row, int col);           // Attempt to place the current player's mark at (row, col)
    void playerMove(int row, int col);          // Process a human player's move at (row, col)
    void computerMove();                        // Process a CPU player's move
    GameState evaluateBoard() const;            // Evaluate and return the current board state (win/tie/running)
    bool isAvailable(int row, int col) const;   // Check if the cell at (row, col) is available for a move
    void switchTurn();                          // Switch to the other player's turn

    // Output / feedback
    void printResult();                         // Print the result of the round (win/tie)
    void printScores() const;                   // Print the current scores for both players

    // Read current round state
    GameState getState() const { return state; } // Getter to access the current game state
};