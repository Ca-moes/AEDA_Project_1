//
// Created by Diana Freitas on 23/10/2019.
//

#ifndef PROJECT_1_INPUTCHECK_H
#define PROJECT_1_INPUTCHECK_H

#include <string>
#include <regex>
#include "Date.h"
#include "Person.h"

using namespace std;

/**
* Check if the wrong type was assigned to a variable by input or when reading a file line
*
* @returns 0 if type is valid and 1 otherwise
*/
int checkInvalidType(istream & in);

/**
* Check if a string is valid : non empty and non numeric
*
* @returns 0 if string is valid and 1 otherwise
*/
int checkStringInput(string & str);

/**
* Check if a string is alphanumeric : non empty and with no symbols
*
* @returns 0 if string is valid and 1 otherwise
*/
int checkAlphaNumericInput(string & str);

/**
* Check if a string can be converted to float
*
* @returns 0 if the string is convertible to float
*/
int checkFloatInput(string & st);

/**
* Check if a date is in the format dd/mm/yyyy
*
*
* @param date the date string
 * @param d the Date object to set with the day, month and year if the format is correct
*
* @returns 0 if the date is in the right format
*/
int checkDateInput(string date, Date & d);

/**
* Check if a string can be converted to an int
*
* @returns 0 if the string is convertible to an int
*/
int checkPositiveIntInput(string & str);

/**
 * Transforms a the file's lines to a vector
 *
 * @param in the stream with the file's lines
 * @returns the vector with the file's lines
 */

vector<string> fileToLineVector(istream & in);

/**
 * Counts the days between (and including) two dates
 *
 * @param begin the date of beginning
 * @param end the date of ending
 * @returns the numbers of days
 */
int daysBetween(const Date begin, const Date end);

/**
 * Compares two objects of a class - must have < operator
 *
 * @param p1 right object
 * @param p2 left object
 * @returns true if p1<p2, false otherwise
 */
template <class T>
bool sortMembersAlphabetically(const T * p1, const T * p2){
    return (*p1) < (*p2);
}

/**
 * Deletes repeted elements from vector of objects with == and < operators defined
 *
 * @param v1 the vector to be changed
 */
template <class T>
void noRepeatVector (vector<T> & v1){
    typename vector<string>::iterator it;
    sort(v1.begin(), v1.end());
    it = unique(v1.begin(), v1.end());
    v1.resize(distance(v1.begin(), it));
}

/**Handles an exception thrown in menus by showing the option to go back to the previous menu*/
void exceptionHandler();

/**
 * Compares two competitions, allowing to order a vector of competitions by Begin Date (End Date and Alphabetically if needed)
 *
 * @param c1 competition 1
 * @param c2 competition 2
 * @returns true if c1 begins after c2 / if they begin in the same day and c1 ends earlier/ if they begin and end in the same day and c1's name comes first in the alphabet
 */
bool sortCompetitionsByDate(const Competition & c1, const Competition & c2);

/**
 * Compares two trials, allowing to order a vector of trials by date or name if the dates are the same
 *
 * @param t1 trial 1
 * @param t2 trial 2
 * @returns true if t1 begins after t2 / if they begin in the same day and c1 comes first in the alphabet, false otherwise
 */
bool sortTrialsByDate(const Trial & t1, const Trial & t2);
#endif //PROJECT_1_INPUTCHECK_H
