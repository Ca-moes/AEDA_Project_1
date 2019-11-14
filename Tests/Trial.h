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

/**A class to store the information about a Trial*/
class Trial {
    string name;/**< The name of the Trial*/
    vector <string> participants;/**< The type of the medal - g(old), s(ilver), b(bronze) */
    string winner; /**< the name of the winner */
    Date date; /**< The day of the Trial*/
    unsigned int numberOfElements; /**< The number of competitors*/
public:
    /*Trial Default Constructor*/
    Trial(){};

    /**Trial Copy Constructor
     * @param t the Trial to copy
     */
    Trial(const Trial & t);

    /** Get the name of the Trial
    * @returns the name of the Trial
    */
    const string & getName() const;

    /** Get the winner of the Trial
    * @returns the winner of the Trial
    */
    const string & getWinner() const;

    /** Get the Date of the Trial
    * @returns the Date of the Trial
    */
    const Date & getDate() const;

    /** Get the participants of the Trial
    * @returns the participants of the Trial
    */
    const vector<string> & getParticipants() const;

    /**Set the winner of the Trial
     * @param w the winner of the Trial
     */
    void setWinner(const string &w);

    /**Set the Date of the Trial
     * @param dthe Date of the Trial
     */
    void setDate(const Date & d);

    /**Set the name of the Trial
     * @param n the name of the Trial
     */
    void setName(const string & n);

    /**Set the participants of the Trial
     * @param players the participants of the Trial
     */
    void setPlayers(const vector<string> & players);

    /** Get the number of participants of the Trial
    * @returns the number of participants of the Trial
    */
    unsigned int getNumberOfElements() const;

    /**Set the number of participants of the Trial
     * @param n the number of participants of the Trial
     */
    void setNumberOfElements(unsigned int n);

    /**Get the information about the Trial for testing purposes
    *@returns info about the Trial
    */
    string info() const;

    /** Shows information about the Trial in a human friendly way*/
    void showInfo() const;

    /** Shows information about the Trial in a human friendly way (without showing the Date)*/
    void showInfoNoDate() const;
};

/** Prints info about the Trial for testing purposes
   * @param os the name of the ostream
   * @param g Trial object
   * @returns reference to the original ostream to allow input/output chains
   */
ostream& operator<<(ostream& os, const Trial & g);

#endif //PROJECT_1_TRIAL_H
