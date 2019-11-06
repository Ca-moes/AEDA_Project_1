//
// Created by Diana Freitas on 20/10/2019.
//

#include "Medal.h"
#include <iomanip>


Medal::Medal(char type, const string & winner, const string &country):type(type), winner(winner),
                                                                                country(country) {}


char Medal::getType() const {
    return type;
}


void Medal::setType(char type) {
    Medal::type = type;
}


string Medal::getWinner() const {
    return winner;
}


void Medal::setWinner(const string & winner) {
    Medal::winner = winner;
}


const string &Medal::getCountry() const {
    return country;
}


void Medal::setCountry(const string &country) {
    Medal::country = country;
}

string Medal::info() const{
    ostringstream os;
    os <<  left <<setw(17) << "Type" << setw(4) << " "<<  type << setw(3) <<endl;
    os <<  left <<setw(17) << "Winner" << setw(4) << " "<< winner << setw(3) <<endl;
    os <<  left <<setw(17) << "Country" << setw(4) << " "<< country << setw(3) <<endl;
    return os.str();
}