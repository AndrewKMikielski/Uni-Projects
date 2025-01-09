// Andrew Mikielski Project 6
// 12/01/2024
// Game.cpp
// Modified by Andrew Mikielski to include vector, string and stringstream libraries, a default constructor,
// assignment constructor, == operator overload, solve() function, tryCalculation() function, and displaySolution() function.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Game.h"
#include "mersenne-twister.h"

using namespace std;

// Default constructor added by Andrew Mikielski
// Sets all values to 0, just to assign them something
// to allow Game to be used by GameNode.
Game::Game() {
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		numbers[i] = 0;
	}
	target = 0;
}

// Constructor to initialize the game state
// Chooses random numbers and the target (goal)
// Parameter numLarge is the number (0-4) of large numbers
// Remaining of random numbers will be small
Game::Game(int numLarge) {
	// Sets the random numbers
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (i < numLarge) {
			numbers[i] = chooseRandomNumber(1, 4) * 25;
		}
		else {
			numbers[i] = chooseRandomNumber(1, 10);
		}
	}

	// Sets the target
	target = chooseRandomNumber(101, 999);
}

// Overloaded assignment constructor added by Andrew Mikielski
// Copies every value in the Game object passed through the parameter to this Game object.
Game::Game(const Game& g) {
	for(int i = 0; i < NUMBERS_COUNT; i++) {
		this->numbers[i] = g.numbers[i];
	}
	this->target = g.target;
}

// Overloaded == comparison operator added by Andrew Mikielski
// Only returns true if every variable in this Game and rhs are equal to each other.
bool Game::operator==(const Game& rhs) const {
	for(int i = 0; i < NUMBERS_COUNT; i++) {
		if(numbers[i] != rhs.numbers[i]) {
			return false;
		}
	}
	if(target != rhs.target) {
		return false;
	}
	return true;
}

// Display numbers left for the users to choose and the target
void Game::displayNumbers() {
	cout << "Your numbers are: ";

	// Display all numbers remaining (skip 0s which indicate an open spot)
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] != 0) {
			cout << numbers[i] << " ";
		}
	}
	cout << endl;

	cout << "The target is: " << target << endl;
}

// Add a number to the numbers available for the user to choose
// Parameter addNum is the number to add
void Game::addNumber(int addNum) {
	// Go through the available spots and put the new number at the first 0 (empty spot)
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] == 0) {
			numbers[i] = addNum;
			return;
		}
	}

	cout << "Error: no space for added number!" << endl;
}

// Determine if the user has lost the game
// Returns true if the user has lost, falst if they have not (they've won or game is still going)
bool Game::lostGame() {
	// Winning takes priority--not a loss if the game has been won
	if (wonGame()) {
		return false;
	}

	// Look through each number, count the numbers that remain (aren't 0)
	int countNumbersRemain = 0;
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] != 0) {
			countNumbersRemain++;
		}
	}

	// If there is 1 or fewer number left, the user has lost
	return (countNumbersRemain <= 1);
}

// Removes the given number from the list of numbers to work with
// userNumber is the number to remove
// Returns true if the userNumber was found (and removed)
// Returns false if userNumber is not in the list
bool Game::removeNumber(int userNumber) {
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] == userNumber) {
			numbers[i] = 0;
			// Return true, number was false
			return true;
		}
	}

	// Number wasn't found, return false
	return false;
}

// Calculates the answer of the specified operation
// operation is a character, either '+', '-', '*', or '/' to specify the type of calculation
// num1 and num2 are the two numbers (where order matters, num1 comes first, e.g. num1 - num2)
// Returns the result of the calculation
int Game::performOperation(int num1, char operation, int num2) {
	// Perform the calculation depending on the operation chosen
	// (Note: breaks not needed since return statement leaves the function)
	switch (operation) {
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '/':
		return num1 / num2;
	case '*':
		return num1 * num2;
	}

	// Error: invalid operation, return 0
	return 0;
}

// Determines if the user has won the game
// Returns true if user has won, false if they have lost or game still going
bool Game::wonGame() {
	// Look through available numbers
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		// If target is found, return true
		if (numbers[i] == target) {
			return true;
		}
	}

	// Target not found
	return false;
}

// Determines if the game is over
// Returns true if game is over (user has either won or lost)
// Returns false if game still going
bool Game::gameOver() {
	return wonGame() || lostGame();
}

// Tries to look for a solution to the current game with a copy of the game to perform calculations on.
void Game::solve(Game g) {
	// Vector to store the calculations that lead to a solution.
	vector<string> solution;
	
	// Build list of solutions.
	tryCalculation(g, solution);

	// Output Solutions, if any
	displaySolution(solution);
} // end Game::solve()

// solve() uses this function to recursively iterate through the array with operations (+,-,*,/) to find a solution.
// Recursive function that attempts to find a solution to the copy of the game sent in as a parameter.
// Takes a vector of strings to provide the steps to the solution, if a solution is found.
bool Game::tryCalculation(Game g, vector<string>& solution) {
	// If the game copy has a winning solution then return true.
	if(g.wonGame()) {
		return true;
	}

	// Loop through array to perform calculations with all combinations of numbers and operations.
	// Outer loop controls num1, second loop controls num2, innermost loop controls operand.
	for(int i = 0; i < NUMBERS_COUNT; i++) {
		int num1 = g.numbers[i];

		if(num1 == 0) {
			// Do nothing this iteration.
			continue;
		}

		for(int j = 0; j < NUMBERS_COUNT; j++) {
			int num2 = g.numbers[j];
			
			if(num2 == 0) {
				// Do nothing this iteration.
				continue;
			}
			if(i == j) {
				// Do nothing this iteration, this is the same number.
				continue;
			}
			// Loop through trying with different operators.
			// Operation attempts will be calculated in the order of: addition, subtraction, multiplication, then division.
			const string operators = "+-*/";
			for(unsigned int k = 0; k < operators.size(); k++) {
				// Calculate the result of num1 and num2 with an operator (+,-,*,/) controlled by iterator k.
				int result = g.performOperation(num1, operators[k], num2);

				// Create stringstream to build and store calculation output into resultString.
				stringstream ss;
				string resultString;
				ss << num1 << " " << operators[k] << " " << num2 << " = " << result;
				getline(ss, resultString);
				
				// Make another copy of the game to apply the calculation to. This is to preserve the state of the array the three loops are working with.
				Game gCopy(g);
				//gCopy.removeNumber(num1);
				gCopy.numbers[i] = 0;
				gCopy.numbers[j] = 0;
				//gCopy.removeNumber(num2);
				gCopy.addNumber(result);

				// Try the next calculation. If this evaluates to true it means the calcuation we just did was part of the solution.
				if(tryCalculation(gCopy, solution)) {
					solution.push_back(resultString);
					return true;
				}
				
			} // end of innermost loop
		} // end of second loop
	} // end of outer loop

	return false;
} // end Game::tryCalculation()

// Takes a vector of strings and outputs everything in the vector.
// Outputs the sequence of calculations needed to solve the game if it can be solved.
// Outputs it cannot find a solution if the vector is empty.
void Game::displaySolution(const vector<string> solution) const {
	if(!solution.empty()) {
		cout << "Solution:" << endl;
		for(int i = solution.size() - 1; i >= 0; i--) {
			cout << solution[i] << endl;
		}
	} else {
		cout << "Unable to find a solution." << endl;
	}
} // end Game::displaySolution()