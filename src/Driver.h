#pragma once // Ensures the header is included only once during compilation
#include <array> // std::array for the 3x3 board

// High-level state of a single round of Tic-Tac-Toe.
enum class GameState {
    RUNNING,    // The game is currently ongoing
    HUMAN_WIN,  // The human player has won the game
    CPU_WIN,    // The CPU player has won the game
    TIE         // The game ended in a tie
};

// The TicTacToe class encapsulates board data, rules, and round/score logic.
// \n// Public API now supports human-friendly coordinates: ROW = 'A'|'B'|'C', COL = 1|2|3.
// Internally, the board still uses 0-based indices (0..2). Conversions are handled
// by private helper functions declared below.
class TicTacToe {
private:
    std::array<std::array<char, 3>, 3> board{}; // 3x3 board holding 'X', 'O', or ' ' (space) for empty
    GameState state = GameState::RUNNING;       // Current state of the game (RUNNING, HUMAN_WIN, etc.)
    char currentPlayer = 'X';                   // Current player: 'X' for human, 'O' for CPU
    int scoreHuman = 0;                         // Accumulated score for the human player
    int scoreCPU   = 0;                         // Accumulated score for the CPU player

public:
    // Public helpers so UI code can convert labels
    static int rowIndexFromLabel(char rowLabel);   // 'A'/'a'->0, 'B'/'b'->1, 'C'/'c'->2; returns -1 if invalid
    static int colIndexFromLabel(int colLabel);    // 1->0, 2->1, 3->2; returns -1 if invalid

    TicTacToe();                                // Constructor to initialize the game

    // Round lifecycle
    void resetGame();                           // Reset the board, set state to RUNNING, and set human as starter
    void drawBoard() const;                     // Display the board with headers: columns 1..3 and rows A..C

    // Core rules (internal 0-based coordinates)
    bool placeMark(int row, int col);           // Attempt to place the current player's mark at (row, col)
    void playerMove(int row, int col);          // Process a human player's move at (row, col)
    bool isAvailable(int row, int col) const;   // Check if the cell at (row, col) is available for a move

    // Core rules (human-friendly labeled coordinates)
    bool placeMark(char rowLabel, int colLabel); // e.g., 'A',1  / 'B',3  — converts and forwards to (row,col)
    void playerMove(char rowLabel, int colLabel);
    bool isAvailable(char rowLabel, int colLabel) const;

    void computerMove();                        // Process a CPU player's move
    GameState evaluateBoard() const;            // Evaluate and return the current board state (win/tie/running)
    void switchTurn();                          // Switch to the other player's turn

    // Output / feedback
    void printResult();                         // Print the result of the round (win/tie)
    void printScores() const;                   // Print the current scores for both players

    // Read current round state
    GameState getState() const { return state; } // Getter to access the current game state
};