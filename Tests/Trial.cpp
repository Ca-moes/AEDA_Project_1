//
// Created by Diana Freitas on 15/10/2019.
//

#include "Trial.h"
#include <iomanip>

const string & Trial::getName() const{
    return name;
}

const vector<string> & Trial::getParticipants() const{
    return participants;
}

Trial::Trial(const Trial & t){
    name = t.getName();
    date = t.getDate();
    winner = t.getWinner();
    numberOfElements = t.getNumberOfElements();
    participants = t.getParticipants();
}

const string & Trial::getWinner() const{
    return winner;
}

const Date & Trial::getDate() const{
    return date;
}

void Trial::setDate(const Date & d){
    date = d;
}

void Trial::setName(const string & n){
    name = n;
}

void Trial::setWinner(const string &w) {
    this->winner = w;
}

void Trial::setPlayers(const vector<string> & players){
    participants=players;
}

void Trial::setNumberOfElements(unsigned int n){
    numberOfElements = n;
}

unsigned int Trial::getNumberOfElements() const{
    return numberOfElements;
}

string Trial::info() const{
    ostringstream os;
    os <<  left <<setw(17) << "Name" << setw(4) << " "<< name <<endl;
    os <<  left <<setw(17) << "Date" <<setw(4) << " "<< date << endl;
    os <<  left <<setw(17) << "Participants" <<setw(4) << " ";
    for(const auto & participant : participants)
        os << participant <<" ";
    os << endl;
    os <<  left <<setw(17) << "Winner" << setw(4) << " "<< winner <<endl;
    os <<  left <<setw(17) << "Number of Elements" << setw(4) << " "<< numberOfElements <<endl;
    return os.str();
}

void Trial::showInfo() const{
    cout <<  left <<setw(17) << "Name" << setw(4) << " "<< name <<endl;
    cout <<  left <<setw(17) << "Date" <<setw(4) << " "<< date << endl;
    cout <<  left <<setw(17) << "Participants" <<setw(4) << " ";
    for(const auto & participant : participants)
        cout << participant <<" ";
    cout << endl;
    cout <<  left <<setw(17) << "Winner" << setw(4) << " "<< winner <<endl;
}

void Trial::showInfoNoDate() const{
    cout <<  left <<setw(17) << "Name" << setw(4) << " "<< name <<endl;
    cout <<  left <<setw(17) << "Participants" <<setw(4) << " ";
    for(const auto & participant : participants)
        cout << participant <<" ";
    cout << endl;
    cout <<  left <<setw(17) << "Winner" << setw(4) << " "<< winner <<endl;
}