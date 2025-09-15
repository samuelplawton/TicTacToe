#include "driver.h" // Include the header file for TicTacToe class and related declarations
#include <iostream> // For input/output stream operations
#include <random>   // For random number generation (used in computerMove)
#include <chrono>   // For time-related functions (used to seed RNG)
#include <vector>   // For using std::vector (used in computerMove)

using std::cout; // Use cout from std namespace

TicTacToe::TicTacToe() // Constructor for TicTacToe class
    : state(GameState::RUNNING), currentPlayer('X'), scoreHuman(0), scoreCPU(0) { // Initialize state, currentPlayer, and scores
    resetGame(); // Reset the game board and state
}

void TicTacToe::resetGame() { // Reset the game board and state
    for (auto& row : board) row.fill(' '); // Fill each row with spaces (empty cells)
    state = GameState::RUNNING; // Set game state to running
    currentPlayer = 'X'; // human first // Set current player to 'X' (human starts)
}

void TicTacToe::drawBoard() const { // Draw the current state of the board
    cout << "\n    0   1   2\n"; // Print column headers
    for (int r = 0; r < 3; ++r) { // For each row
        cout << "  -------------\n"; // Print horizontal line
        cout << r << " |"; // Print row number and left border
        for (int c = 0; c < 3; ++c) { // For each column
            cout << " " << board[r][c] << " |"; // Print cell value and right border
        }
        cout << "\n"; // Newline at end of row
    }
    cout << "  -------------\n\n"; // Print bottom border
}

bool TicTacToe::isAvailable(int row, int col) const { // Check if a cell is available
    if (row < 0 || row > 2 || col < 0 || col > 2) return false; // Out of bounds check
    return board[row][col] == ' '; // Return true if cell is empty
}

bool TicTacToe::placeMark(int row, int col) { // Place the current player's mark on the board
    if (!isAvailable(row, col)) return false; // If cell is not available, return false
    board[row][col] = currentPlayer; // Place the mark
    return true; // Return true for successful placement
}

void TicTacToe::switchTurn() { // Switch the current player
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Toggle between 'X' and 'O'
}

GameState TicTacToe::evaluateBoard() const { // Evaluate the current board state
    auto threeEqual = [&](char a, char b, char c, char who) { // Lambda to check if three cells are equal to 'who'
        return (a == who && b == who && c == who);
    };

    for (int i = 0; i < 3; ++i) { // Check rows and columns for win
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'X')) return GameState::HUMAN_WIN; // Row win for X
        if (threeEqual(board[i][0], board[i][1], board[i][2], 'O')) return GameState::CPU_WIN;   // Row win for O

        if (threeEqual(board[0][i], board[1][i], board[2][i], 'X')) return GameState::HUMAN_WIN; // Column win for X
        if (threeEqual(board[0][i], board[1][i], board[2][i], 'O')) return GameState::CPU_WIN;   // Column win for O
    }

    if (threeEqual(board[0][0], board[1][1], board[2][2], 'X')) return GameState::HUMAN_WIN; // Diagonal win for X
    if (threeEqual(board[0][0], board[1][1], board[2][2], 'O')) return GameState::CPU_WIN;   // Diagonal win for O
    if (threeEqual(board[0][2], board[1][1], board[2][0], 'X')) return GameState::HUMAN_WIN; // Anti-diagonal win for X
    if (threeEqual(board[0][2], board[1][1], board[2][0], 'O')) return GameState::CPU_WIN;   // Anti-diagonal win for O

    for (const auto& row : board) // Check for any empty cells
        for (char cell : row)
            if (cell == ' ') return GameState::RUNNING; // Game still running if empty cell found

    return GameState::TIE; // No winner and no empty cells means tie
}

void TicTacToe::playerMove(int row, int col) { // Handle a move by the human player
    if (state != GameState::RUNNING) return; // Do nothing if game is not running
    if (placeMark(row, col)) { // Try to place the mark
        state = evaluateBoard(); // Update game state after move
        if (state == GameState::RUNNING) switchTurn(); // If game still running, switch turn
    } else {
        std::cout << "Invalid move. Cell is taken or out of range.\n"; // Print error for invalid move
    }
}

void TicTacToe::computerMove() { // Handle a move by the computer player
    if (state != GameState::RUNNING) return; // Do nothing if game is not running

    std::vector<std::pair<int, int>> empty; // Vector to store empty cell positions
    empty.reserve(9); // Reserve space for up to 9 positions
    for (int r = 0; r < 3; ++r) // Iterate through rows
        for (int c = 0; c < 3; ++c) // Iterate through columns
            if (board[r][c] == ' ') empty.emplace_back(r, c); // Add empty cell to vector

    if (empty.empty()) return; // If no empty cells, return

    static std::mt19937 rng(
        static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count())); // Static random number generator seeded with current time
    std::uniform_int_distribution<int> dist(0, static_cast<int>(empty.size()) - 1); // Distribution for picking a random empty cell

    auto [row, col] = empty[dist(rng)]; // Choose a random empty cell
    placeMark(row, col); // Place the computer's mark

    state = evaluateBoard(); // Update game state after move
    if (state == GameState::RUNNING) switchTurn(); // If game still running, switch turn
}

void TicTacToe::printResult() { // Print the result of the game and update scores
    switch (state) { // Check game state
    case GameState::HUMAN_WIN: // If human wins
        std::cout << "Human wins!\n"; ++scoreHuman; break; // Print message and increment human score
    case GameState::CPU_WIN: // If computer wins
        std::cout << "Computer wins!\n"; ++scoreCPU; break; // Print message and increment computer score
    case GameState::TIE: // If tie
        std::cout << "It's a tie!\n"; break; // Print tie message
    default: break; // No action for other states
    }
}

void TicTacToe::printScores() const { // Print the scores of both players
    std::cout << "Human Score: " << scoreHuman
              << " | Computer Score: " << scoreCPU << "\n"; // Print scores
}