// Andrew Mikielski Project 2 Countdown Math
// 9/30/2024
// This program will generate 6 random numbers for users to play a game with.
// The user gets to choose 0 to 4 "big numbers" (25, 50, 75, or 100) they receive and
// the rest of the numbers are "small numbers" (1-10). A target number is also randomly
// generated and the user is prompted to use math operations (+, -, *, /) with their
// generated numbers to try to reach the target number. The user cannot re-use numbers
// chosen in their calculations, however they will be able to use the calculated results
// in future calculations. If the user reaches the target number they win the game.
// The user will lose if they only have one number remaining.

#include <iostream>
#include "mersenne-twister.h"

using namespace std;

int chooseRandomNumber(int min, int max);

// This function generates all the random numbers in the game. Takes num1-6, Big Numbers, and the Target number as input.
// It changes the values of num1-6 and the Target number.
void generateNumbers(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int numBigNumbers, int& numTarget);

// This function asks for the number of Big Numbers from the user and initializes num1-6 and the Target number.
void initializeGame(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int& numTarget);

// This function prints all non-zero num1-6 variables and the Target number.
void printNumbers(int num1, int num2, int num3, int num4, int num5, int num6, int numTarget);

// This function will replace the first num1-6 variable that has the same value as inputNumber with a value of 0.
void replaceWithZero(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int inputNumber);

// This function updates the game's 6 numbers based on user input and calculations done upon the user input.
// The parameters are num1-6, user's input numbers, and a calculated new number.
void updateNumbers(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int inputNumOne, int inputNumTwo, int numNewNumber);

// This function adds two numbers and returns the result as an int.
int add(int inputNumOne, int inputNumTwo);

// This function subtracts two numbers and returns the result as an int.
int subtract(int inputNumOne, int inputNumTwo);

// This function multiplies two numbers and returns the result as an int.
int multiply(int inputNumOne, int inputNumTwo);

// This function divides two numbers and returns the result as an int.
int divide(int inputNumOne, int inputNumTwo);

// This function accepts the user's input to calculate a new number, which is returned as an int.
int calcNewNumber(int inputNumOne, int inputNumTwo, char operand);

// This function accepts num1-6 as parameters to ask the user for input, calculate and update the game variables.
// Returns False if the user wishes to quit the game. Returns True once input calculation and variable updating is complete.
bool gameLoop(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6);

// This function Returns true if the user won the game. Takes num1-6 and target number as parameters.
// A false value DOES NOT mean the user lost the game.
bool checkForWin(int num1, int num2, int num3, int num4, int num5, int num6, int numTarget);

// This function Returns true if the user lost. Takes num1-6 as parameters.
// A false value DOES NOT mean the user won the game.
bool checkForLoss(int num1, int num2, int num3, int num4, int num5, int num6);


int main() 
{
    int randSeed = 0;

    // Variables used to track values throughout the game
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    int num5 = 0;
    int num6 = 0;
    int numTarget = 0;
    bool isGameRunning = true;

    cout << "Enter random seed: ";
    cin >> randSeed;
    seed(randSeed);
    cout << endl;

    // Begins Countdown Math by initiliazing all starting number variables
    initializeGame(num1, num2, num3, num4, num5, num6, numTarget);

    // This loop will run until isGameRunning is set to false.
    do
    {
        // Display current game variable values to the user
        printNumbers(num1, num2, num3, num4, num5, num6, numTarget);

        // gameLoop handles user input, num calculation, and num updating.
        // Only returns False when the user enters '0' to quit
        isGameRunning = gameLoop(num1, num2, num3, num4, num5, num6);

        // This break statement only happens if the user enters '0' to quit, ending the program
        if(!isGameRunning) {
            break;
        }
        
        // Checks to see if the user won or lost the game
        if(checkForWin(num1, num2, num3, num4, num5, num6, numTarget)) {
            cout << "You win!" << endl;
            isGameRunning = false;
        } else if(checkForLoss(num1, num2, num3, num4, num5, num6)) {
            cout << "You lose." << endl;
            isGameRunning = false;
        }
    } while(isGameRunning);
    // Countdown Math game is over

    return 0;
} // end main()

int chooseRandomNumber(int min, int max) {
    return rand_u32() % (max + 1 - min) + min;
}

