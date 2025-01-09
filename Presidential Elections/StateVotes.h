/*  Andrew Mikielski 11/06/2024
    StateVotes.h
    Holds number of votes for a user-specified candidate and total number of votes
    for a single State from a votes*.txt file. */
#ifndef STATE_VOTES_H
#define STATE_VOTES_H

#include <string>
using std::string;

class StateVotes {
    public:
        // Constructor
        StateVotes();

        // Setters of private variables
        void setState(string newState);
        void setCandidate(string newCandidate);
        void updateCandidateVotes(unsigned int newVotes); // Add to the number of candidate votes.
        void updateTotalVotes(unsigned int newVotes); // Add to the number of total votes.
        
        // Getters of private variables
        unsigned int getCandidateVotes() const;
        unsigned int getTotalVotes() const;
        string getState() const;
        string getCandidate() const;

        // Returns percentage of total votes the Candidate received in the State.
        double percentVotes() const;

    private:
        string state;
        string candidate;
        unsigned int numCandidateVotes;
        unsigned int numTotalVotes;
};

#endif // STATE_VOTES_H