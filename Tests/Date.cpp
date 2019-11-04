//
// Created by Diana Freitas on 15/10/2019.
//

#include "Date.h"

Date::Date() {
    year=0, month=0, day =0;
}

Date::Date(string date) {

}

/**
 * Date constructor with int parameters
 *
 * @param day the day (1-2 digits)
 * @param month the month (1-2 digit)
 * @param year the year (1-4 digits)
 */
Date::Date(unsigned short day, unsigned short month, unsigned year) {
    this->day = day;
    this->month = month;
    this->year = year;
}


unsigned short int Date::getYear() const {
    return year;
}

void Date::setYear(int y) {
    year = y;
}

unsigned short int Date::getMonth() const {
    return month;
}

void Date::setMonth(int m) {
    month = m;
}

unsigned short int Date::getDay() const {
    return day;
}

void Date::setDay(int d) {
    day = d;
}

bool Date::validateDate() {
    if ((month >= 1) && (month <= 12) && (day <= 31) && (day >= 1) && (year >1900)) {
        if (month == 2) {
            if (leapYear()) {
                return day <= 29;
            }
            else {
                return day <= 28;
            }
        }
        else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
            return day <= 30;
        }
        else
            return true;
    }
    else
        return false;
}

bool Date::leapYear(){
    if (year % 400 == 0)
        return true;
    return (year % 4 == 0) && (year % 10 != 0);
}

bool Date::isOlimpianDate() {
    return ((month == 7 && day >= 24 && day <= 31) || (month == 8 && day >= 1 && day <= 9)) && (year == 2020);
}

int daysBetween(const Date begin, const Date end) {
    if(end.day < begin.day){
        return 32-begin.day + end.day;
    } else {
        return end.day - begin.day +1;
    }
}

ostream& operator<<(ostream& os, const Date & d){
    os << d.getDay() << "/" << d.getMonth() << "/" << d.getYear();
    return os;
}

//Exceptions
ostream & operator <<(ostream & os, InvalidDate & d){
    os << d.date << " is not a valid date \n";
    return os;
}

InvalidDate::InvalidDate(string date){
    this->date = date;
}