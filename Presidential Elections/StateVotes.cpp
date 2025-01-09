/*  Andrew Mikielski 11/06/2024
    StateVotes.cpp
    Holds number of votes for a specified candidate and total number of votes
    for a single State from a votes*.txt file. */
#include <string>
#include "StateVotes.h"
using namespace std;

//  Constructor
StateVotes::StateVotes() {
    state = "";
    candidate = "";
    numCandidateVotes = 0;
    numTotalVotes = 0;
}

//  Setters
void StateVotes::setState(string newState) {
    state = newState;
}

void StateVotes::setCandidate(string newCandidate) {
    candidate = newCandidate;
}

//  Add to the number of candidate votes.
void StateVotes::updateCandidateVotes(unsigned int newVotes) {
    numCandidateVotes += newVotes;
}

//  Add to the number of total votes.
void StateVotes::updateTotalVotes(unsigned int newVotes) {
    numTotalVotes += newVotes;
}

//  Getters
unsigned int StateVotes::getCandidateVotes() const {
    return numCandidateVotes;
}

unsigned int StateVotes::getTotalVotes() const {
    return numTotalVotes;
}

string StateVotes::getState() const {
    return state;
}

string StateVotes::getCandidate() const {
    return candidate;
}

//  Returns percentage of total votes the Candidate received in the State.
double StateVotes::percentVotes() const {
    return (1.0 * numCandidateVotes / numTotalVotes) * 100;
}