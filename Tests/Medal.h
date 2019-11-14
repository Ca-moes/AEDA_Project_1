//
// Created by Diana Freitas on 20/10/2019.
//

#ifndef PROJECT_1_MEDAL_H
#define PROJECT_1_MEDAL_H

#include <string>

using namespace std;

/**
 * A class to store the information about a Medal
 */
class Medal {
public:
    /**Trial Default Constructor*/
    Medal(){}

    /**Trial Constructor
     * @param type the type of the medal (g,s,b)
     * @param winner the winner of the medal
     * @param country the country of the winner
     */
    Medal(char type, const string & winner, const string &country);

    /** Get the type of the medal
    * @returns the type of the medal
    */
    char getType() const;

    /**Set the type of the medal
     * @param type the type of the medal
     */
    void setType(char type);

    /**
    * Get the name of the winner
    * @returns the name of the winner
    */
    string getWinner() const;

    /**
   * Set the name of the winner
   * @param winner the name of the winner
   */
    void setWinner(const string & winner);

    /**Get the country of the winner
    * @returns the country of the winner
    */
    const string &getCountry() const;

    /**
   * Set the country of the winner
   *@param country the country of the winner
   */
    void setCountry(const string &country);

    /**Get the information about the medal for testing purposes
    *@returns info about the medal
    */
    string info() const;

    /** Shows the information of a medal in a human friendly way*/
    void showInfo() const;

    /** Shows the type of a medal in a human friendly way*/
    void showType() const;

    /** Compares two medals
    * @param p The Medal to compare with
    * @returns true if this medal is better than the other
    */
    bool operator <(Medal & m);

    /** Compares two medals
    * @param p The Medal to compare with
    * @returns true if the country of this medal comes first in the alphabet than the other, false otherwise
    */
    bool operator >(Medal & m);

private:
    char type;/**< The type of the medal - g(old), s(ilver), b(bronze) */
    string winner;/**< The name of the winner*/
    string country;/**< The country of the winner*/
};


#endif //PROJECT_1_MEDAL_H
