#include "Competition.h"
#include "Trial.h"
#include "Date.h"


Competition::Competition(){
    name = "";
    begin = Date();
    end = Date();
}

/**
 * Competition Constructor
 *
 * @param name the name of the Competition
 * @param begin the begin Date of the Competition
 * @param end the begin Date of the Competition
 */
Competition::Competition(string name, Date begin, Date end){
    this->name = name;
    this->begin = begin;
    this ->end = end;
}

const Date & Competition::getBegin() const{
    return begin;
}

const Date & Competition::getEnd() const{
    return end;
}

const string &  Competition::getName() const{
    return name;
}

void Competition::setName(const string &n) {
    this->name = name;
}

void Competition::setBegin(const Date &b) {
    this->begin = begin;
}

void Competition::setEnd(const Date &e) {
    this->end = end;
}

void Competition::setTrial(const vector<Trial> & trials){
    this->trials=trials;
}

void Competition::setMedals(const vector<Medal> &medals){
    this->medals = medals;
}

void Competition::addTrial(const Trial & t){
}

void Competition::removeTrial(const string & t){}


void Competition::updateTrial(const string & t){}


void Competition::showTrials() const{}


void Competition::addParticipant(const string & p){}


void Competition::removeParticipant(const string & p){}


void Competition::updateParticipant(const string & p){}


void Competition::showParticipants() const{}


ostream& operator<<(ostream& os, const Competition & c)
{
    os << c.getName() << "\n";
    return os;
}
