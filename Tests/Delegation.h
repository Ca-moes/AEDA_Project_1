//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_DELEGATION_H
#define PROJECT_1_DELEGATION_H

#include <regex>
#include <fstream>
#include <Person.h>
#include "Trial.h"
#include "Sport.h"

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

    /** Used in Destructor, writes Competition data back to .txt file
     * */
    void writeCompetitionsFile();

    /**Reads the File with the information about the Delegation's Teams and structures it in the program
    *
    * @param lines a vector with the lines from Teams's file
    */
    void readTeamsFile(const vector<string> & lines);

    /** Used in Destructor, writes Team data back to .txt file
     * */
    void writeTeamsFile();

    /** Used in Destructor, writes Delegation data back to .txt file
     * */
    void writeDelegationFile();

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
     * @param dailyCost the Delegation's daily cost for Athletes
     */
    void setDailyCostAthlete(float dailyCost);

    /**
    * Get the Delegation's daily cost for Athletes
    * @returns the Delegation's daily cost for Athletes
    */
    float getDailyCostAthlete() const;

    /**
    * Set the Delegation's daily cost for Teams
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
     * Sorts the people and athletes vector
     *
     */
     void sortAllPeople();


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

    /** Removes a staff member of the people vector */
    void removeStaffMember();

    /** Changes a data of a staff member */
    void changeStaffMember();

    /**
    * Adds an athlete to the people vector and the athlete vector
    *
    */
    void addAthlete();

    /**
    * Removes an athlete from the people and athletes vectors
    *
    */
    void removeAthlete();

    /**
    * Changes data of an athlete from the people and athletes vectors
    *
    */
    void changeAthlete();

    /**
   * Find a Person in the people vector
   *
   * @params name the name of the Person
   * @returns the index of the Person, -1 if it does not exist
   */
   int findPerson(const string & name) const;

    /**
    * Find a Sport in the sports vector
    *
    * @params name the name of the Sport
    * @returns the index of the Sport, -1 if it does not exist
    */
    int findSport(const string & name) const;

    /**
    * Find a Team in the teams vector
    *
    * @params name the name of the Team
    * @returns the index of the Team, -1 if it does not exist
    */
    int findTeam(const string & name) const;

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

    /** End the participation of the Portuguese Delegation in a specific sport and saves the "history"
     * @param sport the name of the sport to remove
     * @throws NonExistentSport if the sport was successfully eliminated
     */
    void removeSport(const string &sport);

    /** Shows the information of a specific competition in a specific sport
     * @param sport the name of the sport
     * @throws NoCompetitions if the sport doesn't have competitions
     * @throws NonExistentCompetition if a specific competition doesn't exist in the sport
     */
    void showCompetition(const string & sport);

    /** Shows the information of all the competitions in a specific sport
     * @param sport the name of the sport
     * @throws NoCompetitions if the sport doesn't have competitions
     */
    void showAllCompetitions(const string & sport);

    /** Shows the information of all the trials in a specific sport
     * @param sport the name of the sport
     * @throws NoTrials if the sport's competitions don't have trials
     */
    void showAllTrials(const string & sport);

    /** Shows the information of all the trials ordered by Date
     * @param sport the name of the sport
     * @throws NoTrials if there are no sports with trials
     */
    void showAllTrials();

    /** Shows the information of all the trials in a specific competition
     * @param competition the name of the competition
     * @throws NoTrials if the competition doesn't have trials
     */
    void showTrials(const string & comp,const string & sport) const;

    /** Shows the information of all the trials in a specific day
     * @param sport the name of the sport
     * @throws NoTrials if the competition doesn't have trials
     */
    void showTrialsInDay();
    /** Shows the information of all the medals
    * @throws NoMedals if there isn't information about any medal
    */
    void showAllMedals() const;

    /** Shows the information of all the medals of a country
     * @throws NonExistentCountry if there the country doesn't take part in any competition
     * @throws NoMedals if the country doesn't have any medals
     */
    void showCountryMedals() const;

    /** Shows the information of all the medals of a country
     * @param c the country to show medals
     * @throws NonExistentCountry if there the country doesn't take part in any competition
     * @throws NoMedals if the country doesn't have any medals
     */
    void showCountryMedals(const string & c) const;

    /** Return the number of medals of a country
     * @param name the country
     * @throws NoMedals if the country doesn't have any medals
     * @returns number of medals of the country
     */
    int numberOfMedalsCountry(const string & name) const;

    /** Compares to countries by the total of medals
     * @param left country1
     * @param right country2
     * @returns true if left country has more medals than right
     */
    bool compareCountriesByMedals(const string &left, const string & right) const;

    /** Get a list of the countries that won medals
     * @returns list of countries with medals
     * @throws NoMedals if there are no medals
     */
    vector<string> getCountriesWithMedals() const;

    /** Show the most awarded countries in a user friendly way*/
    void mostAwardedCountries() const;

    /** Sort the countries by the total of medals
     * @param delegation the Delegation
     * @param countries the countries with medals to sort
     */
    void friend countriesSort(const Delegation & d, vector<string> & countries);

    /** Show the countries with more gold medals*/
    void mostAwardedGold() const;

    /** Get a list of the countries that won gold medals
     * @returns list of countries with gold medals
     * @throws NoMedals if there are no gold medals
     */
    vector<string> getCountriesWithGoldMedals() const;

    /** Compares to countries by the total of gold medals
     * @param left country1
     * @param right country2
     */
    bool compareCountriesByGoldMedals(const string &left, const string & right) const;

    /** Sort the countries by the total of gold medals
     * @param delegation the Delegation
     * @param countries the countries with gold medals to sort
     * @returns true if left country has more gold medals than right
     */
    void friend countriesSortGold(const Delegation & d, vector<string> & countries);

    /** Return the number of gold medals of a country
     * @param name country
     * @throws NoMedals if the country doesn't have any gold medals
     * @returns number of medals of a country
     */
    int numberOfGoldMedalsCountry(const string & name) const;

    /** Shows the information of all the gold medals of a country
    * @param c the country to show gold medals
    * @throws NonExistentCountry if there the country doesn't take part in any competition
    * @throws NoMedals if the country doesn't have any gold medals
    */
    void showCountryGoldMedals(const string & c) const;

    /** Shows the information of all the medals of an athlete
    * @param c the athlete to show medals
    */
    void showAthleteMedals(const string & c) const;

    /** Get a list of the athletes that won medals
     * @returns list of countries with medals
     * @throws NoMedals if there are no medals
     */
    vector<string> getAthletesWithMedals() const;

    /** Return the number of medals of an athlete
     *@param name the name of the athlete
     *@throws NoMedals if the athlete doesn't have any medals
     *@returns number of medals of the athlete
     */
    int numberOfMedalsAthlete(const string & name) const;

    /** Show the athletes with more medals*/
    void mostAwardedAthletes() const;

    /** Sort the athletes by the total of medals
     * @param delegation the Delegation
     * @param countries the athletes with medals to sort
     */
    friend void athletesSort(const Delegation & d,vector<string> & ats);

    /** Compares to athletes by the total of medals
     * @param left athlete1
     * @param right athlete2
     * @returns true if left athlete has more medals than right
     */
    bool compareAthletesByMedals(const string &left, const string & right) const;

    /** get the Team of an athlete
     * @param at athlete
     * @returns the team of the athlete
     */
    Team * getAthleteTeam(const string & at) const;

};

