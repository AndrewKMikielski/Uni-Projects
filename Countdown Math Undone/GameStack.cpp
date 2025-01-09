// Andrew Mikielski Project 6
// 12/01/2024
// GameStack.h
// Defines the class, GameStack, which is a Stack, a type of linked list
// that only allows adding and removal from the top/beginning of the list.
// Requires the Game and GameNode classes.
// Creates and handles a list of GameNodes containing Game objects.

#include "GameStack.h"

// Default constructor
GameStack::GameStack() {
    top = nullptr;
}

// Destructor empties the stack via removeGame()
GameStack::~GameStack() {
    while(top) {
        removeGame();
    }
}

// Adds a new GameNode with a Game object as its data to the top of the stack.
void GameStack::addGame(Game g) {
    GameNode* newNode = new GameNode(g, top);
    top = newNode;
    return;
}

// Removes a GameNode from the top of the stack.
void GameStack::removeGame() {
    GameNode* temp = top;
    top = top->getNext();
    delete temp;
}

// Returns Game object stored at the top of the stack.
Game GameStack::getGame() const {
    return top->getData();
}

// Returns true if the stack is empty, false otherwise.
bool GameStack::isEmpty() const {
    return (top == nullptr);
}