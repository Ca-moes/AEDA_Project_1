//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_DELEGATION_H
#define PROJECT_1_DELEGATION_H

#include "Sport.h"
#include "fstream"
#include <regex>
#include <list>

class Delegation {
    string peopleFilename; /**< Nome do ficheiro People.txt*/
    string competitionsFilename; /**< Nome do ficheiro de competições*/
    string teamsFilename;
    string country;
    float dailyCostStaff;
    float dailyCostAthlete;
    float totalCost;
    vector<Person*> people;
    vector<Athlete*> athletes;
    vector<Team*> teams;
    vector<Sport*> sports;
    list<Sport*> oldSports;
    list<Person> oldAthletes;
    list<Team> oldTeams;
public:
    /** Delegation Default Constructor*/
    Delegation();

    /** Delegation Destructor (Write to .txt) */
    ~Delegation();

    /**Reads the Delegation's File and structures it in the program*/
    void readDelegationFile();

    /**Reads the File with the information about the Delegation's Athletes and Staff and structures it in the program
     *
     * @param lines a vector with the lines from People's file
     */
    void readPeopleFile(const vector<string> &lines);

    /** Used in Destructor, writes data back to .txt file
     * */
    void writePeopleFile();

    /**Reads the File with the information about the Delegation's Athletes and Staff and structures it in the program
    *
    * @param lines a vector with the lines from Competitions's file
    */
    void readCompetitionsFile(const vector<string> &lines);

    /** Used in Destructor, writes data back to .txt file
     * */
    void writeCompetitionsFile();

    /**Reads the File with the information about the Delegation's Teams and structures it in the program
    *
    * @param lines a vector with the lines from Teams's file
    */
    void readTeamsFile(const vector<string> & lines);

    /**
     * Get the Delegation's Country
     *
     * @returns the Delegation's Country
     */
    const string &getCountry() const;

    /** Set the Delegation's Country*/
    void setCountry(const string &country);

    /**
     * Set the Delegation's daily cost for Athletes
     *
     * @param dailyCost the Delegation's daily cost for Athletes
     */

    void setDailyCostAthlete(float dailyCost);

    /**
    * Get the Delegation's daily cost for Athletes
    *
    * @returns the Delegation's daily cost for Athletes
    */
    float getDailyCostAthlete() const;

    /**
    * Set the Delegation's daily cost for Teams
    *
    * @param dailyCost the Delegation's daily cost for Teams
    */
    void setDailyCostStaff(float dailyCost);

    /**
   * Get the Delegation's daily cost for Teams
   *
   * @returns the Delegation's daily cost for Teams
   */
    float getDailyCostStaff() const;

    /**
   * Get the Delegation's total cost
   *
   * @returns the Delegation's total cost
   */
    float getTotalCost() const;

    /**
   * Set the Delegation's total cost
   *
   * @param totalCost the Delegation's total cost
   */
    void setTotalCost(float totalCost);

    /**
   * Get the Sports
   *
   * @returns a vector of Sports
   */
    const vector<Sport*> & getSports() const;

    /**
   * Calculates the Delegation's total cost
   * Sets the Delegation's total cost
   */
    void calculateTotalCost();

    /**
    * Get the information about the Delegation in a formatted way
    *
    * @returns the Delegation's information
    */
    string info() const;

    /**
    * Adds a staff member to the people vector
    *
    */
    void addStaffMember();

    /**
    * Removes a staff member of the people vector
    *
    */
    void removeStaffMember();

    /**Changes a data of a staff member*/
    void changeStaffMember();

    /**
    * Adds an athlete to the people vector and the athlete vector
    *
    */
    void addAthlete();

    /**
   * Find a Person in the people vector
   *
   * @params name the name of the Person
   * @returns the index of the Person, -1 if it does not exist
   */
   int findPerson(const string name) const;

    /**
    * Find a Sport in the sports vector
    *
    * @params name the name of the Sport
    * @returns the index of the Sport, -1 if it does not exist
    */
    int findSport(const string name) const;

    /**Shows the information of all the members of the Portuguese Delegation in a human friendly way*/
    void showPortugueseMembers();

    /** Shows the information of a staff member of the Portuguese Delegation in a human friendly way*/
    void showStaffMember() const;

    /** Shows the information of all the staff members of the Portuguese Delegation in a human friendly way*/
    void showStaffMembers();

    /** Shows the information of an athlete of the Portuguese Delegation in a human friendly way*/
    void showAthlete() const;

    /** Shows the information of all the athletes of the Portuguese Delegation in a human friendly way*/
    void showAllAthletes();

    /** Shows the information of a team of the Portuguese Delegation in a human friendly way*/
    void showTeam() const;

    /** Shows the information of all teams of the Portuguese Delegation in a human friendly way*/
    void showAllTeams();

