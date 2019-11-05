//
// Created by Diana Freitas on 15/10/2019.
//

#include "Person.h"

//Person
Person::Person(const string &name, const Date &birth, const string & passport, const Date &arrival, const Date &departure) : name(
        name), birth(birth), passport(passport), arrival(arrival), departure(departure) {}

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

//Participant

Participant::Participant(const string & sport) : sport(sport){}

/*unsigned int Participant::getRanking() const {
    return ranking;
}

void Participant::setRanking(int ranking) {
    this->ranking = ranking;
}*/

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
                 float height) : Person(name, birth, passport, arrival, departure), Participant(sport), weight(weight), height(height){}

Athlete::Athlete() : Person(){
}

Athlete::Athlete(const Athlete & a) : Person(a.getName(), a.getBirth(), a.getPassport(), a.getArrival(), a.getDeparture()), Participant(a.getSport()){
    weight = a.getWeight();
    height = a.getHeight();
    competitions = a.getCompetitions();
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
    //os <<  left <<setw(17) << "Ranking" <<  setw(4) << " " << to_string(getRanking()) <<endl;
    return os.str();
}

//Team

Team::Team(const string &name, const string &sport) : Participant(sport), name(name) {}

const string &Team::getName() const {
    return name;
}

void Team::setName(const string &name) {
    this->name = name;
}

Team::Team(const Team & t) : Participant(t.getSport()){
    name = t.getName();
    competitions = t.getCompetitions();
    for(size_t i = 0; i< t.getAthletes().size();i++)
        athletes.push_back(t.getAthletes()[i]);
}

const vector<Athlete> & Team::getAthletes() const{
    return athletes;
}