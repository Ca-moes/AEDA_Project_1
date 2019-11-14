//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_PERSON_H
#define PROJECT_1_PERSON_H

#include "Date.h"
#include <vector>
#include <iomanip>
#include "Sport.h"

class Delegation;
/**
 * A class to store the general information about a Person
 */
class Person {
    string name;/**< The name of the person*/
    Date birth; /**< The birth of the person*/
    string passport;/**< The passport of the person*/
    Date arrival;/**< The date when the person arrives to the Olympics*/
    Date departure;/**< The date when the person goes back home*/
public:
    /**Person Constructor
     * @param name the name of the Person
     * @param birth the birth of the Person
     * @param passport the passport of the Person
     * @param arrival the arrival Date of the flight
     * @param departure the departure Date of the flight
     */
    Person(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure);

    //virtual double getDailyCost()=0;

    /**Person Default Constructor*/
    Person();

    /**Person Default virtual Destructor*/
    virtual ~Person() {}

    /**Get the name of the person
   * @returns the name of the person
   */
    const string &getName() const;

    /**Set the name of the person
   * @param name the name of the person
   */
    void setName(const string &name);

    /**Get the birth date of the person
   * @returns  birth date of the person
   */
    const Date &getBirth() const;

    /**Set the birth of the person
      *@param birth the birth of the person
      */
    void setBirth(const Date &birth);

    /**Get the passport of the person
   * @returns  passport of the person
   */
    const string &getPassport() const;

    /**Set the passport of a person
      * @param birth the passport of the person
      */
    void setPassport(const string &passport);

    /**Get the date of arrival of the person
    * @returns  date of arrival of the person
    */
    const Date &getArrival() const;

    /** Set the date of arrival of the person
      *@param arrival the the date of departure of the person
      */
    void setArrival(const Date &arrival);

    /**Get the date of departure of the person
    *@returns  date of departure of the person
    */
    const Date &getDeparture() const;

    /**Set the date of departure of the person
      *@param arrival the the date of departure of the person
      */
    void setDeparture(const Date &departure);

    /**Get the information about the person for testing purposes
    *@returns info about the person
    */
    virtual string info();

    /** Shows the information of a person of the Delegation in a human friendly way*/
    virtual void showInfo() const;

    /** Shows the information of a person of the Delegation in a human friendly way*/
    virtual void showInfoPerson() const;

    /** Checks if a person is an athlete
     *@returns true if the person is an athlete
     */
    virtual bool isAthlete() const {return false;};

    /** Checks if an athlete plays team sport
     *@param delegation the delegation
     *@returns true if the person is an athlete and plays a team sport
     */
    virtual bool playsTeamSport(const Delegation & delegation) const{return false;};

    /** Compares two people
    * @param p The Person to compare with
    * @returns true if the first is an athlete and the second is not, false if the first is not an athlete and second is and, otherwise, return true if the name of the first person comes first in the alphabet
    */
    bool operator<(const Person & p) const;

    /** Checks if two people are the same
    * @param p1,p2 The people to compare
    * @returns true if the people have the same name
    */
    friend bool operator==(const Person & p1, const Person &p2);
};

/** Used to print the info about the person
    * @param os the name of the ostream
    * @param p The Person
    * @returns reference to the original ostream to allow input/output chains
    */
ostream & operator<<(ostream & os, const Person & p);

/**
 * A class to store the general information about a Participant - Team or Athlete
 */
class Participant {
protected:
    string sport;/**< The sport played by the participant*/
    vector<string> competitions; /**< The list of competitions that the participant takes part in */
public:
    /**Participant Default Constructor*/
    Participant(){}

    /**Participant Default Destructor*/
    virtual ~Participant(){}

    /**
    * A pure virtual member.
    * @see getName()
    * @returns the name of a person
    */
    virtual const string &getName() const=0;

    /**
    * A pure virtual member.
    * @see setName()
    * @param name the name of a person
    */
    virtual void setName(const string &name)=0;

    /** Set the competitions the participant takes part in
    * @param competitions the competitions
    */
    void setCompetitions(const vector<string> & competitions);

    /** Get the competitions the participant takes part in
   * @returns the competitions
   */
    const vector<string> & getCompetitions() const;

    /** Get the Sport played by the participant
    * @returns the sport played by the participant
    */
    const string & getSport() const;

    /** Set the Sport played by the participant
    * @param sport the sport played by the participant
    */
    void setSport(const string & sport);

    /**
    * A pure virtual method.
    * @see showInfo()
    */
    virtual void showInfo() const = 0;
};

