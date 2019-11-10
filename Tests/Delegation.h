//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_DELEGATION_H
#define PROJECT_1_DELEGATION_H

#include "Sport.h"
#include "fstream"
#include <regex>
#include <list>
/**
 * A class to store the general information about a Delegation that takes part in the 2020 Tokyo Olympic Games
 */
class Delegation {
    string peopleFilename; /**< Name of the people file - people.txt*/
    string competitionsFilename; /**< Name of the competitions file*/
    string teamsFilename; /**< Name of the teams file*/
    string country; /**< The country of the Delegation*/
    float dailyCostStaff;/**< Daily Cost for the staff members*/
    float dailyCostAthlete;/**< Daily Cost for the athletes*/
    float totalCost;/**< Total Paid by the Delegation in the Olympics*/
    vector<Person*> people;/**< All the members of the Delegation*/
    vector<Athlete*> athletes;/**< All the athletes of the Delegation*/
    vector<Team*> teams;/**< All the teams of the Delegation*/
    vector<Sport*> sports;/**< All the sports of the Delegation*/
    list<Sport*> oldSports;/**< Sports that the Delgation no longer participates in*/
    list<Person> oldAthletes;/**< Ahletes that no longer belong to the Delegation*/
    list<Team> oldTeams; /**< Teams that no longer belong to the Delegation*/
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

    /**Shows the information of all the members of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Members
     */
    void showMembers();

    /** Shows the information of a staff member of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Members
     * @throws NonExistentStaff if the Delegation's Staff doesn't have a specific member
     */
    void showStaffMember() const;

    /** Shows the information of all the staff members of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation's Staff has no Members
     */
    void showStaffMembers();

    /** Shows the information of an athlete of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Athletes
     */
    void showAthlete() const;

    /** Shows the information of all the athletes of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Athletes
     * @throws NonExistentAthlete if a specific athlete doesn't exist in the Delegation
     */
    void showAllAthletes();

    /** Shows the information of all teams of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Teams
     */
    void showAllTeams();

    /** Shows the information of a team of the Portuguese Delegation in a human friendly way
     * @throws NoMembers if the Delegation has no Teams
     * @throws NonExistentTeam if a specific team doesn't exist in the Delegation
     */
    void showTeam() const;

    /** End the participation of the Portuguese Delegation in a specific sport and saves the "history"- throws exception if no team exists
     * @param sport the name of the sport to remove
     * @throws NonExistentSport if the sport was successfully eliminated
     */
    void removeSport(const string &sport);

    /** Shows the information of a specific competition in a specific sport - throws exception if the sport doesn't exist
     * @param sport the name of the sport to remove
     * @throws NoCompetitions if the sport doesn't have competitions
     * @throws NonExistentCompetition if a specific competition doesn't exist in the sport
     */
    void showCompetition(const string & sport);

    /** Shows the information of all the competitions in a specific sport - throws exception if no sport exists
     * @param sport the name of the sport to remove
     * @throws NoCompetitions if the sport doesn't have competitions
     */
    void showAllCompetitions(const string & sport);

    /** Shows the information of all the trials in a specific sport - throws exception if no trials exists
     * @param sport the name of the sport to remove
     * @throws NoTrials if the sport's competitions don't have trials
     */
    void showAllTrials(const string & sport);

    /** Shows the information of all the trials in a specific competition - throws exception if no trials exists
     * @param competition the name of the competition
     * @throws NoTrials if the competition doesn't have trials
     */
    void showTrials(const Competition & competition) const;
};

//Exceptions
/**
 *  An exception thrown when there is an error locating or opening a file
 */
class FileError{
    string file;/**< Name of the file that generated the error*/
public:
    friend ostream & operator << (ostream & os, const FileError & file);
    explicit FileError(string file);
};

/**
 *  An exception thrown when the structure of a file is not the expected
 */
class FileStructureError{
    string file;/**< Name of the file where the structure is not the expected*/
public:
    friend ostream & operator << (ostream & os, const FileStructureError & file);
    explicit FileStructureError(string file);
};

/**
 *  An exception thrown when the Delegation doesn't take part in a sport
 */
class NonExistentSport{
    string sport;/**< Name of the sport that doesn't exist anymore*/
public:
    friend ostream & operator <<(ostream & os, const NonExistentSport & c);
    explicit NonExistentSport(string name);
};

/**
 *  An exception thrown when the Delegation doesn't take part in any sport
 */
class NoSports{
public:
    friend ostream & operator <<(ostream & os, const NoSports & c);
    explicit NoSports();
};

/**
 *  An exception thrown when there is not any competition with a specific name in a specific sport
 */
class NonExistentCompetition{
    string competition;/**< Name of the Competition that doesn't exist*/
    string sport;/**< Name of the sport where the competition was searched for*/
public:
    friend ostream & operator <<(ostream & os, const NonExistentCompetition & c);
    explicit NonExistentCompetition(string name, string sport);
};

/**
 *  An exception thrown when there isn't any trial with a specific name in a specific competition of a particular sport
 */
class NonExistentTrial{
    string name;/**< Name of the Trial that doesn't exist*/
    string competition;/**< Name of the competition where the trial was searched for*/
    string sport;/**< Name of the sport where the trial was searched for*/
public:
    friend ostream & operator <<(ostream & os, NonExistentTrial & t);
    NonExistentTrial(string name, string competition, string sport);
};

/**
 *  An exception thrown when there isn't any person(staff or athlete) with a specific name in the Delegation
 */
class NonExistentPerson{
    string person;/**< Name of the person that doesn't exist*/
public:
    friend ostream & operator <<(ostream & os, NonExistentPerson & p);
    NonExistentPerson(string name);
};

/**
 *  An exception thrown when there isn't any member with a specific name in the Delegation's staff
 */
class NonExistentStaff{
    string person;/**< Name of the staff member that doesn't exist*/
public:
    friend ostream & operator <<(ostream & os, NonExistentStaff & p);
    NonExistentStaff(string name);
};

/**
 *  An exception thrown when there isn't any athlete with a specific name in the Delegation's athletes
 */
class NonExistentAthlete{
    string person;/**< Name of the athlete that doesn't exist*/
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
    string person; /**the name or de passport of the person that already exists*/
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
    string sport; /**< Name of the sport that doesn't have competitions*/
public:
    friend ostream & operator <<(ostream & os, NoCompetitions & p);
    NoCompetitions(const string & sport);
};

/**
 *  An exception thrown when a competition within a sport doesn't have any trials
 */
class NoTrials{
    string sport;/**< Name of the sport or competition that doesn't have trials*/
public:
    friend ostream & operator <<(ostream & os, NoTrials & p);
    NoTrials(const string & sport);
};
#endif //PROJECT_1_DELEGATION_H