// This function generates all random numbers needed to begin playing the game.
// It takes 6 game numbers, the number of Big Numbers requested by the user, and the Target Number as input.
// The function "returns" the values of the 6 game numbers and Target Number as reference variables.
void generateNumbers(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int numBigNumbers, int& numTarget) {

    // This loop will generate random Big Numbers.
    // Number of Big Numbers range from 0 to 4.
    for(int i = 0; i < numBigNumbers; i++) {
        if(i == 0) {
            num1 = chooseRandomNumber(1, 4) * 25;
        }
        else if(i == 1) {
            num2 = chooseRandomNumber(1, 4) * 25;
        }
        else if(i == 2) {
            num3 = chooseRandomNumber(1, 4) * 25;
        }
        else if(i == 3) {
            num4 = chooseRandomNumber(1, 4) * 25;
        }
    }

    // This loop will generate random Small Numbers.
    // Number of Small Numbers range from 2 to 6.
    for(int i = numBigNumbers; i < 6; i++) {
        if(i == 0) {
            num1 = chooseRandomNumber(1, 10);
        }
        else if(i == 1) {
            num2 = chooseRandomNumber(1, 10);
        }
        else if(i == 2) {
            num3 = chooseRandomNumber(1, 10);
        }
        else if(i == 3) {
            num4 = chooseRandomNumber(1, 10);
        }
        else if(i == 4) {
            num5 = chooseRandomNumber(1, 10);
        }
        else if(i == 5) {
            num6 = chooseRandomNumber(1, 10);
        }
    }

    // Generate the Target Number
    numTarget = chooseRandomNumber(101, 999);
} // end generateNumbers()

// This function starts the game by accepting numbers 1-6 and Target Number as parameters.
// It asks the user for the number of Big Numers and calls generateNumbers to initialize the beginning of the game,
// prior to the game's main logic loop.
void initializeGame(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int& numTarget) {
    int numBigNumbers;

    cout << "Let's play Countdown!" << endl;
    cout << "How many big numbers would you like (0-4)? ";
    cin >> numBigNumbers;
    
    generateNumbers(num1, num2, num3, num4, num5, num6, numBigNumbers, numTarget);
} // end initializeGame()

// This function prints all non-zero num1-6 variables and the Target number. No numbers are modified.
void printNumbers(int num1, int num2, int num3, int num4, int num5, int num6, int numTarget) {
    cout << "Your numbers are: ";
    if(num1 != 0) {
        cout << num1 << " ";
    }
    if(num2 != 0) {
        cout << num2 << " ";
    }
    if(num3 != 0) {
        cout << num3 << " ";
    }
    if(num4 != 0) {
        cout << num4 << " ";
    }
    if(num5 != 0) {
        cout << num5 << " ";
    }
    if(num6 != 0) {
        cout << num6 << " ";
    }
    cout << endl << "The target is: " << numTarget << endl;
} // end printNumbers()

// This function will replace the first num1-6 variable that has the same value as inputNumber with a value of 0.
void replaceWithZero(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int inputNumber) {

    // Replace the first number that matches inputNumber with 0
    if(num1 == inputNumber) {
        num1 = 0;
    } else if(num2 == inputNumber) {
        num2 = 0;
    } else if(num3 == inputNumber) {
        num3 = 0;
    } else if(num4 == inputNumber) {
        num4 = 0;
    } else if(num5 == inputNumber) {
        num5 = 0;
    } else if(num6 == inputNumber) {
        num6 = 0;
    }
} // end replaceWithZero()

// This function updates the game's 6 numbers based on user input and calculations done upon the user input.
// The parameters are the game num1-6, user's input numbers, and a calculated new number.
// Variables num1-6 are reference variables.
// Numbers matching user input are replaced with a value of 0.
// The new calculated number then replaces the first value of 0 we see in order of 1 through 6.
void updateNumbers(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6, int inputNumOne, int inputNumTwo, int numNewNumber) {

    // Replace the first number that matches the user's first input with 0
    replaceWithZero(num1, num2, num3, num4, num5, num6, inputNumOne);

    // Replace the first number that matches the user's second input with 0
    replaceWithZero(num1, num2, num3, num4, num5, num6, inputNumTwo);

    // Replace the first 0 that appears with the new calculated number
    if(num1 == 0) {
        num1 = numNewNumber;
    } else if(num2 == 0) {
        num2 = numNewNumber;
    } else if(num3 == 0) {
        num3 = numNewNumber;
    } else if(num4 == 0) {
        num4 = numNewNumber;
    } else if(num5 == 0) {
        num5 = numNewNumber;
    } else if(num6 == 0) {
        num6 = numNewNumber;
    }
} // end updateNumbers()

