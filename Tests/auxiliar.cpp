#include <iostream>
#include "auxiliar.h"
#include "Menus.h"

int checkInvalidType(istream & in){
    if (in.eof()) {
        in.clear();
        in.ignore(1000, '\n');
        return 1;
    }
    return 0;
}

int checkStringInput(string & str) {
    //check if the string is empty
    if (str.empty())
        return 1;
    //check for numeric values that make the string invalid
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
            return 1;
    }
    return 0;
}

int checkAlphaNumericInput(string & str){
    //check if the string is empty
    if (str.empty()) return 1;

    //check for non alphanumeric values that make the string invalid
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (!isalnum(str[i]) && str[i] != ' ') return 1;
    }
    return 0;
}

int checkFloatInput(string & str) {
    //check if the string is empty
    try{
        float n= stof(str);
    }
    catch(invalid_argument & e){
        return 1;
    }
    return 0;
}

int checkDateInput(string date, Date & d){
    istringstream ss(date);
    unsigned int day,month,year;
    char c1,c2;

    try{
        ss >> day >> c1 >> month >> c2 >> year;
    }
    catch(invalid_argument const &e){
        return 1;
    }
    catch(out_of_range const &e){
        return 1;
    }

    d = Date(day,month,year);

    if(!d.validateDate())
        return 1;

    return 0;
}

int checkPositiveIntInput(string & str){
    //check if the string is empty
    try{
        int n= stoi(str);
    }
    catch(invalid_argument & e){
        return 1;
    }
    catch( out_of_range & e){
        return 1;
    }
    //se for float
    if(stof(str)-stoi(str) != 0)
        return 1;
    //se for negativo
    if(stoi(str)<0)
        return 1;
    return 0;
}

vector<string> fileToLineVector(istream & in){
    vector<string> v;
    string str;

    while(getline(in, str))
        v.push_back(regex_replace(str, regex("^ +| +$|( ) +"), "$1"));

    return v;
}

int daysBetween(const Date begin, const Date end) {
    if(end.getDay() < begin.getDay()){
        return 32-begin.getDay() + end.getDay();
    } else {
        return end.getDay() - begin.getDay() +1;
    }
}

void exceptionHandler(){
    int test = 0;
    string input = "";

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

bool sortCompetitionsByDate(const Competition & c1, const Competition & c2){
    return(c1.getBegin() < c2.getBegin());
}

bool sortPersons(const Person * p1, const Person * p2){
    return (*p1) < (*p2);
}