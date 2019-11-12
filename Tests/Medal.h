//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_MEDAL_H
#define PROJECT_1_MEDAL_H

#include <string>

using namespace std;

class Medal {
public:
    Medal(){}
    Medal(char type, const string & winner, const string &country);

    char getType() const;

    void setType(char type);

    string getWinner() const;

    void setWinner(const string & winner);

    const string &getCountry() const;

    void setCountry(const string &country);

    string info() const;

    void showInfo() const;

    void showType() const;

    bool operator <(Medal & m);

    bool operator >(Medal & m);

private:
    char type;
    string winner;
    string country;
};


#endif //PROJECT_1_MEDAL_H
