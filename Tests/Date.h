//
// Created by Diana Freitas on 15/10/2019.
//

#ifndef PROJECT_1_DATE_H
#define PROJECT_1_DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date {
public:
    Date();
    Date(string date);
    Date(unsigned short day, unsigned short month, unsigned year);
    unsigned short int getYear() const;
    void setYear(int y);
    unsigned short int getMonth() const;
    void setMonth(int m);
    unsigned short int getDay() const;
    void setDay(int d);
    bool validateDate();
    bool isOlimpianDate();
    bool leapYear();
private:
    unsigned short int year;
    unsigned short int month;
    unsigned short int day;
};

ostream& operator<<(ostream& os, const Date & d);

//Exceptions

class InvalidDate{
    string date;
public:
    friend ostream & operator <<(ostream & os, InvalidDate & d);
    explicit InvalidDate(string date);
};




#endif //PROJECT_1_DATE_H
