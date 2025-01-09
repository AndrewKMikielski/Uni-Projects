/*  Andrew Mikielski 11/24/2024
 *  Board.h
 *  Contains a square board stored as a 2D array to play
 *  a game that is like a simplified 1024 game.
 *  Includes functions to facilitate board creation,
 *  placement of numbers on the board, and sliding
 *  numbers across the board. */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
using std::vector;

// Defines a struct to be able to keep track of a single space of a board in Board class
struct BoardSpace {
    int row = 0;
    int column = 0;
}; // end struct BoardSpace

class Board {
    public:
        Board();
        void newGame(char newDifficulty); // Start a new game with chosen difficulty.
        // Slides the board in the user's chosen direction. Returns true if the game is still running. Returns false if the game ended.
        bool playTurn(char slideDirection);

    private:
        const static int BOARD_SIZE = 4; // Defines the size of the board.
        int boardArray[BOARD_SIZE][BOARD_SIZE]; // Creates a board as a 2D array of size BOARD_SIZE.
        char difficulty; // 'E' for easy, 'M' for medium, 'H' for hard.

        void placeRandomNumber(); // Randomly places a randomly generated number to an empty space on the board.
        // Slide direction functions:
        void slideLeft();
        void slideRight();
        void slideUp();
        void slideDown();
        // Uses BoardSpace structs to check if a specific space is allowed to slide.
        bool canSpaceSlide(const BoardSpace& currentSpace, const vector<BoardSpace>& staticSpaces) const;
        bool checkForWin() const; // Check board status for a win condition.
        bool checkForLoss() const; // Check board status for a loss condition.
        void displayBoard() const; // Displays current board status.
}; // end Board class declaration

#endif // BOARD_H