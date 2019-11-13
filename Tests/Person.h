//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_PERSON_H
#define PROJECT_1_PERSON_H

#include "Date.h"
#include <vector>
#include "Sport.h"
#include <iomanip>

class Person {
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
    Person();

    virtual ~Person() {}

    const string &getName() const;

    void setName(const string &name);

    const Date &getBirth() const;

    void setBirth(const Date &birth);

    const string &getPassport() const;

    void setPassport(const string &passport);

    const Date &getArrival() const;

    void setArrival(const Date &arrival);

    const Date &getDeparture() const;

    void setDeparture(const Date &departure);

    virtual string info();

    virtual void showInfo() const;

    virtual void showInfoPerson() const;

    virtual bool isAthlete() const {return false;};

    bool operator<(const Person & p) const;

    friend bool operator==(const Person & p1, const Person &p2);
private:
    string name;
    Date birth;
    string passport;
    Date arrival;
    Date departure;
};

ostream & operator<<(ostream & os, const Person & p);

class Participant {
protected:
    string sport;
    vector<string> competitions;
public:
    Participant(){}
    virtual ~Participant(){}
    virtual const string &getName() const=0;
    virtual void setName(const string &name)=0;
    void setCompetitions(const vector<string> & competitions);
    const vector<string> & getCompetitions() const;
    const string & getSport() const;
    void setSport(const string & sport);
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
    vector<Athlete*> athletes;
    string name;
    //historial
public:
    Team (){};
    ~Team(){}
    Team (const Team & t);
    Team(const string &name, const string & sport);
    const string &getName() const;
    void setName(const string &name);
    const vector<Athlete*> & getAthletes() const;
    void setAthletes(const vector<Athlete*> & a);
    void addAthlete(Athlete* a);
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
