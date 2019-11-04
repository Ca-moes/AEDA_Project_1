//
// Created by Diana Freitas on 20/10/2019.
//



#ifndef PROJECT_1_DELEGATION_H
#define PROJECT_1_DELEGATION_H

#include "Sport.h"
#include "fstream"
#include <regex>

class Delegation {
    string peopleFilename; /**< Nome do ficheiro People.txt*/
    string competitionsFilename; /**< Nome do ficheiro de competições*/
    string country;
    float dailyCost;
    float totalCost;
    vector<Person *> people;
    vector<Athlete *> athletes;
    vector<Team*> teams;
    vector<Sport*> sports;
public:
    /** Delegation Default Constructor*/
    Delegation();

    /**Reads the Delegation's File and structures it in the program*/
    void readDelegationFile();

    /**Reads the File with the information about the Delegation's Athletes and Staff and structures it in the program
     *
     * @param lines a vector with the lines from People's file
     */
    void readPeopleFile(const vector<string> & lines);

    /**Reads the File with the information about the Delegation's Athletes and Staff and structures it in the program
 *
 * @param lines a vector with the lines from People's file
 */
    void readCompetitionsFile(const vector<string> & lines);

    /**
     * Get the Delegation's Country
     *
     * @returns the Delegation's Country
     */
    const string &getCountry() const;

    /** Set the Delegation's Country*/
    void setCountry(const string &country);

    /**
     * Get the Delegation's daily cost
     *
     * @returns the Delegation's daily cost
     */
    float getDailyCost() const;

    void setDailyCost(float dailyCost);

    float getTotalCost() const;

    void setTotalCost(float totalCost);

};

//Exceptions
//Opening Files Exceptions
class FileError{
    string file;
public:
    friend ostream & operator << (ostream & os, const FileError & file);
    explicit FileError(string file);
};

class FileStructureError{
    string file;
public:
    friend ostream & operator << (ostream & os, const FileStructureError & file);
    explicit FileStructureError(string file);
};

//Non Existent Sport
template <class Participant>
class NonExistentSport{
    string sport;
public:
    friend ostream & operator << <Participant>(ostream & os, const NonExistentSport<Participant> & c);
    explicit NonExistentSport(string name);
};

//Non Existent Competition exception
template <class Participant>
class NonExistentCompetition{
    string competition;
    string sport;
public:
    friend ostream & operator << <Participant>(ostream & os, const NonExistentCompetition<Participant> & c);
    explicit NonExistentCompetition(string name, string sport);
};


//Non Existent Trial
template <class Participant>
class NonExistentTrial{
    string name;
    string competition;
    string sport;
public:
    friend ostream & operator << <Participant> (ostream & os, NonExistentTrial & t);
    NonExistentTrial(string name, string competition, string sport);
};

//Non Existent Participant (Team or person)
template <class Participant>
class NonExistentParticipant{
    string participant;
    string where;
public:
    friend ostream & operator << <Participant> (ostream & os, NonExistentParticipant & p);
    NonExistentParticipant(string name, string where);
};

#endif //PROJECT_1_DELEGATION_H
