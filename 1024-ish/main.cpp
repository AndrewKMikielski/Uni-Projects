/*  Andrew Mikielski Project 5
 *  11/24/2024
 *  main.cpp
 *  This program is a lite version of the game 1024.
 *  This is a math game on a 4x4 grid with numbers that are powers of 2.
 *  Players can slide the numbers on the board by one spot in a direction
 *  of their choosing, and matching numbers will combine when they
 *  slide into each other. A random number is added to the board after each
 *  turn. The goal is to keep combining numbers to reach 256, 512, or 1024 in
 *  a single space, depending on chosen difficulty level. */

#include <iostream>
#include "mersenne-twister.h"
#include "Board.h"

using namespace std;

/*  Asks for and returns user's input for the game mode.
 *  'E' for easy, 'M' for medium, 'H' for hard. */
char chooseGameMode();

/*  Asks for and returns user's input for the board move.
 *  'U' for up, 'D' for down, 'L' for left, 'R' for right. */
char chooseMove();

//  Creates and uses a Board class to play 1024.
void playGame();

int main() 
{
    int randSeed;
    cout << "Enter random seed: ";
    cin >> randSeed;
    seed(randSeed);
    
    // Play 1024
    playGame();

    return 0;
} // end main()

/*  Asks for and returns user's input for the game mode.
 *  'E' for easy, 'M' for medium, 'H' for hard. */
char chooseGameMode() {
    char userInput;

    cout << "Choose game mode: Easy (E), Medium (M), or Hard (H): ";
    cin >> userInput;
    userInput = toupper(userInput);

    while(userInput != 'E' && userInput != 'M' && userInput != 'H') {
        cout << "Error: Invalid mode." << endl;
        cout << "Choose game mode: Easy (E), Medium (M), or Hard (H): ";
        cin >> userInput;
        userInput = toupper(userInput);
    }
    cout << endl << endl;

    return userInput;
} // end chooseGameMode()

/*  Asks for and returns user's input for the board move.
 *  'U' for up, 'D' for down, 'L' for left, 'R' for right. */
char chooseMove() {
    char userInput;

    cout << "Enter move: U, D, L, or R. Q to quit: ";
    cin >> userInput;
    userInput = toupper(userInput);
    while(userInput != 'U' && userInput != 'D' && userInput != 'L' && userInput != 'R' && userInput != 'Q') {
        cout << endl << "Error: Invalid move." << endl;
        cout << "Enter move: U, D, L, or R. Q to quit: ";
        cin >> userInput;
        userInput = toupper(userInput);
    }

    return userInput;
} // end chooseMove()

/*  Creates and uses a Board class to play 1024.
 *  Game ends when the user wins or loses. */
void playGame() {
    char userInput;
    bool isGameRunning = true;
    // Create Board class object
    Board GameBoard;

    userInput = chooseGameMode();

    // Start a new game with the user's chosen game mode.
    GameBoard.newGame(userInput);

    // This do/while loop controls everything happening in a single turn.
    do {
        // Ask the user to make a move
        userInput = chooseMove();
        
        // Makes the move or allows the user to quit the game
        if(userInput != 'Q') {
            // Board.playTurn() returns false when the game is over.
            isGameRunning = GameBoard.playTurn(userInput);
        } else {
            // If the player chooses to quit we exit the game loop.
            break;
        }
    } while(isGameRunning);
} // end playGame()