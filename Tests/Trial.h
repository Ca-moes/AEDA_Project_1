//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_TRIAL_H
#define PROJECT_1_TRIAL_H


#include <vector>
#include <iostream>
#include "Date.h"
#include <map>

using namespace std;

class Trial {
    string name;
    vector <string> participants;
    string winner; /**< the name of the winner */
    Date date;
    unsigned int numberOfElements;
public:
    Trial(){};
    Trial(const Trial & t);
    const string & getName() const;
    const string & getWinner() const;
    const Date & getDate() const;
    const vector<string> & getParticipants() const;
    void setWinner(const string &w);
    void setDate(const Date & d);
    void setName(const string & n);
    void setPlayers(const vector<string> & players);
    unsigned int getNumberOfElements() const;
    void setNumberOfElements(unsigned int n);
    string info() const;
};

ostream& operator<<(ostream& os, const Trial & g);

#endif //PROJECT_1_TRIAL_H
