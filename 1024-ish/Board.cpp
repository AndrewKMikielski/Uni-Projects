/*  Andrew Mikielski 11/24/2024
 *  Board.cpp
 *  Contains a square board stored as a 2D array to play
 *  a game that is like a simplified 1024 game.
 *  Includes functions to facilitate board creation,
 *  placement of numbers on the board, and sliding
 *  numbers across the board. */

 #include <iostream>
 #include <iomanip>
 #include <vector>
 #include "mersenne-twister.h"
 #include "Board.h"
 
 using namespace std;

//  Constructor
Board::Board() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            boardArray[i][j] = 0;
        }
    }

    // Default difficulty is easy.
    difficulty = 'E';
} // end Constructor

/*  Sets the difficulty level of the game.
 *  Sets two random numbers onto the board. 
 *  Difficulty levels:
 *  'E' for easy
 *  'M' for Medium
 *  'H' for hard
 *  Default difficulty is easy. */
void Board::newGame(char newDifficulty) {
    // Reset the board to all 0's in case the object is reused.
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            boardArray[i][j] = 0;
        }
    }

    switch(newDifficulty) {
        case 'E':
        case 'M':
        case 'H':
            difficulty = newDifficulty;
            break;
        default:
            difficulty = 'E';
            break;
    }
    
    placeRandomNumber();
    placeRandomNumber();
    // Display the starting board.
    displayBoard();
} // end Board::newGame()

/*  Randomly chooses an open board space to place
 *  a random value of 2 or 4 into the space. */
void Board::placeRandomNumber() {
    int numOpenSpace = 0;
    int randNum;
    BoardSpace openSpace;
    vector<BoardSpace> OpenSpaceList;

    // Count the number of, and keep track of, the empty spaces
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == 0) {
                numOpenSpace++;
                openSpace.row = i;
                openSpace.column = j;
                OpenSpaceList.push_back(openSpace);
            }
        }
    }

    // Choose the random free space
    randNum = chooseRandomNumber(1, numOpenSpace);
    // Get the location of the randomly chosen free space.
    openSpace.row = OpenSpaceList[randNum - 1].row;
    openSpace.column = OpenSpaceList[randNum - 1].column;

    // Assign a randomly chosen 2 or 4 for the space.
    randNum = chooseRandomNumber(1, 10);
    if(difficulty == 'E') { // 50% chance of a 2
        if(randNum <= 5) {
            boardArray[openSpace.row][openSpace.column] = 2;
        } else {
            boardArray[openSpace.row][openSpace.column] = 4;
        }
    } else if(difficulty == 'M') { // 70% chance of a 2
        if(randNum <= 7) {
            boardArray[openSpace.row][openSpace.column] = 2;
        } else {
            boardArray[openSpace.row][openSpace.column] = 4;
        }
    } else { // 90% chance of a 2
        if(randNum <= 9) {
            boardArray[openSpace.row][openSpace.column] = 2;
        } else {
            boardArray[openSpace.row][openSpace.column] = 4;
        }
    }
} // end Board::placeRandomNumber()

/*  Outputs the current state of the board.
 *  Each number gets 4 white spaces. 0 is displayed as a blank space.
 *  Pipes, | , are displayed in between each column, and as left and right edge borders.
 *  Dashes, - , are displayed in between rows, and as top and bottom edge borders. */
void Board::displayBoard() const {
    /* Calculate total character width
     * Example: BOARD_SIZE = 4 and WHITESPACE_WIDTH = 4
     *      4 * 4 + 4 + 1 = 21 characters wide */
    const int WHITESPACE_WIDTH = 4;
    const int BOARD_WIDTH = WHITESPACE_WIDTH * BOARD_SIZE + BOARD_SIZE + 1;

    // Draws the board.
    cout << endl << left << setfill('-') << setw(BOARD_WIDTH) << "-" << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << setfill(' ') << "|";
        // Inner loop draws the rows that contain board values.
        for (int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == 0) {
                cout << right << setw(WHITESPACE_WIDTH + 1) << "|";
            } else {
                cout << right << setw(WHITESPACE_WIDTH) << boardArray[i][j] << "|";
            }
        }
        cout << endl << left << setfill('-') << setw(BOARD_WIDTH) << "-" << endl;
    }
} // end Board::displayBoard()

/*  Slides the board based on user input, adds a
 *  randomly placed number after the slide is complete,
 *  and displays the board.
 *  Returns true if the game is still running.
 *  Returns false if the game has ended. */
bool Board::playTurn(char slideDirection) {
    switch(slideDirection) {
        case 'U':
            slideUp();
            break;
        case 'D':
            slideDown();
            break;
        case 'L':
            slideLeft();
            break;
        case 'R':
            slideRight();
            break;
    }

    // Add a new number and display the board after sliding.
    placeRandomNumber();
    displayBoard();

    // Check if the user won or lost.
    if(checkForWin()) {
        cout << "You win!" << endl;
        return false;
    } else if(checkForLoss()) {
        cout << "You lose." << endl;
        return false;
    }

    return true;
} // end Board::playTurn()

/*  Returns true when the player gets one number to become the target number.
 *  Target Number:
 *  Easy: 256
 *  Medium: 512
 *  Hard: 1024 */
bool Board::checkForWin() const {
    int targetNum;
    
    if(difficulty == 'E') {
        targetNum = 256;
    } else if(difficulty == 'M') {
        targetNum = 512;
    } else if(difficulty == 'L') {
        targetNum = 1024;
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == targetNum) {
                return true;
            }
        }
    }

    return false;
} // end Board::checkForWin()

/*  The player loses when there are no more open spaces.
 *  Returns true when there are no open spaces.
 *  Returns false if there's at least 1 open space. */