//Exceptions
/**
 *  An exception thrown when there is an error locating or opening a file
 */
class FileError{
    string file;/**< Name of the file that generated the error*/
public:
    /** Shows the name of the file that generated the error
     * @param os the name of ostream
     * @param file file
     * @returns reference to the original ostream to allow input/output chains
     */
    friend ostream & operator << (ostream & os, const FileError & file);
    /** File Error Constructor*/
    explicit FileError(string file);
};

/**
 *  An exception thrown when the structure of a file is not the expected
 */
class FileStructureError{
    string file;/**< Name of the file where the structure is not the expected*/
public:
    /** Shows the name of the file that generated the error
    * @param os the name of the ostream
    * @param file file
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator << (ostream & os, const FileStructureError & file);
    /** File Structure Error Constructor*/
    explicit FileStructureError(string file);
};

/**
 *  An exception thrown when the Delegation doesn't take part in a sport
 */
class NonExistentSport{
    string sport;/**< Name of the sport that doesn't exist anymore*/
public:
    /** Shows the name of the sport that no longer exists
    * @param os the name of the ostream
    * @param c sport tha doesn't exist anymore
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, const NonExistentSport & c);
    /** Non Existent Sport Constructor*/
    explicit NonExistentSport(string name);
};

/**
 *  An exception thrown when the Delegation doesn't take part in any sport
 */
class NoSports{
public:
    /** Indicates that no sports exist
    * @param os the name of the ostream
    * @param s NoSports object
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, const NoSports & s);
    /** No Sports Default Constructor*/
    explicit NoSports();
};

/**
 *  An exception thrown when there is not any competition with a specific name in a specific sport
 */
class NonExistentCompetition{
    string competition;/**< Name of the Competition that doesn't exist*/
    string sport;/**< Name of the sport where the competition was searched for*/
public:
    /** Shows the name of the competition that doesn't exist in a specific sport
    * @param os the name of the ostream
    * @param c The Competition that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, const NonExistentCompetition & c);
    /** Non Existent Competition Constructor*/
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
    /** Shows the name of the trial that doesn't exist in a specific competition in a specific sport
    * @param os the name of the ostream
    * @param t The Trial that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NonExistentTrial & t);
    /** Non Existent Trial Constructor*/
    NonExistentTrial(string name, string competition, string sport);
};

/**
 *  An exception thrown when there isn't any person(staff or athlete) with a specific name in the Delegation
 */
class NonExistentPerson{
    string person;/**< Name of the person that doesn't exist*/
public:
    /** Shows the name of the person that doesn't exist
    * @param os the name of the ostream
    * @param p The Person that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NonExistentPerson & p);
    /** Non Existent Person Constructor*/
    explicit NonExistentPerson(string name);
};

