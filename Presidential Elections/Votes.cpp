/*  Andrew Mikielski 11/06/2024
    Votes.cpp
    Holds information from a single line of a votes*.txt file. */
#include <string>
#include "Votes.h"
using namespace std;

//  Constructor
Votes::Votes() {
    state = "";
    county = "";
    candidate = "";
    party = "";
    numVotes = 0;
}

//  Setters
void Votes::setState(string newState) {
    state = newState;
}

void Votes::setCounty(string newCounty) {
    county = newCounty;
}

void Votes::setCandidate(string newCandidate) {
    candidate = newCandidate;
}

void Votes::setParty(string newParty) {
    party = newParty;
}

void Votes::setNumVotes(unsigned int newNumVotes) {
    numVotes = newNumVotes;
}

//  Getters
string Votes::getState() const {
    return state;
}

string Votes::getCounty() const {
    return county;
}

string Votes::getCandidate() const {
    return candidate;
}

string Votes::getParty() const {
    return party;
}

int Votes::getNumVotes() const {
    return numVotes;
}