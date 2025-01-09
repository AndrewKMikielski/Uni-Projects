/*  Andrew Mikielski Project 3: Countdown Letters
    10/16/2024
    Two players are given a randomly generated string of 9 letters.
    The players choose between 3 to 5 letters to be vowels.
    The players then try to create a word from the list of letters.
    The player with the longest valid word, checked with a dictionary, is the winner.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "mersenne-twister.h"

using namespace std;

int chooseRandomNumber(int min, int max);
string fullSetOfVowels();
string fullSetOfConsonants();

/*  Takes the dictionary of words from a file and puts them into a vector for efficiency.
    Returns a vector of strings. */
vector<string> buildDictionary();

//  Returns a number between 3 and 5, inclusive, from user input.
int getNumVowels();

//  Returns a string converted to all upper case
string strToUpper(string strInput);

//  Returns a string of 9 random letters. Takes number of vowels as input.
string generateLetters(int numVowels);

/*  Initializes a new game with fresh letters.
    Creates and returns a string of letters for the players to play the game with. */
string initializeNewGame();

/*  Checks if a word's letters can be made from the string of random letters.
    Accepts the word and random letters as string parameters.
    Returns true if the word can be made. */
bool isWordInLetters(const string& word, string letters);

/*  Checks if a word is in the dictionary.
    Accepts the dictionary and word as parameters.
    Returns true if the word is in the dictionary. */
bool isWordInDictionary(const vector<string>& dictionary, const string& word);

/*  Checks if a player's word is valid against the random letters and dictionary.
    Returns true if the word is valid.
    Returns false if the word is not valid.
    Takes the dictionary, randomly generated letters, and a player's input as parameters. */
bool isWordValid(const vector<string>& dictionary, const string& letters, const string& strInput);

/*  Takes the dictionary of words as a vector and randomly generated letters as input and plays the game. */
void playGame(const vector<string>& dictionary, const string& letters);

/*  Returns true if both players tied each other.
    Returns false if it is not a tie.
    Takes both player's input strings and both player's boolean validity as parameters */
bool checkForTie(const string& strPlayer1, const string& strPlayer2, bool isPlayer1Valid, bool isPlayer2Valid);

/*  Checks for a winner between Player 1 and Player 2 and outputs the result.
    Takes both player's input strings and both player's boolean validity as parameters. */
void determineWinner(const string& strPlayer1, const string& strPlayer2, bool isPlayer1Valid, bool isPlayer2Valid);

/*  Finds and returns the longest possible word.
    Takes the vector dictionary and string of generated letters as input. */
string longestWord(const vector<string>& dictionary, const string& letters);


int main() 
{
    int randSeed = 0;
    string letters;
    vector<string> dictionary;
    char playAgain;

    // Read dictionary into memory from a file
    dictionary = buildDictionary();

	cout << "Enter random seed: ";
    cin >> randSeed;
    seed(randSeed);
    
    // Begin playing Countdown Letters
    cout << "Let's play Countdown!" << endl;
    do {
        // Get new letters for each game
        letters = initializeNewGame();
        cout << "The letters are: " << letters << endl;

        playGame(dictionary, letters);

        cout << endl << "Do you want to play again (y/n)? ";
        cin >> playAgain;
        playAgain = toupper(playAgain);
    } while(playAgain == 'Y');
    // End playing Countdown Letters
    
    return 0;
} // end main()

int chooseRandomNumber(int min, int max) {
	return rand_u32() % (max + 1 - min) + min;
}

string fullSetOfVowels() {
	return 
		string(15, 'A') + 
		string(21, 'E') + 
		string(13, 'I') + 
		string(13, 'O') + 
		string(5, 'U');
}

string fullSetOfConsonants() {
	return
		string(2, 'B') +
		string(3, 'C') +
		string(6, 'D') +
		string(2, 'F') +
		string(3, 'G') +
		string(2, 'H') +
		string(1, 'J') +
		string(1, 'K') +
		string(5, 'L') +
		string(4, 'M') +
		string(8, 'N') +
		string(4, 'P') +
		string(1, 'Q') +
		string(9, 'R') +
		string(9, 'S') +
		string(9, 'T') +
		string(1, 'V') +
		string(1, 'W') +
		string(1, 'X') +
		string(1, 'Y') +
		string(1, 'Z');
}


