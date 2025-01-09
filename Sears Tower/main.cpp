/*  Date: 9/5/2024
    Andrew Mikielski
    Project 1 - Sears Tower
    This program will construct a Sears Tower as outlined in the Project requirements.
    This program will also display the following ASCII art:
    .--------------.
    |\\//\\//\\//\\|
    |//\\//\\//\\//|
    |\\//\\//\\//\\|
    |//\\//\\//\\//|
    |\\//\\//\\//\\|
    |//\\//\\//\\//|
    |\\//\\//\\//\\|
    |//\\//\\//\\//|
    '--------------'
*/
#include <iostream>
#include <iomanip>

using namespace std;

// This function will draw the top section of the Sears Tower.
// This function takes towerSize as the input to produce ASCII output.
void drawTopSection(int towerSize)
{
    cout << endl;
    // Draws the roof over the Top Section.
    cout << setfill(' ') << setw(towerSize + 3) << "_" << setfill('_') << setw(towerSize - 1) << "_" << endl;

    // Draws the utility floor.
    cout << setfill(' ') << setw(towerSize + 2) << "|" << setfill('#') << setw(towerSize + 1) << "|" << endl;

    // This loop draws the rest of the floors except for the bottom-most floor of the Top Section.
    for(int i = 1; i < (towerSize - 1); i++) {
        cout << setfill(' ') << setw(towerSize + 2) << "|" << setw(towerSize + 1) << "|" << endl;
    }

    // Draws the roof and floor part of the bottom of the Top Section.
    cout << " " << setfill('_') << setw(towerSize + 1) << "|" << setfill(' ') << setw(towerSize + 1) << "|"  << endl;
}

// This function will draw the second section of the Sears Tower.
// This function takes towerSize as the input to produce ASCII output.
void drawSecondSection(int towerSize)
{
    // Draws the utility floor.
    cout << "|" << setfill('#') << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|" << endl;

    // This loop draws the rest of the floors of the Second/middle Section
    for(int i = 1; i < towerSize; i++) {
        cout << "|" << setfill(' ') << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|";

        // This if will be False on the final floor of the section.
        if(i != (towerSize - 1)) {
            cout << endl;
        }
    }

    // Draws the roof over the Ground Section.
    cout << setfill('_') << setw(towerSize) << "_" << endl;
}

// This function will draw the ground section of the Sears Tower.
// This function takes towerSize as the input to produce ASCII output.
void drawGroundSection(int towerSize)
{
    // Draws the utility floor.
    cout << "|" << setfill('#') << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|" << endl;

    // This loop draws the rest of the floors of the Ground Section.
    for(int i = 1; i < (towerSize * 2); i++) {
        cout << "|" << setfill(' ') << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|" << setw(towerSize + 1) << "|" << endl;
    }

    // Draws the ground underneath the building.
    cout << setfill('=') << setw((towerSize * 3) + 4) << "=" << endl;
}

// This function draws the Sears Towers by calling specialized drawing functions.
// This function takes towerSize as the input to pass into the specialized functions.
void drawTower(int towerSize)
{
    drawTopSection(towerSize);
    drawSecondSection(towerSize);
    drawGroundSection(towerSize);
}

// This function draws my own ASCII art. Example is included in the header of this file.
void drawOriginalGraphic()
{
    // Start with a fresh line for spacing and draw first line
    cout << endl << "." << setfill('-') << setw(15) << "." << endl;

    // Loop to draw the middle of the pattern
    for(int i = 1; i <= 8; i++) {
        cout << "|";

        // This if/else block determines which slash character to start with based on the row
        // The inner loops use different variables (j and k) for readability
        // These loops draw the primary contents of a single line
        if((i % 2) == 0) {
            for(int j = 1; j <= 7; j++) {

                // This if/else block alternates the slash characters
                if((j % 2) == 0) {
                    cout << setfill('\\') << setw(2) << "\\";
                }
                else {
                    cout << setfill('/') << setw(2) << "/";
                }
            }
        }
        else {
            for(int k = 1; k <= 7; k++) {

                // This if/else block alternates the slash characters
                if((k % 2) == 0) {
                    cout << setfill('/') << setw(2) << "/";
                }
                else {
                    cout << setfill('\\') << setw(2) << "\\";
                }
            }
        }
        cout << "|" << endl;
    }

    // Draw last line
    cout << "'" << setfill('-') << setw(15) << "'" << endl;
}

int main() {
    char menuChoice;
    int towerSize;

    // The menu output. Don't modify this, so that it outputs exactly as expected
    cout << "Program 1: Sears Tower" << endl;
    cout << "Which option would you like?" << endl;
    cout << "  1. Display original graphic" << endl;
    cout << "  2. Display Sears Tower" << endl;
    cout << "Your choice: ";

    // This will get valid input from the user.
    cin >> menuChoice;
    while(menuChoice != '1' && menuChoice != '2') {
        cout << "Please enter 1 or 2: ";
        cin >> menuChoice;
    }
    
    // If the user wants to see the Sears Tower this will prompt them for a non-negative, non-zero tower size.
    if(menuChoice == '2') {
        // The prompt for entering thesize, if the user chooses the tower
        cout << "What is the size of the Sears Tower? ";
        cin >> towerSize;

        while(towerSize <= 0){
            cout << "Please enter a positive number: ";
            cin >> towerSize;
        }

        // Function call to draw the Sears Tower with the user's input
        drawTower(towerSize);
    }
    else {
        // Draws my ASCII art.
        drawOriginalGraphic();
    }

    return 0;
}