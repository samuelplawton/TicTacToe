#include "Interface.h" // Include the header file for the Interface class
#include <iostream> // Include for input/output stream objects
#include <limits> // Include for numeric_limits, used to handle input errors

using std::cout; // Use cout for console output
using std::cin; // Use cin for console input
using std::numeric_limits; // Use numeric_limits to handle stream limits
using std::streamsize; // Use streamsize for input buffer size

// Main loop to run the Tic Tac Toe game interface
int Interface::run() {
    do {
        game.resetGame(); // Reset the game state at the beginning of each round

        // Continue the game loop while the game is running
        while (game.getState() == GameState::RUNNING) {
            draw(); // Draw the current state of the game board

            auto [row, col] = promptMove(); // Prompt the user for a move (row and column)
            if (row < 0) continue; // If input was invalid, prompt again

            game.playerMove(row, col); // Execute the player's move

            // If the game is still running after the player's move, let the computer make a move
            if (game.getState() == GameState::RUNNING) {
                game.computerMove();
            }
        }

        draw(); // Draw the final state of the game board
        game.printResult(); // Print the result of the game (who won or if it was a draw)
        game.printScores(); // Print the current scores

        if (!promptPlayAgain()) break; // Ask the user if they want to play again; if not, exit loop

    } while (true); // Repeat the game loop as long as the user wants to play again

    cout << "Thanks for playing!\n"; // Print a thank you message at the end
    return 0; // Return 0 to indicate successful execution
}

// Prompt the user for their move and validate the input
std::pair<int,int> Interface::promptMove() const {
    int row, col; // Variables to store row and column input from the user
    cout << "Enter row and col (0-2): "; // Ask the user for input
    if (!(cin >> row >> col)) { // If the input is not two integers
        cin.clear(); // Clear the error flag on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input line
        cout << "Invalid input. Please enter two integers from 0 to 2.\n"; // Inform the user of invalid input
        return {-1, -1}; // Return invalid coordinates
    }
    if (row < 0 || row > 2 || col < 0 || col > 2) { // If row or column is out of the allowed range
        cout << "Out of range. Use 0, 1, or 2.\n"; // Inform the user of out-of-range input
        return {-1, -1}; // Return invalid coordinates
    }
    return {row, col}; // Return the valid row and column
}

// Ask the user if they want to play again
bool Interface::promptPlayAgain() const {
    char choice; // Variable to store the user's choice
    cout << "Play again? (y/n): "; // Prompt the user
    cin >> choice; // Read the user's choice
    return (choice == 'y' || choice == 'Y'); // Return true if the user wants to play again
}

// Draw the current state of the game board
void Interface::draw() const {
    game.drawBoard(); // Call the drawBoard method of the game object
}