// This function adds two numbers and returns the result as an int.
int add(int inputNumOne, int inputNumTwo) {
    return inputNumOne + inputNumTwo;
} // end add()

// This function subtracts two numbers and returns the result as an int.
int subtract(int inputNumOne, int inputNumTwo) {
    return inputNumOne - inputNumTwo;
} // end subtract()

// This function multiplies two numbers and returns the result as an int.
int multiply(int inputNumOne, int inputNumTwo) {
    return inputNumOne * inputNumTwo;
} // end multiply()

// This function divides two numbers and returns the result as an int.
int divide(int inputNumOne, int inputNumTwo) {
    return inputNumOne / inputNumTwo;
} // end divide()

// This function accepts the user's input to calculate a new number
// It returns the new number as an int.
int calcNewNumber(int inputNumOne, int inputNumTwo, char operand) {
    int numNewNumber = 0;

    if(operand == '+') {
        // call addition function
        numNewNumber = add(inputNumOne, inputNumTwo);
    } else if(operand == '-') {
        // call subtraction function
        numNewNumber = subtract(inputNumOne, inputNumTwo);
    } else if(operand == '*') {
        // call multiplication function
        numNewNumber = multiply(inputNumOne, inputNumTwo);
    } else if(operand == '/') {
        // call division function
        numNewNumber = divide(inputNumOne, inputNumTwo);
    }

    return numNewNumber;
} // end calcNewNumber()

// This function accepts the 6 game numbers as reference parameters.
// It requests user input to calculate a new number and update the 6 game numbers appropriately.
// Returns False if the user wishes to quit the game.
// Returns True once input calculation is complete.
bool gameLoop(int& num1, int& num2, int& num3, int& num4, int& num5, int& num6) {
    int inputNumOne;
    int inputNumTwo;
    int numNewNumber;
    char operand;

    cout << "Enter a calculation (or 0 to quit): ";
    cin >> inputNumOne;

    // This statement will quit the game.
    if(inputNumOne == 0) {
        return false;
    }
    // Continue accepting input if the user is not quitting the game.
    cin >> operand;
    cin >> inputNumTwo;

    // Display the users input
    cout << inputNumOne << " "
         << operand << " "
         << inputNumTwo << " = ";
    
    // Calculates the user input
    numNewNumber = calcNewNumber(inputNumOne, inputNumTwo, operand);

    // Displays the calculated result of the user input
    cout << numNewNumber << endl << endl;

    // Updates all of our numbers based on user input and the new calculated number
    updateNumbers(num1, num2, num3, num4, num5, num6, inputNumOne, inputNumTwo, numNewNumber);

    return true;
} // end gameLoop()

// This function checks if the user won the game.
// A win condition is when any game number matches the target number.
// Returns true if the user won.
// Returns false if the user didn't win.
// A false value DOES NOT mean the user lost the game.
bool checkForWin(int num1, int num2, int num3, int num4, int num5, int num6, int numTarget) {
    if((num1 == numTarget) || (num2 == numTarget) || (num3 == numTarget) ||
       (num4 == numTarget) || (num5 == numTarget) || (num6 == numTarget)) {
        return true;
    }

    return false;
} // end checkForWin()

// This function checks if the user lost the game.
// A loss condition is when there is none or one non-zero number remaining.
// Returns true if the user lost.
// Returns false if the user didn't lose.
// A false value DOES NOT mean the user won the game.
bool checkForLoss(int num1, int num2, int num3, int num4, int num5, int num6) {
    int numZeroes = 0;

    // Counts how many game numbers are 0
    if(num1 == 0) {
        numZeroes++;
    } if(num2 == 0) {
        numZeroes++;
    } if(num3 == 0) {
        numZeroes++;
    } if(num4 == 0) {
        numZeroes++;
    } if(num5 == 0) {
        numZeroes++;
    } if(num6 == 0) {
        numZeroes++;
    }

    // If there are 5 or more zeroes the user ran out of numbers and lost.
    if(numZeroes >= 5) {
        return true;
    }

    return false;
} // end checkForLoss()