//
// Created by Diana Freitas on 15/10/2019.
//

#include "Person.h"
#include "Delegation.h"

//Person
Person::Person(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure) : name(
        name), birth(birth), passport(passport), arrival(arrival), departure(departure) {
}

Person::Person(){}

const string &Person::getName() const {
    return name;
}

void Person::setName(const string &name) {
    this->name = name;
}

const Date &Person::getBirth() const {
    return birth;
}

void Person::setBirth(const Date &birth) {
    this->birth = birth;
}

const string &Person::getPassport() const {
    return passport;
}

void Person::setPassport(const string &passport) {
    this->passport = passport;
}

const Date &Person::getArrival() const {
    return arrival;
}

void Person::setArrival(const Date &arrival) {
    this->arrival = arrival;
}

const Date &Person::getDeparture() const {
    return departure;
}

void Person::setDeparture(const Date &departure) {
    this->departure = departure;
}

string Person::info(){
    ostringstream os;
    os <<  left <<setw(17) << "Name" << setw(4) << " "<<  getName() << setw(3) <<endl;
    os <<  left <<setw(17) << "Birthday" << setw(4) << " "<< getBirth() << setw(3) <<endl;
    os <<  left <<setw(17) << "Passport" << setw(4) << " "<< getPassport() << setw(3) <<endl;
    os <<  left <<setw(17) << "Flight Arrival" << setw(4) << " "<<  getArrival() << setw(3) <<endl;
    os <<  left <<setw(17) << "Flight Departure" << setw(4) << " "<<getDeparture() << setw(3) <<endl;
    return os.str();
}

bool Person::operator<(const Person & p) const{
    if (this->isAthlete() && !(p.isAthlete())) return true;
    else if(p.isAthlete() && !(this->isAthlete())) return false;
    else return name < p.getName();
}

ostream & operator<<(ostream & os, const Person & p){
    os <<  left <<setw(17) << "Name" << setw(4) << " "<<  p.getName() << setw(3) <<endl;
    os <<  left <<setw(17) << "Birthday" << setw(4) << " "<< p.getBirth() << setw(3) <<endl;
    os <<  left <<setw(17) << "Passport" << setw(4) << " "<< p.getPassport() << setw(3) <<endl;
    os <<  left <<setw(17) << "Flight Arrival" << setw(4) << " "<<  p.getArrival() << setw(3) <<endl;
    os <<  left <<setw(17) << "Flight Departure" << setw(4) << " "<<p.getDeparture() << setw(3) <<endl;
    return os;
}

void Person::showInfoPerson() const{
    cout << (*this);
}

void Person::showInfo() const{
    showInfoPerson();
}

bool operator==(const Person & p1, const Person &p2){
    return p1.getName() == p2.getName();
}

//Staff

const string &Staff::getFunction() const {
    return function;
}

void Staff::setFunction(const string &function) {
    this->function = function;
}

Staff::Staff(const string &name, const Date &birth, const string &passport, const Date &arrival, const Date &departure,
             const string &function) : Person(name, birth, passport, arrival, departure), function(function) {}

Staff::Staff():Person(){}

Staff::Staff(const Staff & s) : Person(s.getName(), s.getBirth(), s.getPassport(), s.getArrival(), s.getDeparture()) {
    function = s.getFunction();
}

string Staff::info(){
    ostringstream os;
    os <<  left << Person::info();
    os <<  left << setw(17) << "Function" << setw(4) << " "<< function << setw(3) <<endl;
    return os.str();
}

void Staff::showInfoPerson() const{
    Person::showInfoPerson();
    cout << left << setw(17) << "Function" << setw(4) << " "<< function << setw(3) <<endl;
}

//Participant

const string & Participant::getSport() const {
    return sport;
}

void Participant::setSport(const string & sport) {
    this->sport = sport;
}

void Participant::setCompetitions(const vector<string> & competitions) {
    this->competitions = competitions;
}

const vector<string> & Participant::getCompetitions() const{
    return competitions;
}

//Athlete