/**
 *  An exception thrown when there isn't any member with a specific name in the Delegation's staff
 */
class NonExistentStaff{
    string person;/**< Name of the staff member that doesn't exist*/
public:
    /** Shows the name of the staff member that doesn't exist
    * @param os the name of the ostream
    * @param p The Staff member that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NonExistentStaff & p);
    /** Non Existent Staff member Constructor*/
    explicit NonExistentStaff(string name);
};

/**
 *  An exception thrown when there isn't any athlete with a specific name in the Delegation's athletes
 */
class NonExistentAthlete{
    string person;/**< Name of the athlete that doesn't exist*/
public:
    /** Shows the name of the athlete that doesn't exist
    * @param os the name of the ostream
    * @param p The Athlete that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NonExistentAthlete & p);
    /** Non Existent Athlete Constructor*/
    explicit NonExistentAthlete(string name);
};

/**
 *  An exception thrown when there isn't any team with a specific name in the Delegation's teams
 */
class NonExistentTeam{
    string team;/**<the name of the team that doesn't exist*/
public:
    /** Shows the name of the team that doesn't exist
    * @param os the name of the ostream
    * @param p The Team that doesn't exist
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NonExistentTeam & p);
    /** Non Existent Team Constructor*/
    explicit NonExistentTeam(string name);
};

/**
 *  An exception thrown when a person with a specific name already belongs to the Delegation
 */
class PersonAlreadyExists{
    string person; /**<the name or de passport of the person that already exists*/
public:
    /** Shows the name of the person that already exists in the Delegation
    * @param os the name of the ostream
    * @param p The Person that already exists
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, PersonAlreadyExists & p);
    /** Person already exists Constructor*/
    explicit PersonAlreadyExists(string person);
};

/**
 *  An exception thrown when a team with a specific name already belongs to the Delegation
 */
class TeamAlreadyExists{
    string team; /**<the name or de passport of the person that already exists*/
public:
    /** Shows the name of the team that already exists in the Delegation
    * @param os the name of the ostream
    * @param p The Team that already exists
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, TeamAlreadyExists & p);
    /** Team already exists Constructor*/
    explicit TeamAlreadyExists(string team);
};

/**
 *  An exception thrown when the Delegation doesn't have any member(staff/athlete)
 */
class NoMembers{
public:
    /** Informs that there are no members
    * @param os the name of the ostream
    * @param p NoMembers object
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream & operator <<(ostream & os, NoMembers & p);
    /** No Members default constructor*/
    NoMembers();
};

/**
 *  An exception thrown when the Delegation doesn't have any competition to show in a specific sport
 */
class NoCompetitions{
    string sport; /**< Name of the sport that doesn't have competitions*/
public:
    /** Informs that there are no competitions
   * @param os the name of the ostream
   * @param p NoCompetitions object
   * @returns reference to the original ostream to allow input/output chains
   */
    friend ostream & operator <<(ostream & os, NoCompetitions & p);
    /** No competitions constructor*/
    explicit NoCompetitions(const string & sport);
};

/**
 *  An exception thrown when a competition within a sport doesn't have any trials
 */
class NoTrials{
    string sport;/**< Name of the sport or competition that doesn't have trials*/
public:
    /** Informs that there are no trials
   * @param os the name of the ostream
   * @param p NoTrials object
   * @returns reference to the original ostream to allow input/output chains
   */
    friend ostream & operator <<(ostream & os, NoTrials & p);
    /** No trials constructor*/
    explicit NoTrials(const string & sport);
    NoTrials(){sport="";}
};

/**
 *  An exception thrown when the Delegation doesn't have info about any medal or if a country doesn't have medals
 */
class NoMedals{
public:
    string country;/**<The country with no medals*/
    /** Indicates that no medals exist
    * @param os the name of the ostream
    * @param s NoMedals object
    * @returns reference to the original ostream to allow input/output chains
    */
    friend ostream &operator<<(ostream &os, NoMedals &m);
    /** No Medals Default Constructor*/
    NoMedals();
    explicit NoMedals(const string & c);
};

/**
 *  An exception thrown when the Sport is not a team sport
 */
class NotATeamSport{
    string sport; /**< Name of the sport that doesn't have competitions*/
public:
    /** Informs that the sport is not a team sport
   * @param os the name of the ostream
   * @param p NotATeamSport object
   * @returns reference to the original ostream to allow input/output chains
   */
    friend ostream & operator <<(ostream & os, NotATeamSport & p);
    /** NotATeamSport constructor*/
    explicit NotATeamSport(const string & s);
};

/**
 *  An exception thrown when the Team is full
 */
class FullTeam{
    string team; /**< Name of the sport that doesn't have competitions*/
public:
    /** Informs that the team is full
   * @param os the name of the ostream
   * @param p FullTeam object
   * @returns reference to the original ostream to allow input/output chains
   */
    friend ostream & operator <<(ostream & os, FullTeam & p);
    /** FullTeam constructor*/
    explicit FullTeam(const string & t);
};
#endif //PROJECT_1_DELEGATION_H
