//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_MEDAL_H
#define PROJECT_1_MEDAL_H

#include <string>

using namespace std;

class Medal {
public:
    /**Trial Default Constructor*/
    Medal(){}

    /**Trial Constructor
     * @param type
     * @param
     * @param
     */
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
    char type;/**< The type of the medal - g(old), s(ilver), b(bronze) */
    string winner;/**< The name of the winner*/
    string country;/**< The country of the winner*/
};


#endif //PROJECT_1_MEDAL_H
