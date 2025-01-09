/*  Andrew Mikielski 11/06/2024
    Votes.h
    Holds information from a single line of a votes*.txt file. */
#ifndef VOTES_H
#define VOTES_H

#include <string>
using std::string;

class Votes {
    public:
        // Constructor
        Votes();

        // Setters of private variables
        void setState(string newState);
        void setCounty(string newCounty);
        void setCandidate(string newCandidate);
        void setParty(string newParty);
        void setNumVotes(unsigned int newNumVotes);

        // Getters of private variables
        string getState() const;
        string getCounty() const;
        string getCandidate() const;
        string getParty() const;
        int getNumVotes() const;

    private:
        string state;
        string county;
        string candidate;
        string party;
        unsigned int numVotes;
};

#endif // VOTES_H