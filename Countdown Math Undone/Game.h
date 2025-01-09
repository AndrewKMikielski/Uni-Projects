// Andrew Mikielski Project 6
// 12/01/2024
// Game.h
// Modified by Andrew Mikielski to include vector and string libraries, a default constructor,
// assignment constructor, == operator overload, solve() function, tryCalculation() function, and displaySolution() function.

#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

// Game class keeps track of the state of a single game
class Game
{
public:
	// Quantity of numbers that are part of the game
	static const int NUMBERS_COUNT = 6;

private:
	// Array of numbers (0 if a spot is empty)
	int numbers[NUMBERS_COUNT];

	// Target (goal the user is going for)
	int target;

	// solve() uses this function to recursively iterate through the array with all operations (+,-,*,/) to attempt to find a solution.
	// Takes a Game object and a vector of strings as parameters.
	bool tryCalculation(Game g, vector<string>& solution);
	// Takes a vector of strings and outputs everything in the vector.
	void displaySolution(const vector<string> solution) const;

public:
	// Default constructor added by Andrew Mikielski
	Game();
	Game(int numLarge);
	// Assignment constructor added by Andrew Mikielski
	Game(const Game& origGame);
	// Overloaded operator== added by Andrew Mikielski
	bool operator==(const Game& rhs) const;

	void displayNumbers();
	void addNumber(int num);
	bool wonGame();
	bool lostGame();
	bool gameOver();
	bool removeNumber(int userNumber);
	int performOperation(int num1, char operation, int num2);

	// Tries to look for a solution to the current game with a copy of the game to perform calculations on.
	void solve(Game g);
};

