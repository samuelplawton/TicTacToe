//logic.cpp

#include "Driver.h"
#include <iostream>   // I/O for drawBoard, messages
#include <random>     // Random choice for CPU
#include <chrono>     // Seed RNG with clock
#include <vector>     // Store list of empty cells for CPU

using std::cout;
using std::endl;

// ===== CONSTRUCTOR =====
// Initialize scores and set up the first playable round.
// We delegate board clearing & starting player to resetGame().
TicTacToe::TicTacToe()
    : state(GameState::RUNNING),
    currentPlayer('X'),
    scoreHuman(0),
    scoreCPU(0)
{
    resetGame();
}

// ===== RESET GAME =====
// Prepare a fresh 3x3 board and reset round state.
// Human ('X') always starts, but you could randomize this later.
void TicTacToe::resetGame() {
    for (auto& row : board) {
        row.fill(' ');                 // Fill each cell with a space (empty)
    }
    state = GameState::RUNNING;        // New round is active
    currentPlayer = 'X';               // Human begins
}

// ===== DRAW BOARD =====
// Prints coordinate labels and a boxed grid showing each mark.
void TicTacToe::drawBoard() const {
    cout << "\n    0   1   2\n";        // Column headers for user input
    for (int r = 0; r < 3; ++r) {
        cout << "  -------------\n";    // Horizontal divider
        cout << r << " |";              // Row label (0..2)
        for (int c = 0; c < 3; ++c) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n";
    }
    cout << "  -------------\n\n";
}

// ===== CHECK AVAILABILITY =====
// Returns true if (row,col) is inside the 3x3 grid and empty.
bool TicTacToe::isAvailable(int row, int col) const {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false; // Bounds check
    return board[row][col] == ' ';
}

// ===== PLACE MARK =====
// Places the current player's mark if the target cell is available.
// Returns true on success; false if invalid (occupied or out of range).
bool TicTacToe::placeMark(int row, int col) {
    if (!isAvailable(row, col)) return false;
    board[row][col] = currentPlayer;   // Drop 'X' or 'O'
    return true;
}

// ===== SWITCH TURN =====
// Toggle the active player. The main loop calls this only if the round continues.
void TicTacToe::switchTurn() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// ===== EVALUATE BOARD =====
// Checks all win conditions (3 rows, 3 columns, 2 diagonals).
// If no winners and spaces remain, return RUNNING; otherwise TIE.
GameState TicTacToe::evaluateBoard() const {
    // Small helper to test "did 'who' occupy all three cells?"
    auto threeEqual = [&](char a, char b, char c, char who) {
        return (a == who && b == who && c == who);
        };

    // Check rows and columns for either 'X' or 'O'.
    for (int i = 0; i < 3; ++i) {
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'X')) return GameState::HUMAN_WIN;
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'O')) return GameState::CPU_WIN;

        if (threeEqual(board[0][i], board[1][i], board[2][i], 'X')) return GameState::HUMAN_WIN;
        if (threeEqual(board[0][i], board[1][i], board[2][i], 'O')) return GameState::CPU_WIN;
    }

    // Check the two diagonals.
    if (threeEqual(board[0][0], board[1][1], board[2][2], 'X')) return GameState::HUMAN_WIN;
    if (threeEqual(board[0][0], board[1][1], board[2][2], 'O')) return GameState::CPU_WIN;

    if (threeEqual(board[0][2], board[1][1], board[2][0], 'X')) return GameState::HUMAN_WIN;
    if (threeEqual(board[0][2], board[1][1], board[2][0], 'O')) return GameState::CPU_WIN;

    // If any space remains, the round continues.
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return GameState::RUNNING;
        }
    }

    // No spaces and no winners => tie.
    return GameState::TIE;
}

// ===== PLAYER MOVE (HUMAN) =====
// Wraps placeMark with round-state/turn handling.
// If move ends the round (win/tie), we do not switch turns.
void TicTacToe::playerMove(int row, int col) {
    if (state != GameState::RUNNING) return;   // Ignore input if round ended

    if (placeMark(row, col)) {                 // Attempt to drop 'X'
        state = evaluateBoard();               // Recalculate outcome
        if (state == GameState::RUNNING) {
            switchTurn();                      // Hand over to CPU if still playing
        }
    }
    else {
        std::cout << "Invalid move. Cell is taken or out of range.\n";
    }
}

// ===== COMPUTER MOVE (RANDOM) =====
// Very simple AI: choose uniformly among all empty cells.
// You can replace this with minimax later for perfect play.
void TicTacToe::computerMove() {
    if (state != GameState::RUNNING) return;   // Skip if round ended

    // Gather coordinates of all currently empty cells.
    std::vector<std::pair<int, int>> empty;
    empty.reserve(9);
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == ' ') empty.emplace_back(r, c);
        }
    }
    if (empty.empty()) return;                 // Safety check (shouldn�t happen if RUNNING)

    // Pseudo-random engine seeded with current time.
    static std::mt19937 rng(
        static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count())
    );
    std::uniform_int_distribution<int> dist(0, static_cast<int>(empty.size()) - 1);

    // Choose one empty cell at random and play it as the current player ('O').
    auto [row, col] = empty[dist(rng)];
    placeMark(row, col);

    // Evaluate after the move. If still running, return the turn to the human.
    state = evaluateBoard();
    if (state == GameState::RUNNING) {
        switchTurn();
    }
}

// ===== PRINT RESULT & UPDATE SCORES =====
// This function should be called exactly once per round (after the loop ends).
void TicTacToe::printResult() {
    switch (state) {
    case GameState::HUMAN_WIN:
        std::cout << "Human wins!\n";
        ++scoreHuman;           // Update cumulative score
        break;
    case GameState::CPU_WIN:
        std::cout << "Computer wins!\n";
        ++scoreCPU;             // Update cumulative score
        break;
    case GameState::TIE:
        std::cout << "It's a tie!\n";
        break;
    case GameState::RUNNING:
        // Shouldn't be called while RUNNING, but ignore gracefully.
        break;
    }
}

// ===== PRINT RUNNING SCORES =====
// Shows totals across all completed rounds in this session.
void TicTacToe::printScores() const {
    std::cout << "Human Score: " << scoreHuman << "\n"
        << "Computer Score: " << scoreCPU << "\n";
}
