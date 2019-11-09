//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_COMPETITION_H
#define PROJECT_1_COMPETITION_H

#include "Trial.h"
#include "Medal.h"
#include <vector>
#include <map>

class Competition {
    string name;
    Date begin;
    Date end;
    vector<Trial> trials;
    vector<Medal> medals;
public:
    Competition();
    Competition(const Competition & c);
    Competition(string name, Date begin, Date end);
    const Date & getBegin() const;
    const Date & getEnd() const;
    const string & getName() const;
    void setName(const string &n);
    void setBegin(const Date &b);
    void setEnd(const Date &e);
    void setMedals(const vector<Medal> &medals);
    const vector<Medal> & getMedals() const;
    void setTrials(const vector<Trial> & trials);
    const vector<Trial> & getTrials() const;
    void addTrial(const Trial & t);
    void removeTrial(const string & t);
    void updateTrial(const string & t);
    void showTrials() const;
    void addParticipant(const string & p);
    void removeParticipant(const string & p);//Alterar - para participantes indicar passaporte e para equipas o nome?
    void updateParticipant(const string & p);//Alterar - para participantes indicar passaporte e para equipas o nome?
    void showParticipants() const;
    string info() const;
};

template <class Participant>
ostream& operator<<(ostream& os, const Competition & c);

#endif //PROJECT_1_COMPETITION_H
