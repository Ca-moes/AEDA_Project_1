//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_COMPETITION_H
#define PROJECT_1_COMPETITION_H

#include "Trial.h"
#include "Medal.h"
#include <vector>
#include <map>

/**A class to store the information about a Competition*/
class Competition {
    string name; /**< Name of the competition*/
    Date begin; /**< Begin date of the Competition*/
    Date end; /**< End date of the Competition*/
    vector<Trial> trials; /**< list of the trials*/
    vector<Medal> medals; /**< list of medals */
    vector<string> participants;/**< List of the participants*/
public:
    /** Competition Default Constructor*/
    Competition();

    /** Competition copy constructor
     * @param c the Competition to copy
     */
    Competition(const Competition & c);

    /** new competition with specific data
     * @param name the name of the competition
     * @param begin the begin Date
     * @param end the end Date
     */
    Competition(string name, Date begin, Date end);

    /**
    * Get the Competition's Begin Date
    *
    * @returns the Competition's Begin Date
    */
    const Date & getBegin() const;

    /**
    * Get the Competition's End Date
    *
    * @returns the Competition's End Date
    */
    const Date & getEnd() const;

    /**
    * Get the Competition's name
    *
    * @returns the Competition's name
    */
    const string & getName() const;

    /**
    * Set the Competition's name
    *
    * @param n the Competition's name
    */
    void setName(const string &n);

    /**
    * Set the Competition's begin Date
    *
    * @param b the Delegation's begin Date
    */
    void setBegin(const Date &b);

    /**
    * Set the Competition's name
    *
    * @param e the Delegation's end Date
    */
    void setEnd(const Date &e);

    /**
    * Set the Competition's Medals
    *
    * @param medals the Medals list
    */
    void setMedals(const vector<Medal> &medals);

    /**
    * Get the Competition's medals
    *
    * @returns the Competition's Medals
    */
    const vector<Medal> & getMedals() const;

    /**
    * Set the Competition's trials
    *
    * @param trials the Competition's trials
    */
    void setTrials(const vector<Trial> & trials);

    /**
    * Get the Competition's trials
    *
    * @returns the Competition's trials
    */
    const vector<Trial> & getTrials() const;

    /**
    * Add athlete to the Competition
    *
    * @param p the athlete's name
    */
    void addParticipant(const string & p);

    /**
    * Set the Participants of the competition
    *
    * @param n the participants
    */
    void setParticipants(const vector<string> & p);

    /**
    * Get the Participants of the competition
    *
    * @returns the participants
    */
    vector<string> getParticipants();

    /** Show info about the competition in an user friendly way*/
    void showInfo() const;

    /**Show the medals of the competition in an user friendly way*/
    void showMedals() const;

    /**Get the Information about the Competition in a string for testing purposes
     *
     * @returns the information about the competition
     */
    string info() const;
};

/** Shows the name of the Competition for testing purposes
 * @param os the name of ostream
 * @param c the competition object
 * @returns reference to the original ostream to allow input/output chains
 */
ostream& operator<<(ostream& os, const Competition & c);

#endif //PROJECT_1_COMPETITION_H
