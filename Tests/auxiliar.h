//
// Created by Diana Freitas on 23/10/2019.
//

#ifndef PROJECT_1_INPUTCHECK_H
#define PROJECT_1_INPUTCHECK_H

#include <string>
#include <regex>
#include "Date.h"

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

#endif //PROJECT_1_INPUTCHECK_H