/*  Takes the dictionary of words from a file and puts them into a vector for efficiency.
    Returns a vector of strings. */
vector<string> buildDictionary() {
    ifstream fileIn;
    string fileInput;
    vector<string> dictionary;

    fileIn.open("words.txt");

    //  Loops through the file to add each word to the vector dictionary
    while(!fileIn.eof()) {
        fileIn >> fileInput;
        dictionary.push_back(fileInput);
    }

    fileIn.close();
    return dictionary;
} // end buildDictionary()

/*  Asks the user for the number of vowels for the game.
    Returns a number from the user between 3 and 5, inclusive.
    Asks the user for input again if the number isn't 3-5. */
int getNumVowels() {
    const int MINIMUM_NUMBER = 3;
    const int MAXIMUM_NUMBER = 5;
    int numInput;

    cout << "How many vowels would you like (" << MINIMUM_NUMBER << "-" << MAXIMUM_NUMBER << ")? ";
    cin >> numInput;
    while((numInput < MINIMUM_NUMBER) || (numInput > MAXIMUM_NUMBER)) {
        cout << "Invalid number of vowels." << endl;
        cout << "How many vowels would you like (" << MINIMUM_NUMBER << "-" << MAXIMUM_NUMBER << ")? ";
        cin >> numInput;
    }

    return numInput;
} // end getNumVowels()

//  Returns a string converted to all upper case
string strToUpper(string strInput) {
    for(unsigned int i = 0; i < strInput.size(); i++) {
        strInput.at(i) = toupper(strInput.at(i));
    }

    return strInput;
} // end strToUpper()

//  Returns a string of 9 random letters. Takes number of vowels as input to generate vowels first.
string generateLetters(int numVowels) {
    const int TOTAL_LETTERS = 9;
    string gameLetters = "";
    string vowels = fullSetOfVowels();
    string consonants = fullSetOfConsonants();
    int randIndex;

    //  Generate vowels first
    for(int i = 0; i < numVowels; i++) {
        randIndex = chooseRandomNumber(0, vowels.size() - 1);
        gameLetters += vowels.at(randIndex);
        vowels.replace(randIndex, 1, "");
    }
    
    //  Fill the rest with random consonants
    for(int i = numVowels; i < TOTAL_LETTERS; i++) {
        randIndex = chooseRandomNumber(0, consonants.size() - 1);
        gameLetters += consonants.at(randIndex);
        consonants.replace(randIndex, 1, "");
    }
    
    return gameLetters;
} // end generateLetters()

/*  Initializes a new game with fresh letters.
    Creates and returns a string of letters for the players to play the game with. */
string initializeNewGame() {
    //  Get user input for number of vowels.
    int numVowels = getNumVowels();

    //  Generate and return string of random letters.
    return generateLetters(numVowels);
} // end initializeNewGame()

/*  Checks if a word's letters can be made from the string of random letters.
    Accepts the word and random letters as string parameters.
    Returns true if the word can be made. */
bool isWordInLetters(const string& word, string letters) {
    size_t findIndex;

    /*  Check to see if word's characters are contained within letter's characters. */
    for(unsigned int i = 0; i < word.size(); i++) {
        findIndex = letters.find(word.at(i));
        if(findIndex == string::npos) {
            return false;
        }
        else {
            letters.replace(findIndex, 1, "");
        }
    }

    // If the end of the loop is reached then the word can be made from the random letters.
    return true;
} // end isWordInLetters()

/*  Checks if a word is in the dictionary.
    Accepts the dictionary and word as parameters.
    Returns true if the word is in the dictionary. */
bool isWordInDictionary(const vector<string>& dictionary, const string& word) {
    for(unsigned int i = 0; i < dictionary.size(); i++) {
        if(dictionary.at(i) == word) {
            return true;
        }
    }

    // If the loop above doesn't return true then the word is not in the dictionary.
    return false;
} // end isWordInDictionary()

/*  Checks if a player's word is valid against the random letters and dictionary.
    Returns true if the word is valid.
    Returns false if the word is not valid.
    Takes the dictionary, randomly generated letters, and a player's input as parameters. */
