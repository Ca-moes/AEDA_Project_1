#ifndef PROJECT_1_SPORT_H
#define PROJECT_1_SPORT_H

#include "Competition.h"
#include "Person.h"

class Team;
class Athlete;
class Participant;

/**
 * A class to store the general information about a Sport
 */
class Sport {
protected:
    vector<Competition> competitions;/**< The competitions of the Sport */
public:
    string name;/**< The name of the Sport */
    /**Sport Default Constructor*/
    Sport(){};

    /**Sport Default Destructor*/
    ~Sport();

    /**Sport Constructor
     * @param name the name of the Sport
     * @param competitions the competitions
     */
    Sport(const string &name, const vector<Competition>  & competitions);

    /**Get the name of the Sport
    * @returns the name of the Sport
    */
    const string & getName() const;

    /**Set the name of the Sport
    * @param n name of the Sport
    */
    void setName(string n);

    /**Get the Sport's participants
     * @see getParticipants()
     * @returns sport's participants */
    virtual vector<Participant*> getParticipants() const{vector<Participant*> p; return p;};

    /**Set the Sport's competitions
     * @param sport's competitions */
    void setCompetitions(const vector<Competition> & competitions);

    /**Get the Sport's competitions
     * @returns sport's competitions*/
    vector<Competition> getCompetitions() const;

    /**Get a string with the information about the sport for testing purposes
     * @returns a string with the info about the sport for testing purposes
     */
    virtual string info() const;

    /** Check if a sport is a team sport
     * @see isTeamSport()
     * @returns false
     */
    virtual bool isTeamSport(){return false;};

    /**Compare two Sports Alphabetically
     * @param left the right Sport to compare with
     *@returns true if the name of the left Sport comes first in the alphabet and false otherwise
     */
    bool operator < (const Sport & left) const;

    /** Checks if two sports are the same
   * @param s1,s2 The Sports to compare
   * @returns true if the Sports have the same name
   */
    friend bool operator== (const Sport & s1,const Sport & s2 );
};

/**
 * A class to store the general information about a TeamSport
 */
class TeamSport: public Sport{
    vector<Team*> teams;/**< The teams participating in the Sport */
    unsigned int numberOfElements{};/**< The number of elements of a team */
public:
    /**Team Sport Default Constructor*/
    ~TeamSport(){};

    /**Team Sport Default Destructor*/
    TeamSport(){}

    /**Team Sport Copy Constructor
     * @param s the Team Sport to copy
     */
    TeamSport(const TeamSport & s);

    /**Set the Sport's participants
    * @param teams sport's participants */
    void setParticipants(const vector<Team> & teams);

    /**Get the Sport's participants
    * @returns sport's participants */
    vector<Participant*> getParticipants() const;

    /**Set the number of elements of the Team Sport
    * @param n number of elements */
    void setNumberofElements(unsigned int n);

    /**Get the number of elements of the Team Sport
    * @returns number of elements */
    unsigned int getNumberofElements() const;

    /**Add a Team to the Team Sport
    * @param n Team to add */
    void addTeam(Team* t);

    /**Get the Teams that play the Team Sport
    * @returns teams that play the Team Sport*/
    vector<Team*> getTeams() const;

    /** Check if a sport is a team sport
    * @returns true
    */
    bool isTeamSport(){return true;};
};

/**
 * A class to store the general information about an Individual Sport
 */
class IndividualSport: public Sport{
    vector<Athlete*> athletes;/**< The type of the medal - g(old), s(ilver), b(bronze) */
public:
    /**Individual Sport Default Destructor*/
    ~IndividualSport(){};

    /**Individual Sport Copy Constructor
     * @param s the Individual Sport to copy
     */
    IndividualSport(const IndividualSport & s);

    /**Individual Sport Default Constructor*/
    IndividualSport(){};

    /**Set the Sport's participants
    * @param athletes sport's participants */
    void setParticipants(const vector<Athlete*> & athletes);

    /**Get the Sport's participants
    * @returns sport's participants */
    vector<Participant*> getParticipants() const;

    /**Add a Athlete to the Team Sport
    * @param a Athlete to add */
    void addAthlete(Athlete* a);

    /**Get the Athletes that play the Individual Sport
    * @returns athletes that play the Individual Sport*/
    vector<Athlete*> getAthletes() const;

    /** Check if a sport is a team sport
    * @returns false
    */
    bool isTeamSport(){return false;};
};


#endif //PROJECT_1_SPORT_H
