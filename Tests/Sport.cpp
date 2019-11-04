#include "Sport.h"
#include <algorithm>

using namespace std;

Sport::~Sport(){}

const string & Sport::getName() const{
    return name;
}

void Sport::setName(const string & n){
    name = n;
}

void Sport::addCompetition(const Competition & c){

}

void Sport::removeCompetition(const string & c){

}

void Sport::updateCompetition(const string & c){

}

void Sport::showCompetitions() const{

}


void Sport::removeParticipant(const string & p){

}

void Sport::updateParticipant(const string & p){

}

void Sport::showParticipants() const{

}

void Sport::setCompetitions(const vector<Competition> & competitions){
    this->competitions=competitions;
}

void TeamSport::setNumberofElements(unsigned int n){
    numberOfElements = n;
}

void TeamSport::setParticipants(const vector<Team> & tems){
    this->teams = teams;
}

const vector<Participant*> & TeamSport::getParticipants() const{
    vector<Participant*> p;
    vector<Team*>::const_iterator it;
    for(it = teams.begin() ; it != teams.end() ; it++)
        p.push_back(*it);
    return p;
}

void TeamSport::addTeam(Team* t){
    teams.push_back(t);
}

void IndividualSport::setParticipants(const vector<Athlete *> & athletes){
    this->athletes = athletes;
}

const vector<Participant*> & IndividualSport::getParticipants() const{
    vector<Participant*> p;
    vector<Athlete*>::const_iterator it;
    for(it = athletes.begin() ; it != athletes.end() ; it++)
        p.push_back(*it);
    return p;
}

void  IndividualSport::addAthlete(Athlete* a){
    athletes.push_back(a);
}