//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_PERSON_H
#define PROJECT_1_PERSON_H

#include "Date.h"
#include <vector>
#include "Sport.h"
#include <iomanip>

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
    /**
     * Person Constructor
     *
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

    /**
   * Get the name of the person
   *
   * @returns the name of the person
   */
    const string &getName() const;

    /**
   * Set the name of the person
   *
   * @param name the name of the person
   */
    void setName(const string &name);

    /**
   * Get the birth date of the person
   *
   * @returns  birth date of the person
   */
    const Date &getBirth() const;

    /**
      * Set the birth of the person
      *
      * @param birth the birth of the person
      */
    void setBirth(const Date &birth);

    /**
   * Get the passport of the person
   *
   * @returns  passport of the person
   */
    const string &getPassport() const;

    /**
      * Set the passport of a person
      *
      * @param birth the passport of the person
      */
    void setPassport(const string &passport);

    /**
    * Get the date of arrival of the person
    *
    * @returns  date of arrival of the person
    */
    const Date &getArrival() const;

    /**
      * Set the date of arrival of the person
      *
      * @param arrival the the date of departure of the person
      */
    void setArrival(const Date &arrival);

    /**
    * Get the date of departure of the person
    *
    * @returns  date of departure of the person
    */
    const Date &getDeparture() const;

    /**
      * Set the date of departure of the person
      *
      * @param arrival the the date of departure of the person
      */
    void setDeparture(const Date &departure);

    /**
    * Get the information about the person for testing purposes
    *
    * @returns info about the person
    */
    virtual string info();

    /** Shows the information of a person of the Portuguese Delegation in a human friendly way*/
    virtual void showInfo() const;

    /** Shows the information of a person of the Portuguese Delegation in a human friendly way*/
    virtual void showInfoPerson() const;

    /** Checks if a person is an athlete
     *@returns true if the person is an athlete
     */
    virtual bool isAthlete() const {return false;};

    /** Compares two people
    * @param p The Person that already exists
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
    * @see setName()
    * @param name the name of a person
    */
    virtual void showInfo() const = 0;
};

class Athlete : public Person, public Participant{
    float weight;
    float height;
public:
    Athlete(){};
    ~Athlete(){}
    Athlete(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure, const string & sport, float weight,
            float height);
    Athlete(const Athlete & a); //copy constructor;
    void setName(const string &name);
    const string &getName() const;
    float getWeight() const;
    void setWeight(float weight);
    float getHeight() const;
    void setHeight(float height);
    string info();
    bool isAthlete() const {return true;};
    void showInfoPerson() const;
    void showInfo() const;
};

class Team: public Participant{
private:
    vector<Athlete> athletes;
    string name;
    //historial
public:
    Team (){};
    ~Team(){}
    Team (const Team & t);
    Team(const string &name, const string & sport);
    const string &getName() const;
    void setName(const string &name);
    const vector<Athlete> & getAthletes() const;
    void setAthletes(const vector<Athlete> & a);
    void showInfo() const;
    bool operator<(const Team & t) const;
};

class Staff: public Person{
    string function;
public:
    Staff();
    Staff(const string &name, const Date &birth, const string &passport, const Date &arrival, const Date &departure,
          const string &function);
    Staff(const Staff & s);
    const string &getFunction() const;
    void setFunction(const string &function);
    string info();
    bool isAthlete() const {return false;};
    void showInfoPerson() const;
    //virtual double getDailyCost()=0;  //depende do tipo de funcionário
};

#endif //PROJECT_1_PERSON_H
