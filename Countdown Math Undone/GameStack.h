// Andrew Mikielski Project 6
// 12/01/2024
// GameStack.h
// Declares a class, GameStack, which is a Stack, a type of linked list that only
// allows adding, removal, and acquiring data from the top/beginning of the list.
// Requires the Game and GameNode classes.
// Creates and handles a list of GameNodes containing Game objects.

#ifndef GAME_STACK
#define GAME_STACK

#include "Game.h"
#include "GameNode.h"

class GameStack
{
private:
    GameNode* top;

public:
    // Constructor and destructor
    GameStack();
    ~GameStack();

    // Add/remove from the top of the list functions.
    void addGame(Game g);
    void removeGame();
    // Get the Game object from the top GameNode.
    Game getGame() const;
    // Returns true if the stack is empty, false otherwise.
    bool isEmpty() const;
};

#endif //GAME_STACK