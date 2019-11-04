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

    virtual bool isAthlete(){return false;};
private:
    string name;
    Date birth;
    string passport;
    Date arrival;
    Date departure;
    public:

};

class Participant {
    string sport;
    unsigned int ranking; // o ranking é recebido mas alterado com base nos dados fornecidos?
public:
    Participant(){}
    Participant(unsigned int ranking, const string & sport);
    virtual const string &getName() const=0;
    virtual void setName(const string &name)=0;
    unsigned int getRanking() const;
    void setRanking(int ranking);
    const string & getSport() const;
    void setSport(const string & sport);
};

class Athlete : public Person, public Participant{
    float weight;
    float height;
    vector<string> competitions;
    vector<Medal> medals;
public:
    Athlete();
    Athlete(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure, const string & sport, float weight,
            float height, int ranking);
    Athlete(const Athlete & a); //copy constructor;
    void setName(const string &name);
    const string &getName() const;
    float getWeight() const;
    void setWeight(float weight);
    float getHeight() const;
    void setHeight(float height);
    void setCompetitions(const vector<string> & competitions);
    const vector<string> & getCompetitions() const;
    string info();
    bool isAthlete(){return true;};
    //double getDailyCost();
};

class Team: public Participant{
private:
    vector<Athlete> athletes;
    string name;
    vector <string> competitions;
    //historial
public:
    Team (){};
    Team(const string &name, int ranking, const string & sport);
    const string &getName() const;
    void setName(const string &name);
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
    bool isAthlete(){return false;};
    //virtual double getDailyCost()=0;  //depende do tipo de funcionário
};

#endif //PROJECT_1_PERSON_H
