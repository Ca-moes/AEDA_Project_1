//
// Created by Diana Freitas on 15/10/2019.
//

#include "Trial.h"

const string & Trial::getName() const{
    return name;
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
    this->winner = winner;
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