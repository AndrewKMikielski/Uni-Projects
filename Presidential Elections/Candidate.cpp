/*  Andrew Mikielski 11/06/2024
    Candidate.cpp
    Holds State, Candidate name, Party, and number of votes
    for a single candidate from a votes*.txt file. */
#include <string>
#include "Candidate.h"
using namespace std;

//  Constructor
Candidate::Candidate() {
    state = "";
    candidate = "";
    party = "";
    numVotes = 0;
}

//  Setters
void Candidate::setState(string newState) {
    state = newState;
}

void Candidate::setCandidate(string newCandidate) {
    candidate = newCandidate;
}

void Candidate::setParty(string newParty) {
    party = newParty;
}

//  Uses a Votes object's data to set Candidate data
void Candidate::setWithVotesObject(const Votes& VotesObject) {
    state = VotesObject.getState();
    candidate = VotesObject.getCandidate();
    party = VotesObject.getParty();
    numVotes = VotesObject.getNumVotes();
}

//  Add to the number of votes.
void Candidate::updateNumVotes(unsigned int newNumVotes) {
    numVotes += newNumVotes;
}

//  Getters
string Candidate::getState() const {
    return state;
}

string Candidate::getCandidate() const {
    return candidate;
}

string Candidate::getParty() const {
    return party;
}

int Candidate::getNumVotes() const {
    return numVotes;
}