    /** End the participation of the Portuguese Delegation in a specific sport and saves the "history"- throws exception if no team exists
     * @param sport the name of the sport to remove
     */
    void removeSport(const string &sport);

    /** Shows the information of a specific competition in a specific sport - throws exception if the sport doesn't exist
     * @param sport the name of the sport to remove
     */
    void showCompetition(const string & sport);

    /** Shows the information of all the competitions in a specific sport - throws exception if no sport exists
     * @param sport the name of the sport to remove
     */
    void showAllCompetitions(const string & sport);

    /** Shows the information of all the trials in a specific sport - throws exception if no trials exists
     * @param sport the name of the sport to remove
     */
    void showAllTrials(const string & sport);

    /** Shows the information of all the trials in a specific competition - throws exception if no trials exists
     * @param competition the name of the competition
     */
    void showTrials(const Competition & competition) const;
};

//Exceptions
/**
 *  An exception thrown when there is an error locating or opening a file
 */
class FileError{
    string file;
public:
    friend ostream & operator << (ostream & os, const FileError & file);
    explicit FileError(string file);
};

/**
 *  An exception thrown when the structure of a file is not the expected
 */
class FileStructureError{
    string file;
public:
    friend ostream & operator << (ostream & os, const FileStructureError & file);
    explicit FileStructureError(string file);
};

/**
 *  An exception thrown when the Delegation doesn't take part in a sport
 */
class NonExistentSport{
    string sport;
public:
    friend ostream & operator <<(ostream & os, const NonExistentSport & c);
    explicit NonExistentSport(string name);
};

/**
 *  An exception thrown when the Delegation doesn't take part in any sport
 */
class NoSports{
    string sport;
public:
    friend ostream & operator <<(ostream & os, const NoSports & c);
    explicit NoSports();
};

/**
 *  An exception thrown when there is not any competition with a specific name in a specific sport
 */
class NonExistentCompetition{
    string competition;
    string sport;
public:
    friend ostream & operator <<(ostream & os, const NonExistentCompetition & c);
    explicit NonExistentCompetition(string name, string sport);
};

/**
 *  An exception thrown when there isn't any trial with a specific name in a specific competition of a particular sport
 */
class NonExistentTrial{
    string name;
    string competition;
    string sport;
public:
    friend ostream & operator <<(ostream & os, NonExistentTrial & t);
    NonExistentTrial(string name, string competition, string sport);
};

/**
 *  An exception thrown when there isn't any participant(team or athlete) with a specific name in the Delegation
 */
class NonExistentParticipant{
    string participant;
    string where;
public:
    friend ostream & operator <<(ostream & os, NonExistentParticipant & p);
    NonExistentParticipant(string name, string where);
};

/**
 *  An exception thrown when there isn't any person(staff or athlete) with a specific name in the Delegation
 */
class NonExistentPerson{
    string person;
public:
    friend ostream & operator <<(ostream & os, NonExistentPerson & p);
    NonExistentPerson(string name);
};

/**
 *  An exception thrown when there isn't any member with a specific name in the Delegation's staff
 */
class NonExistentStaff{
    string person;
public:
    friend ostream & operator <<(ostream & os, NonExistentStaff & p);
    NonExistentStaff(string name);
};

/**
 *  An exception thrown when there isn't any athlete with a specific name in the Delegation's athletes
 */
class NonExistentAthlete{
    string person;
public:
    friend ostream & operator <<(ostream & os, NonExistentAthlete & p);
    NonExistentAthlete(string name);
};

/**
 *  An exception thrown when there isn't any team with a specific name in the Delegation's teams
 */
class NonExistentTeam{
    string team;
public:
    friend ostream & operator <<(ostream & os, NonExistentTeam & p);
    NonExistentTeam(string name);
};

/**
 *  An exception thrown when a person with a specific name already belongs to the Delegation
 */
class PersonAlreadyExists{
    string person; /**@brief the name or de passport*/
public:
    friend ostream & operator <<(ostream & os, PersonAlreadyExists & p);
    PersonAlreadyExists(string person);
};

/**
 *  An exception thrown when the Delegation doesn't have any member(staff/athlete)
 */
class NoMembers{
public:
    friend ostream & operator <<(ostream & os, NoMembers & p);
    NoMembers();
};

/**
 *  An exception thrown when the Delegation doesn't have any competition to show in a specific sport
 */
class NoCompetitions{
    string sport;
public:
    friend ostream & operator <<(ostream & os, NoCompetitions & p);
    NoCompetitions(const string & sport);
};

/**
 *  An exception thrown when a competition within a sport doesn't have any trials
 */
class NoTrials{
    string sport;
public:
    friend ostream & operator <<(ostream & os, NoTrials & p);
    NoTrials(const string & sport);
};
#endif //PROJECT_1_DELEGATION_H