bool isWordValid(const vector<string>& dictionary, const string& letters, const string& strInput) {
    //  If input exceeds amount of random letters it cannot be valid.
    if(strInput.size() > letters.size()) {
        return false;
    }

    /*  If input is within the letters we then check if
        the input is in the dictionary, returning true or false. */
    if(isWordInLetters(strInput, letters)) {
        return isWordInDictionary(dictionary, strInput);
    }

    //  If this function reaches this point then it means the input was invalid.
    return false;
} // end isWordValid()

/*  Takes the dictionary of words as a vector and randomly generated letters as input and plays the game. */
void playGame(const vector<string>& dictionary, const string& letters) {
    string strPlayer1;
    string strPlayer2;
    bool isPlayer1Valid;
    bool isPlayer2Valid;

    //  Gather player input
    cout << "Player 1, enter your word: ";
    cin >> strPlayer1;
    cout << "Player 2, enter your word: ";
    cin >> strPlayer2;

    //  Convert all input to uppercase for use in comparisons
    strPlayer1 = strToUpper(strPlayer1);
    strPlayer2 = strToUpper(strPlayer2);

    //  Check if each player's word is valid
    isPlayer1Valid = isWordValid(dictionary, letters, strPlayer1);
    if(!isPlayer1Valid) {
        cout << "Player 1's word is not valid." << endl;
    }
    isPlayer2Valid = isWordValid(dictionary, letters, strPlayer2);
    if(!isPlayer2Valid) {
        cout << "Player 2's word is not valid." << endl;
    }

    // Check to see if this is a tie game.
    if(checkForTie(strPlayer1, strPlayer2, isPlayer1Valid, isPlayer2Valid)) {
        cout << "Tie game." << endl;
    }
    else {
        // If the game isn't a tie we have to check who the winner is.
        determineWinner(strPlayer1, strPlayer2, isPlayer1Valid, isPlayer2Valid);
    }

    // Display the longest possible word
    cout << "The longest possible word is: " << longestWord(dictionary, letters) << endl;
} // end playGame()

/*  Returns true if both players tied each other.
    Returns false if it is not a tie.
    It is a tie when neither word is valid, or they're both valid and the same length.
    Takes both player's input strings and both player's boolean validity as parameters */
bool checkForTie(const string& strPlayer1, const string& strPlayer2, bool isPlayer1Valid, bool isPlayer2Valid) {
    // If both words are not valid it is a tie.
    if(!isPlayer1Valid && !isPlayer2Valid) {
        return true;
    }
    
    // If both words are valid and the same length it is a tie.
    if(isPlayer1Valid && isPlayer2Valid) {
        if(strPlayer1.size() == strPlayer2.size()) {
            return true;
        }
    }

    // If neither of the above are true then the game is not a tie.
    return false;
} // end checkForTie()

/*  Checks for a winner between Player 1 and Player 2 and outputs the result.
    If only one player's word is valid, that player wins.
    If both words are valid the longer word wins.
    Takes both player's input strings and both player's boolean validity as parameters. */
void determineWinner(const string& strPlayer1, const string& strPlayer2, bool isPlayer1Valid, bool isPlayer2Valid) {
    // When both words are valid the longer word wins.
    if(isPlayer1Valid && isPlayer2Valid) {
        if(strPlayer1.size() > strPlayer2.size()) {
            cout << "Player 1 wins!" << endl;
        }
        else {
            cout << "Player 2 wins!" << endl;
        }
        // Exit the function if a winner is found above.
        return;
    }

    // If one player's word is not valid then the other player won
    if(isPlayer1Valid) {
        cout << "Player 1 wins!" << endl;
    }
    else if(isPlayer2Valid) {
        cout << "Player 2 wins!" << endl;
    }
} // end determineWinner()

/*  Finds and returns the longest possible word.
    Takes the vector dictionary and string of generated letters as input. */
string longestWord(const vector<string>& dictionary, const string& letters) {
    string word = "";

    /*  Checks to see if a word in the dictionary is valid within the set of letters.
        The goal is to find the first longest word. */
    for(unsigned int i = 0; i < dictionary.size(); i++) {
        if(isWordInLetters(dictionary.at(i), letters)) {
            /*  Words of equal length to the current value of word will not
                overwrite word, preserving the first longest found.*/
            if(dictionary.at(i).size() > word.size()) {
                word = dictionary.at(i);
            }
        }
    }

    return word;
} // end longestWord()