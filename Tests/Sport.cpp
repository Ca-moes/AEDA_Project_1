#include "Sport.h"
#include <algorithm>

using namespace std;

//Sport
Sport::~Sport(){
}

Sport::Sport(const string &name, const vector<Competition>  & competitions){
    this->name = name;
    this->competitions = competitions;
}

const string & Sport::getName() const{
    return name;
}

void Sport::setName(string n){
    name = n;
}

void Sport::setCompetitions(const vector<Competition> & comps){
    this->competitions=vector<Competition>(comps);
}

vector<Competition> Sport::getCompetitions() const{
    return competitions;
}

bool operator== (const Sport & s1,const Sport & s2){
    return s1.name == s2.name;
}

string Sport::info() const{
    ostringstream os;
    os <<  left <<setw(17) << "Name" << setw(4) << " "<<  getName() << setw(3) <<endl;
    os <<  left <<setw(17) << "Competitions" <<setw(4) << endl;
    for(const auto & competition : competitions){
        os << competition.info() <<" ";
        os << endl;
    }
    os<< endl<<endl;
    return os.str();
}

bool Sport::operator < (const Sport & left) const{
    return name < left.getName();
}

//Team Sport
void TeamSport::setNumberofElements(unsigned int n){
    numberOfElements = n;
}

TeamSport::TeamSport(const TeamSport & s) : Sport(s.getName(), s.getCompetitions()){
    vector<Team *>::iterator it;
    if(!s.getTeams().empty()) {
        vector<Team *> t = s.getTeams();
        for (it = t.begin(); it != t.end(); it++) {
            Team *t = new Team(*(*it));
            teams.push_back(t);
        }
    }
    numberOfElements = s.getNumberofElements();
}

void TeamSport::setParticipants(const vector<Team> & tems){
    this->teams = teams;
}

vector<Participant*> TeamSport::getParticipants() const{
    vector<Participant*> p;
    vector<Team*>::const_iterator it;
    for(it = teams.begin() ; it != teams.end() ; it++)
        p.push_back(*it);
    return p;
}

void TeamSport::addTeam(Team* t){
    teams.push_back(t);
}

vector<Team*> TeamSport::getTeams() const{
    return teams;
}

unsigned int TeamSport::getNumberofElements() const{
    return numberOfElements;
}

//Individual Sport
void IndividualSport::setParticipants(const vector<Athlete *> & athletes){
    this->athletes = athletes;
}

IndividualSport::IndividualSport(const IndividualSport & s) : Sport(s.getName(), s.getCompetitions()) {
    vector<Athlete *>::iterator it;
    if(!s.getAthletes().empty()){
        vector<Athlete *> v = s.getAthletes();
        for(it = v.begin(); it != v.end(); it++){
            Athlete * a = new Athlete(*(*it));
            athletes.push_back(a);
        }
    }
}

vector<Participant*> IndividualSport::getParticipants() const{
    vector<Participant*> p;
    vector<Athlete*>::const_iterator it;
    for(it = athletes.begin() ; it != athletes.end() ; it++)
        p.push_back(*it);
    return p;
}

void  IndividualSport::addAthlete(Athlete* a){
    athletes.push_back(a);
}

vector<Athlete*> IndividualSport::getAthletes() const{
    return athletes;
}