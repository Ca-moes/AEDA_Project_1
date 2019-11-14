//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_DATE_H
#define PROJECT_1_DATE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * A class to store a Date
 */
class Date {
public:
    /** Date Default Constructor*/
    Date();

    /** Date Constructor - construct a date from a string
     * @param date with a specific format*/
    Date(string date);

    /** Delegation Constructor - construct a date from ints
     * @param day,month,year the data to construct the Date Object*/
    Date(unsigned short day, unsigned short month, unsigned year);

    /**
   * Get the year of the date
   * @returns the year
   */
    unsigned short int getYear() const;

    /**
   * Set the year of the date
   * @param y the year
   */
    void setYear(int y);

    /**
   * Get the month of the date
   * @returns the month
   */
    unsigned short int getMonth() const;

    /**
   * Set the month of the date
   * @param m the month
   */
    void setMonth(int m);

    /**
   * Get the day of the date
   * @returns the day
   */
    unsigned short int getDay() const;

    /**
  * Set the day of the date
  * @param d the day
  */
    void setDay(int d);

    /**
    * Validate a date
    * @returns true if the date is valid
    */
    bool validateDate();

    /**
    * Check if a date is between the begin Date and the end Date of the Olympics
    * @returns true if the date is between the begin Date and the end Date of the Olympics
    */
    bool isOlimpianDate();

    /**
    * Check if a year is a leap year
    * @returns true if the year is a leap year
    */
    bool leapYear();

    /** Calculates the number of days between two dates, including both dates
    * @param begin The begin date
    * @param end The end date
    * @returns the number of days between begin and end dates(including both dates)
    */
    friend int daysBetween(const Date begin, const Date end);

    /** Compares two dates to check which of them comes first
    * @param d The date to compare with
    * @returns true if the left date(this date) comes before the other(right date)
    */
    bool operator <(const Date & d) const;

    /** Checks if two dates are the same
    * @param d The date to compare with
    * @returns true if this date is the same as the other
    */
    bool operator ==(const Date & d) const;
private:
    unsigned short int year;/**< The year*/
    unsigned short int month;/**< The month*/
    unsigned short int day;/**< The day*/
};

/** Used to print the date
   * @param os the name of the ostream
   * @param d Date object
   * @returns reference to the original ostream to allow input/output chains
   */
ostream& operator<<(ostream& os, const Date & d);

#endif //PROJECT_1_DATE_H
