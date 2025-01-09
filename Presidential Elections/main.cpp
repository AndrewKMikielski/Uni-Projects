/*  Andrew Mikielski 11/06/2024
    Project 4: Presidentital Elections
    This program will read in election data from a user-specified file
    and save that information to class objects in order to provide
    the user the ability to view the election data in multiple ways.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "Votes.h"
#include "Candidate.h"
#include "StateVotes.h"

using namespace std;

const string STATES[] = { "ALABAMA", "ALASKA", "ARIZONA", "ARKANSAS", "CALIFORNIA", "COLORADO",
	"CONNECTICUT", "DELAWARE", "FLORIDA", "GEORGIA", "HAWAII", "IDAHO", "ILLINOIS",
	"INDIANA", "IOWA", "KANSAS", "KENTUCKY", "LOUISIANA", "MAINE", "MARYLAND", "MASSACHUSETTS", "MICHIGAN",
	"MINNESOTA", "MISSISSIPPI", "MISSOURI", "MONTANA", "NEBRASKA", "NEVADA", "NEW HAMPSHIRE", "NEW JERSEY",
	"NEW MEXICO", "NEW YORK", "NORTH CAROLINA", "NORTH DAKOTA", "OHIO", "OKLAHOMA", "OREGON", "PENNSYLVANIA",
	"RHODE ISLAND", "SOUTH CAROLINA", "SOUTH DAKOTA", "TENNESSEE", "TEXAS", "UTAH", "VERMONT", "VIRGINIA",
	"WASHINGTON", "WASHINGTON DC", "WEST VIRGINIA", "WISCONSIN", "WYOMING" };
const int NUM_STATES = 51;

//  Returns a string converted to all upper case
string strToUpper(string strInput);

//  Clears input buffer up to 10,000 characters.
void clearInputBuffer();

//  Gets user's input and returns it in all upper case.
string getUserStringAsUppercase();

//  Reads in user-specified file into a vector of Votes. Returns a vector of Votes objects.
vector<Votes> readInFileToVector(const string& electionFileName);

//  Displays the number of election records and total number of votes. Takes a vector of Votes objects.
void dataOverview(const vector<Votes>& VotesList);

//  Creates and returns a list of Candidate objects. Takes a vector of Votes objects.
vector<Candidate> buildCandidateList(const vector<Votes>& VotesList);

//  Outputs 1 bar for every 150,000 votes, rounding to the closest number.
//  Takes number of votes.
void printBars(const int& numVotes);

//  Displays each candidate, their party, and number of votes received. Takes a vector of Votes objects.
void nationalResults(const vector<Votes>& VotesList);

//  Displays each candidate, their party, and number of votes received in a single state.
//  Takes a vector of Votes objects and user input.
void stateResults(const vector<Votes>& VotesList, const string& input);

//  Adds up all the votes for a single candidate and the total votes in each state.
//  Takes a vector of Votes objects and user input.
void candidateResults(const vector<Votes>& VotesList, const string& input);

//  Finds the candidate's best state and outputs the Candidate's results in each state.
//  Takes a vector of StateVotes objects.
void printCandidateResults(const vector<StateVotes>& StateVotesList);

//  Asks user for a County name and outputs Votes information for
//  any partial match of the county name.
//  Takes a vector of Votes objects and user input.
void countySearch(const vector<Votes>& VotesList, const string& input);

int main() {
    string input;
    vector<Votes> VotesList;
    char menu;

    // Figure out which data file to load into memory
    cout << "Enter file to use: ";
    getline(cin, input);
    VotesList = readInFileToVector(input);
    cout << endl;

    // Main menu logic loop
    do {
        cout << "Select a menu option:" << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. National results" << endl;
        cout << "  3. State results" << endl;
        cout << "  4. Candidate results" << endl;
        cout << "  5. County search" << endl;
        cout << "  6. Exit" << endl;
        cout << "Your choice: ";
        cin >> menu;
        cout << endl;

        switch(menu) {
            case '1':
                dataOverview(VotesList);
                break;
            case '2':
                nationalResults(VotesList);
                break;
            case '3':
                cout << "Enter state: ";
                input = getUserStringAsUppercase();
                cout << endl;
                stateResults(VotesList, input);
                break;
            case '4':
                cout << "Enter candidate: ";
                input = getUserStringAsUppercase();
                cout << endl;
                candidateResults(VotesList, input);
                break;
            case '5':
                cout << "Enter county: ";
                input = getUserStringAsUppercase();
                countySearch(VotesList, input);
                break;
        }
    } while(menu != '6');
    // end of main menu logic loop

    return 0;
} // end main()

//  Returns a string converted to all upper case
string strToUpper(string strInput) {
    for(unsigned int i = 0; i < strInput.size(); i++) {
        strInput.at(i) = toupper(strInput.at(i));
    }

    return strInput;
} // end strToUpper()

//  Clears input buffer up to 10,000 characters.
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
} // end clearInputBuffer()

//  Gets user's input and returns it in all upper case.
string getUserStringAsUppercase() {
    string input;
    clearInputBuffer();
    getline(cin, input);
    input = strToUpper(input);

    return input;
} // end getUserStringAsUppercase()

//  Reads in user-specified file into a vector of Votes. Returns a vector of Votes objects.
//  Assumed file format per line: state,county,candidate,party,numVotes
vector<Votes> readInFileToVector(const string& electionFileName) {
    string currData;
    Votes currVote;
    vector<Votes> VotesVector;
    ifstream fileIn;

    fileIn.open(electionFileName);

    while(!fileIn.eof()) {
        // State
        getline(fileIn, currData, ',');
        currVote.setState(currData);

        // County
        getline(fileIn, currData, ',');
        currVote.setCounty(currData);

        // Candidate
        getline(fileIn, currData, ',');
        currVote.setCandidate(currData);

        // Party
        getline(fileIn, currData, ',');
        currVote.setParty(currData);

        // Number of Votes
        getline(fileIn, currData);
        currVote.setNumVotes(stoi(currData));

        VotesVector.push_back(currVote);
    }

    fileIn.close();
    return VotesVector;
} // end readInFileToVector()

//  Displays the number of election records and total number of votes.
//  Takes a vector of Votes objects. Iterates over the vector list and adds up their numVotes.
void dataOverview(const vector<Votes>& VotesList) {
    unsigned int numRecords = VotesList.size();
    unsigned int numTotalVotes = 0;

    for(unsigned int i = 0; i < numRecords; i++) {
        numTotalVotes += VotesList.at(i).getNumVotes();
    }

    cout << "Number of election records: " << numRecords << endl;
    cout << "Total number of votes recorded: " << numTotalVotes << endl;
} // end dataOverview()

//  Creates and returns a list of Candidate objects. Takes a vector of Votes objects.
vector<Candidate> buildCandidateList(const vector<Votes>& VotesList) {
    Votes currVotes;
    Candidate currCandidate;
    vector<Candidate> CandidateList;
    bool isNewCandidate;

    // Put the first Votes from the main list into the Candidate list
    currVotes = VotesList.at(0);
    currCandidate.setWithVotesObject(currVotes);
    CandidateList.push_back(currCandidate);
    
    // Outer loop goes through the Votes list to build a Candidate list.
    // Outer loop assumes we have a new candidate and the Inner loop goes through
    // the Candidate list to update a candidate's votes, if that candidate is found.
    // If the Inner Loop didn't update a candidate it means we have a new candidate to add.
    for(size_t i = 1; i < VotesList.size(); i++) {
        isNewCandidate = true;
        currVotes = VotesList.at(i);

        for(size_t j = 0; j < CandidateList.size(); j++) {
            if(currVotes.getCandidate() == CandidateList.at(j).getCandidate()) {
                // Adds votes to a matching Candidate
                CandidateList.at(j).updateNumVotes(currVotes.getNumVotes());
                isNewCandidate = false;
                break;
            }
        }
        // Add a new candidate to the list
        if(isNewCandidate) {
            currCandidate.setWithVotesObject(currVotes);
            CandidateList.push_back(currCandidate);
        }
    }

    // Ensure we always have an OTHER Candidate category for output purposes.
    bool OtherExists = false;
    for(size_t i = 0; i < CandidateList.size(); i++) {
        if(CandidateList.at(i).getCandidate() == "OTHER") {
            OtherExists = true;
            break;
        }
    }
    if(!OtherExists) {
        currCandidate.setCandidate("OTHER");
        currCandidate.setParty("");
        currCandidate.setState("");
        CandidateList.push_back(currCandidate);
    }

    return CandidateList;
} // end buildCandidateList()

//  Outputs 1 bar for every 150,000 votes, rounding to the closest number.
//  Takes number of votes.
void printBars(const int& numVotes) {
    int numBars = numVotes / 150000;
    int remainder = numVotes % 150000;

    if(remainder >= 80000) {
        numBars++;
    }

    for(int i = 0; i < numBars; i++) {
        cout << "|";
    }
}

//  Displays each candidate, their party, and number of votes received,
//  sorted by number of votes in descending order. Takes a vector of Votes objects.
void nationalResults(const vector<Votes>& VotesList) {
    Candidate currCandidate;
    // Creates the list of candidates:
    vector<Candidate> CandidateList = buildCandidateList(VotesList);

    // Output results sorted by greatest number of votes
    sort(CandidateList.begin(), CandidateList.end());
    for(int i = (CandidateList.size() - 1); i >= 0; i--) {
        currCandidate = CandidateList.at(i);
        cout << left << setw(20) << currCandidate.getCandidate();
        cout << setw(15) << currCandidate.getParty();
        cout << right << setw(10) << currCandidate.getNumVotes() << endl;
    }
} // end nationalResults()

//  Gets user input for a single State and builds a list of Candidate objects for that state
//  to display each candidate, their party, and number of votes received in that state.
//  Takes a vector of Votes objects and user input.
void stateResults(const vector<Votes>& VotesList, const string& input) {
    Votes currVotes;
    vector<Votes> sublist;
    vector<Candidate> CandidateList;

    // Go through the Votes and create a Votes sublist
    // containing only the State the user asked for.
    for(size_t i = 0; i < VotesList.size(); i++) {
        currVotes = VotesList.at(i);
        if(input == currVotes.getState()) {
            sublist.push_back(currVotes);
        }
    }

    // Create a Candidate list from the Votes sublist.
    CandidateList = buildCandidateList(sublist);

    // Outputs results sorted by greatest number of votes
    sort(CandidateList.begin(), CandidateList.end());
    for(int i = (CandidateList.size() - 1); i >= 0; i--) {
        cout << left << setw(20) << CandidateList.at(i).getCandidate();
        printBars(CandidateList.at(i).getNumVotes());
        cout << endl;
    }
} // end stateResults()

//  Asks the user for a candidate. Builds a list of StateVotes objects, one per state.
//  Iterates through the list of StateVotes and adds up all the candidate's votes
//  and the total votes for each state. Takes a vector of Votes objects and user input.
void candidateResults(const vector<Votes>& VotesList, const string& input) {
    Votes currVotes;
    vector<StateVotes> StateVotesList;
    string VotesCandidate;
    size_t partialMatch;

    // Assign a state to each StateVotes object
    StateVotesList.resize(NUM_STATES);
    for(int i = 0; i < NUM_STATES; i++) {
        StateVotesList.at(i).setState(STATES[i]);
    }

    // Tally all of the votes for each state with respect to the user's Candidate
    for(size_t i = 0; i < VotesList.size(); i++) {
        currVotes = VotesList.at(i);
        VotesCandidate = currVotes.getCandidate();

        // If the candidate's name is a partial match to the user's input then
        // add the votes to candidate's votes and Total votes for that Votes object's state.
        partialMatch = VotesCandidate.find(input);
        if(partialMatch != string::npos) {
            for(int j = 0; j < NUM_STATES; j++) {
                if(currVotes.getState() == StateVotesList.at(j).getState()) {
                    StateVotesList.at(j).updateCandidateVotes(currVotes.getNumVotes());
                    StateVotesList.at(j).updateTotalVotes(currVotes.getNumVotes());
                    StateVotesList.at(j).setCandidate(VotesCandidate);
                    break;
                }
            }
        } // end if{}, begin else{}
        // If the candidate's name is not a partial match to the user's input then
        // add the votes to the Total votes for that Votes object's state.
        else {
            for(int j = 0; j < NUM_STATES; j++) {
                if(currVotes.getState() == StateVotesList.at(j).getState()) {
                    StateVotesList.at(j).updateTotalVotes(currVotes.getNumVotes());
                    break;
                }
            }
        } // end else{}
    }
    // Output the candidate's results
    printCandidateResults(StateVotesList);
} // end candidateResults()

//  Displays a single candidate's results in each State,
//  showing number of votes for the candidate, total number of votes,
//  and percentage of votes the candidate received.
//  Displays candidate's best State. Takes a vector of StateVotes objects.
void printCandidateResults(const vector<StateVotes>& StateVotesList) {
    double greatestPercentage;
    double percentage;
    string candidateName;
    string bestState;

    // A name is only provided in a StateVotes object if
    // the candidate received any votes in the state,
    // so we must get the candidate name for the output.
    candidateName = StateVotesList.at(0).getCandidate();
    for(int i = 1; i < NUM_STATES; i++) {
        if(candidateName == "") {
            candidateName = StateVotesList.at(i).getCandidate();
        } else {
            break;
        }
    }
    // The for loop outputs results per state while keeping track
    // of the candidate's best state by percentage of votes.
    greatestPercentage = StateVotesList.at(0).percentVotes();
    for(int i = 0; i < NUM_STATES; i++) {
        percentage = StateVotesList.at(i).percentVotes();
        if(percentage > greatestPercentage) {
            greatestPercentage = percentage;
            bestState = StateVotesList.at(i).getState();
        }
        // Output results per state
        cout << left << setw(20) << StateVotesList.at(i).getState();
        cout << right << setw(10) << StateVotesList.at(i).getCandidateVotes();
        cout << setw(10) << StateVotesList.at(i).getTotalVotes();
        cout << setw(7) << fixed << setprecision(1) << percentage << "%" << endl;
    }
    cout << "The best state for " << candidateName << " is " << bestState << endl;
} // end printCandidateResults()

//  Asks user for a County name and outputs Votes information for
//  any partial match of the county name.
//  Takes a vector of Votes objects and user input.
void countySearch(const vector<Votes>& VotesList, const string& input) {
    Votes currVotes;
    size_t partialMatch;
    string countyState;

    for(size_t i = 0; i < VotesList.size(); i++) {
        currVotes = VotesList.at(i);
        partialMatch = currVotes.getCounty().find(input);
        if(partialMatch != string::npos) {
            countyState = currVotes.getCounty() + ", " + currVotes.getState();
            cout << left << setw(40) << countyState;
            cout << setw(20) << currVotes.getCandidate();
            cout << right << setw(10) << currVotes.getNumVotes() << endl;
        }
    }
} // end countySearch()