/**A class to store the general information about an Athlete*/
class Athlete : public Person, public Participant{
    float weight;/**< The weight of the Athlete*/
    float height;/**< The height of the Athlete*/
public:
    /**Athlete default constructor*/
    Athlete(){};

    /**Athlete default destructor*/
    ~Athlete(){}

    /**Athlete Constructor
     * @param name the name of the Person
     * @param birth the birth of the Person
     * @param passport the passport of the Person
     * @param arrival the arrival Date of the flight
     * @param departure the departure Date of the flight
     * @param sport the sport played byt the athlete
     * @param weight the weight of the athlete
     * @param height the height of the athlete
     */
    Athlete(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure, const string & sport, float weight,
            float height);

    /**Athlete Copy Constructor
     * @param a the Person to copy
     */
    Athlete(const Athlete & a);

    /** Set the name of the Athlete
    * @param name the name of the Athlete
    */
    void setName(const string &name);

    /** Get the name of the athlete
    * @returns the name of the athlete
    */
    const string &getName() const;

    /** Get the weight of the athlete
    * @returns the weight of the athlete
    */
    float getWeight() const;

    /** Set the weight of the Athlete
    * @param weight the weight of the Athlete
    */
    void setWeight(float weight);

    /** Get the height of the athlete
    * @returns the height of the athlete
    */
    float getHeight() const;

    /** Set the height of the Athlete
    * @param height the name of the Athlete
    */
    void setHeight(float height);

    /**Get a string with the information about the athlete for testing purpose
     * @returns a string with the info about the athlete
     */
    string info();

    /** Check if a person is an athlete
     * @returns true
     */
    bool isAthlete() const {return true;};

    /**Show the information about the athlete in a user friendly way*/
    void showInfoPerson() const;

    /**Show the information about the athlete in a user friendly way*/
    void showInfo() const;

    /** Checks if an athlete plays team sport
     *@param delegation the delegation
     *@returns true if the person is an athlete and plays a team sport
     */
    bool playsTeamSport(const Delegation &delegation) const;
};

/**A class to store the general information about the Team*/
class Team: public Participant{
private:
    vector<Athlete*> athletes;
    string name;
public:
    /**Team default constructor*/
    Team (){};
    /**Team default destructor*/
    ~Team(){}
    /**Team copy constructor
     * @param t the Team to copy
     */
    Team (const Team & t);

    /**Team constructor
     * @param name the name of the Team
     * @param sport the sport played by the team
     */
    Team(const string &name, const string & sport);

    /** Get the name of the team
    * @returns the name of the team
    */
    const string &getName() const;

    /** Set the name of the Team
    * @param name the name of the Team
    */
    void setName(const string &name);

    /** Get the members of the team
    * @returns the members of the team
    */
    const vector<Athlete*> & getAthletes() const;

    /** Set the members of the team
    * @param a the members of the team
    */
    void setAthletes(const vector<Athlete*> & a);
    
    /** Add an athlete to the Team
    * @param a a pointer to the Athlete to add
    */
    void addAthlete(Athlete* a);
    
    /** Remove an athlete of the Team
    * @param a a pointer to the Athlete to remove
    */
    void removeAthlete(string name);
  
    /**Show the information about the Team in a user friendly way*/
    void showInfo() const;

    /**Compare two teams
     * @param t the right team to compare with
     *@returns true if the name of the left team comes first in the alphabet
     */
    bool operator<(const Team & t) const;
};

/**A class to store the general information about a member of the Staff*/
class Staff: public Person{
    string function;/**< The function of the Staff member*/
public:
    /**Staff default constructor*/
    Staff();

    /**Staff constructor
    * @param name the name of the member of the Staff
     * @param birth the birth of the member of the Staff
     * @param passport the passport of the member of the Staff
     * @param arrival the arrival Date of the flight
     * @param departure the departure Date of the flight
     * @param function the function of the member of the Staff
     */
    Staff(const string &name, const Date &birth, const string &passport, const Date &arrival, const Date &departure,
          const string &function);

    /**Staff copy constructor
     *@param s Staff member to copy info from
     */
    Staff(const Staff & s);

    /** Get the name function of the staff member
    * @returns the name function of the staff member
    */
    const string &getFunction() const;

    /** Set the name function of the staff member
    * @param function the function of the staff member
    */
    void setFunction(const string &function);

    /**Show the information about the Staff member in a user friendly way*/
    string info();

    /** Check if a person is an athlete
     * @returns false
     */
    bool isAthlete() const {return false;};

    /**Show the information about the Staff in a user friendly way*/
    void showInfoPerson() const;

    //virtual double getDailyCost()=0;
};

#endif //PROJECT_1_PERSON_H