bool Board::checkForLoss() const {
    int numOpenSpace = 0;

    // Count the number of the empty spaces
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == 0) {
                numOpenSpace++;
            }
        }
    }

    if(numOpenSpace == 0) {
        return true;
    }

    return false;
} // end Board::checkForLoss()

//  Combines and slides numbers towards the left.
void Board::slideLeft() {
    BoardSpace staticSpace;
    BoardSpace currentSpace;
    vector<BoardSpace> staticSpaces;

    // Check for possible number combines and combine them
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 1; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == boardArray[i][j - 1]) {
                boardArray[i][j - 1] += boardArray[i][j];
                boardArray[i][j] = 0;

                // Track that this space has slid so it does not slide again this turn.
                staticSpace.row = i;
                staticSpace.column = j - 1;
                staticSpaces.push_back(staticSpace);
            }
        }
    }

    /* Slide left, if possible
     * We could re-use staticSpace in place of currentSpace, however
     * it's a bit confusing to read the code below with staticSpace. */
    for(int i = 0; i < BOARD_SIZE; i++) {
        for( int j = 1; j < BOARD_SIZE; j++) {
            if(boardArray[i][j - 1] == 0) {
                currentSpace.row = i;
                currentSpace.column = j;
                if(canSpaceSlide(currentSpace, staticSpaces)) {
                    boardArray[i][j - 1] = boardArray[i][j];
                    boardArray[i][j] = 0;
                }
            }
        }
    }
} // end Board::slideLeft()

//  Combines and slides numbers towards the right.
void Board::slideRight() {
    BoardSpace staticSpace;
    BoardSpace currentSpace;
    vector<BoardSpace> staticSpaces;

    // Check for possible number combines and combine them
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = BOARD_SIZE - 2; j >= 0; j--) {
            if(boardArray[i][j] == boardArray[i][j + 1]) {
                boardArray[i][j + 1] += boardArray[i][j];
                boardArray[i][j] = 0;
                
                // Track that this space has slid so it does not slide again this turn.
                staticSpace.row = i;
                staticSpace.column = j + 1;
                staticSpaces.push_back(staticSpace);
            }
        }
    }

    /* Slide right, if possible
     * We could re-use staticSpace in place of currentSpace, however
     * it's a bit confusing to read the code below with staticSpace. */
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = BOARD_SIZE - 2; j >= 0; j--) {
            if(boardArray[i][j + 1] == 0) {
                currentSpace.row = i;
                currentSpace.column = j;
                if(canSpaceSlide(currentSpace, staticSpaces)) {
                    boardArray[i][j + 1] = boardArray[i][j];
                    boardArray[i][j] = 0;
                }
            }
        }
    }
} // end Board::slideRight()

//  Combines and slides numbers towards the top.
void Board::slideUp() {
    BoardSpace staticSpace;
    BoardSpace currentSpace;
    vector<BoardSpace> staticSpaces;

    // Check for possible number combines and combine them
    for(int i = 1; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == boardArray[i - 1][j]) {
                boardArray[i - 1][j] += boardArray[i][j];
                boardArray[i][j] = 0;
                
                // Track that this space has slid so it does not slide again this turn.
                staticSpace.row = i - 1;
                staticSpace.column = j;
                staticSpaces.push_back(staticSpace);
            }
        }
    }

    /* Slide up, if possible
     * We could re-use staticSpace in place of currentSpace, however
     * it's a bit confusing to read the code below with staticSpace. */
    for(int i = 1; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i - 1][j] == 0) {
                currentSpace.row = i;
                currentSpace.column = j;
                if(canSpaceSlide(currentSpace, staticSpaces)) {
                    boardArray[i - 1][j] = boardArray[i][j];
                    boardArray[i][j] = 0;
                }
            }
        }
    }
} // end Board::slideUp()

//  Combines and slides numbers towards the bottom.
void Board::slideDown() {
    BoardSpace staticSpace;
    BoardSpace currentSpace;
    vector<BoardSpace> staticSpaces;

    // Check for possible number combines and combine them
    for(int i = BOARD_SIZE - 2; i >= 0; i--) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i][j] == boardArray[i + 1][j]) {
                boardArray[i + 1][j] += boardArray[i][j];
                boardArray[i][j] = 0;
                
                // Track that this space has slid so it does not slide again this turn.
                staticSpace.row = i + 1;
                staticSpace.column = j;
                staticSpaces.push_back(staticSpace);
            }
        }
    }

    /* Slide down, if possible
     * We could re-use staticSpace in place of currentSpace, however
     * it's a bit confusing to read the code below with staticSpace. */
    for(int i = BOARD_SIZE - 2; i >= 0; i--) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(boardArray[i + 1][j] == 0) {
                currentSpace.row = i;
                currentSpace.column = j;
                if(canSpaceSlide(currentSpace, staticSpaces)) {
                    boardArray[i + 1][j] = boardArray[i][j];
                    boardArray[i][j] = 0;
                }
            }
        }
    }
} // end Board::slideDown()

/*  Takes a vector of BoardSpace structs, which contain board spaces that
 *  have already slid and should not move again in a single turn.
 *  Takes a single space and compares it to the vector of spaces to see
 *  if the space can slide or not.
 *  Returns true if the space being checked can slide.
 *  Returns false if the space being checked has already slid. */
bool Board::canSpaceSlide(const BoardSpace& currentSpace, const vector<BoardSpace>& staticSpaces) const {
    BoardSpace staticSpace;

    for(unsigned int i = 0; i < staticSpaces.size(); i++) {
        staticSpace = staticSpaces[i];
        if(staticSpace.row == currentSpace.row && staticSpace.column == currentSpace.column) {
            return false;
        }
    }

    return true;
} // end Board::canSpaceSlide()