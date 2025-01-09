// Andrew Mikielski Project 6
// 12/01/2024
// GameNode.cpp
// Stores a single instance of Game class objects in memory.
// To be used with a linked list class, such as GameStack.h
// Defines functionality of a single Node of Game data.

#include "GameNode.h"

// Default Constructor
GameNode::GameNode() {
    this->next = nullptr;
}

// Constructor that takes a Game object and a GameNode* pointer object as parameters.
GameNode::GameNode(Game theData, GameNode* nextNode) {
    this->data = theData;
    this->next = nextNode;
}

// Returns the next GameNode pointer being pointed at.
GameNode* GameNode::getNext() const {
    return next;
}

// Returns the Game object stored in the Node.
Game GameNode::getData() const {
    return data;
}

// Saves a Game object into the Node.
void GameNode::setData(Game theData) {
    this->data = theData;
}

// Changes next to point to the GameNode pointer object passed in as a parameter.
void GameNode::setNext(GameNode* nextNode) {
    this->next = nextNode;
}