Athlete::Athlete(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure, const string & sport, float weight,
                 float height) : Person(name, birth, passport, arrival, departure), weight(weight), height(height){ Participant::sport=sport;}


Athlete::Athlete(const Athlete & a): Person(a.getName(), a.getBirth(), a.getPassport(), a.getArrival(), a.getDeparture()){
    competitions = a.getCompetitions();
    sport=a.getSport();
    weight = a.getWeight();
    height = a.getHeight();
}

float Athlete::getWeight() const {
    return weight;
}

void Athlete::setWeight(float weight) {
    this->weight = weight;
}

float Athlete::getHeight() const {
    return height;
}

void Athlete::setHeight(float height) {
    this->height = height;
}

const string &Athlete::getName() const {
    return Person::getName();
}

void Athlete::setName(const string &name) {
    Person::setName(name);
}

string Athlete::info(){
    ostringstream os;
    os << Person::info();
    os <<  left <<setw(17) << "Sport" << setw(4) << " "<< getSport() <<endl;
    os <<  left <<setw(17) << "Competitions" <<setw(4) << " ";
    for(const auto & competition : competitions)
        os << competition<<" ";
    os << endl;
    os <<  left <<setw(17) << "Weight" <<setw(4) << " " << to_string(weight) <<endl;
    os <<  left <<setw(17) << "Height" <<  setw(4) << " " << to_string(height) <<endl;
    return os.str();
}

void Athlete::showInfoPerson() const{
    Person::showInfoPerson();
    cout << left << setw(17) << "Sport" << setw(4) << " "<< getSport() << setw(3) <<endl;

}

void Athlete::showInfo() const{
    showInfoPerson();
    cout <<  left <<setw(17) << "Competitions" <<setw(4) << " ";
    for(size_t i=0; i<competitions.size();i++){
        cout << competitions[i];
        if(i!=competitions.size()-1)
            cout <<", ";
    }
    cout << endl;
    cout <<  left <<setw(17) << "Weight" <<setw(4) << " " << to_string(weight) <<endl;
    cout <<  left <<setw(17) << "Height" <<  setw(4) << " " << to_string(height) <<endl;
}

bool Athlete::playsTeamSport(const Delegation & delegation) const{
    vector<Sport*> sports = delegation.getSports();
    for(size_t i=0; i<sports.size();i++){
        if(sports[i]->getName() == sport)
            if(sports[i]->isTeamSport())
                return true;
    }
    return false;
}
//Team

Team::Team(const string &name, const string &sport) : name(name) { Participant::sport = sport;}

const string &Team::getName() const {
    return name;
}

void Team::setName(const string &name) {
    this->name = name;
}

Team::Team(const Team & t){
    sport = t.getSport();
    competitions = t.getCompetitions();
    name = t.getName();
    athletes = t.getAthletes();
}

const vector<Athlete*> & Team::getAthletes() const{
    return athletes;
}

void Team::setAthletes(const vector<Athlete*> & a){
    athletes=a;
}

void Team::showInfo() const{
    cout << endl;
    cout <<  left <<setw(17) << "Team Name" <<  setw(4) << " " << name <<endl;
    cout << left << setw(17) << "Sport" << setw(4) << " "<< getSport() << setw(3) <<endl;
    cout <<  left <<setw(17) << "Competitions"<<  setw(4) << " ";
    for(size_t i= 0; i< competitions.size(); i++){
        cout << competitions[i];
        if( i != competitions.size()-1)
            cout << ", ";
    }
    cout << endl;
    cout <<  left <<setw(17) << "Members" <<  setw(4) << " ";
    for(size_t i= 0; i< athletes.size(); i++){
        cout << athletes[i]->getName();
        if( i != athletes.size()-1)
        cout << ", ";
    }
    cout << endl;
}

bool Team::operator<(const Team & p) const{
    return(name < p.getName());
}

void Team::addAthlete(Athlete* a) {
    athletes.push_back(a);
}

void Team::removeAthlete(string name) {
    vector<Athlete*>::iterator it;
    for(it = athletes.begin(); it != athletes.end(); it++){
        if((*it)->getName() == name) athletes.erase(it);
    }
}
