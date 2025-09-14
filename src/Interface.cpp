//interface.cpp

#include "Driver.h"
#include <iostream>   // std::cout, std::cin
#include <limits>     // std::numeric_limits for input flushing

// The main game loop coordinates rounds:
// - Start a new round with resetGame()
// - Alternate between human and CPU moves until evaluateBoard() != RUNNING
// - Print final board, announce result, update/show scores
// - Ask if the user wants to play another round
int main() {
    TicTacToe game;     // Owns board/state/scores and all game logic methods
    char choice = 'y';  // User’s replay response

    do {
        // --- New Round ---
        game.resetGame();

        // --- Round Loop: continue while no win/tie detected ---
        while (game.getState() == GameState::RUNNING) {
            game.drawBoard();   // Show current board before human input

            // ===== HUMAN TURN =====
            int row, col;
            std::cout << "Enter row and col (0–2): ";

            // Validate input: if the user types non-integers, clear and retry.
            if (!(std::cin >> row >> col)) {
                std::cin.clear(); // clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard line
                std::cout << "Invalid input. Please enter two integers from 0 to 2.\n";
                continue;        // Prompt again
            }

            // Apply the human move; this may finish the round (win/tie),
            // or it may switch turn to the CPU if the round continues.
            game.playerMove(row, col);

            // ===== CPU TURN (only if the round is still running) =====
            if (game.getState() == GameState::RUNNING) {
                game.computerMove(); // random empty-cell choice
            }
        }

        // --- Round End: show final board and result, then scores ---
        game.drawBoard();
        game.printResult();   // Also updates cumulative scores
        game.printScores();

        // --- Ask to play again ---
        std::cout << "Play again? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    std::cout << "Thanks for playing!\n";
    return 0;
}

