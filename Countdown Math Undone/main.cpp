// Andrew Mikielski Project 6
// 12/01/2024
// main.cpp
// The goal of this project is to modify a provided solution of Project 2 with an Undo functionality and a Solve functionality.
// Undo is accomplished with a self-written linked list and a function in main.cpp.
// Solve is accomplished within Game.cpp.

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "mersenne-twister.h"
#include "Game.h"
#include "GameStack.h"

using namespace std;

int promptAndGetNumLarge();
void processCalculation(string userInput, int& num1, char& operation, int& num2);

// Will undo the last action, if possible.
// Takes a Game object and GameStack (linked list) object as parameters.
// Added by Andrew Mikielski
void undo(Game& game, GameStack& stack);

int main() {

	// Input a random seed for the program, and call the seed function
	int randSeed;
	cout << "Enter random seed: ";
	cin >> randSeed;
	seed(randSeed);

	// userContinue is used to input whether the user wants to continue to play another game
	string userContinue;
	do {
		// Stack for Undo functionality.
		GameStack undoStack;

		// Get the quantity of large numbers
		int numLarge = promptAndGetNumLarge();

		// Create the game variable, using that quantity of large numbers
		Game game(numLarge);

		// Save the start of the game in the undo stack.
		undoStack.addGame(game);

		// Clear newline from previous input
		string userInput;
		getline(cin, userInput);

		// Repeat until the game is over
		while (!game.gameOver()) {
			// Display the available numbers and get the user's calculation input
			game.displayNumbers();
			cout << "Enter a calculation (or U to Undo, S to Solve, or Q to Quit): ";
			getline(cin, userInput);

			// Quit this game if the user choses Q, but don't exit the program (the user might play another game)
			if (userInput == "q" || userInput == "Q") {
				cout << "Exiting this game." << endl;
				break;
			}

			// Undo the last move.
			// Added by Andrew Mikielski
			if(userInput == "u" || userInput == "U") {
				undo(game, undoStack);
				// Continue at the start of the game loop to ask for new input.
				continue;
			}

			// Output the sequence to solve the current game, if possible.
			// Added by Andrew Mikielski
			if(userInput == "s" || userInput == "S") {
				game.solve(game);
				// Continue at the start of the game loop to ask for new input.
				continue;
			}

			// Get the numbers and operation from the user's input
			int num1;
			char operation;
			int num2;
			processCalculation(userInput, num1, operation, num2);

			// Make sure num1 and num2 are in the list of numbers
			if (!game.removeNumber(num1)) {
				// num1 was not found, display error message
				cout << num1 << " is not a valid number." << endl;
			}
			else if (!game.removeNumber(num2)) {
				// num2 was not found, display error message
				cout << num2 << " is not a valid number." << endl;
				// add num1 back into the list, since it was removed in the previous if condition
				game.addNumber(num1);
			}
			else {
				// num1 and num2 are in our list, perform the operation and display the equation
				int result = game.performOperation(num1, operation, num2);
				cout << num1 << " " << operation << " " << num2 << " = " << result << endl << endl;

				// Add the result to the list of numbers
				game.addNumber(result);

				// Save this instance of the game in the undo stack.
				undoStack.addGame(game);

				// Display win or lose messages if appropriate
				if (game.wonGame()) {
					cout << "You win!" << endl;
				} else if (game.lostGame()) {
					cout << "You lose." << endl;
				}
			}
		}

		// Ask user if they want to continue, do so if they type Y or y
		cout << endl;
		cout << "Would you like to play again (y/n)? ";
		getline(cin, userContinue);
	} while (userContinue == "y" || userContinue == "Y");
}

// Display the greeting and the prompt for choosing big numbers
// Repeats until a valid big number is entered (must be 0-4)
// Returns a valid number of big numbers chosen by the user (0-4)
int promptAndGetNumLarge() {
	int numLarge = 0;

	// Display prompt and get the input
	cout << endl;
	cout << "Let's play Countdown!" << endl;
	cout << "How many big numbers would you like (0-4)? ";
	cin >> numLarge;

	// Repeat if the input isn't valid (valid is between 0 and 4, inclusive)
	while (numLarge < 0 || numLarge > 4) {
		cout << "That's not a valid number. You must choose between 0 and 4." << endl;
		cout << "How many large numbers would you like? ";
		cin >> numLarge;
	}

	// Return the number chosen
	return numLarge;
}

// Determines the pieces of a calculation from the user input
// Parameters:
// userInput is the string, for example "2+3"
// num1 is passed by reference to return the first number in the calculation (the 2 in the above example)
// operation is passed by reference to return the operation in the calculation ('+' in the above example)
// num2 is passed by reference to return the second number in the calculation (the 3 in the above example)
// Function doesn't return a value, it uses the reference variables to return the information
// Will cause an exception if userInput is anything but a valid operation
void processCalculation(string userInput, int& num1, char& operation, int& num2) {
	// Use a stringstream (essentially turning the given string into a stream)
	stringstream ss(userInput);

	// Input the first number, then the operation, and then the second number from that stream
	ss >> num1 >> operation >> num2;
}

// Will undo the last action, if possible.
// Takes a Game object and GameStack (linked list) object as parameters.
// The current state of the game exists on top of the stack.
// Removes the top of the stack and if the stack is empty we are at the beginning of the game and cannot undo.
// Added by Andrew Mikielski
void undo(Game& game, GameStack& undoStack) {
	undoStack.removeGame();
	if(undoStack.isEmpty()) {
		cout << "Cannot undo." << endl;
		// Puts the current state of the game back into the undo stack so we can undo to it later, if needed.
		undoStack.addGame(game);
	} else {
		game = undoStack.getGame();
	}
} // end undo()