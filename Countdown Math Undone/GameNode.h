// Andrew Mikielski Project 6
// 12/01/2024
// GameNode.h
// Stores a single instance of Game class objects in memory.
// To be used with a linked list class, such as GameStack.h
// Declares functionality of a single Node of Game data.

#ifndef GAME_NODE
#define GAME_NODE

#include "Game.h"

class GameNode
{
private:
    // Data held in the node.
    Game data;
    GameNode* next;

public:
    // Constructors
    GameNode();
    GameNode(Game theData, GameNode* nextNode);
    // Get functions
    GameNode* getNext() const;
    Game getData() const;
    // Set functions
    void setData(Game theData);
    void setNext(GameNode* nextNode);
};

#endif //GAME_NODE