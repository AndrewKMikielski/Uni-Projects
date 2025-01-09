/*  Andrew Mikielski 11/06/2024
    Candidate.h
    Holds State, Candidate name, Party, and number of votes
    for a single candidate from a votes*.txt file. */
#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include "Votes.h"
using std::string;

class Candidate {
    public:
        // Constructor
        Candidate();

        // Setters of private variables
        void setState(string newState);
        void setCandidate(string newCandidate);
        void setParty(string newParty);
        void setWithVotesObject(const Votes& VotesObject); // Uses a Votes object's data to set Candidate data
        void updateNumVotes(unsigned int newNumVotes); // Add to the number of votes.

        // overload less-than operator to allow sorting
        bool operator<(const Candidate& rhs) const { return getNumVotes() < rhs.getNumVotes();};

        // Getters of private variables
        string getState() const;
        string getCandidate() const;
        string getParty() const;
        int getNumVotes() const;

    private:
        string state;
        string candidate;
        string party;
        unsigned int numVotes;
};

#endif // CANDIDATE_H