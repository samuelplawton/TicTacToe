#pragma once // Ensure the header is included only once during compilation
#include "driver.h" // Include the driver header for TicTacToe game logic
#include <utility> // Include utility for std::pair usage

class Interface { // Declare the Interface class to handle game interaction
public:
    int run(); // Method to start and run the game loop

private:
    TicTacToe game{}; // Instance of the TicTacToe game
    std::pair<int,int> promptMove() const; // Method to prompt the user for their move, returns a pair of coordinates
    bool promptPlayAgain() const; // Method to ask the user if they want to play again
    void draw() const; // Method to draw the current game state on the interface
};