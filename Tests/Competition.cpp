#include "Competition.h"
#include "Trial.h"
#include "Date.h"
#include <iomanip>


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

string Competition::info() const{
    ostringstream os;
    os <<  left <<setw(17) << "Name" << setw(4) << " "<<  getName() << setw(3) <<endl;
    os <<  left <<setw(17) << "Begin Date" << setw(4) << " "<< getBegin() << setw(3) <<endl;
    os <<  left <<setw(17) << "End Date" << setw(4) << " "<< getEnd() << setw(3) <<endl;
    for(const auto & trial : trials)
        os << trial.info()<<" ";
    os << endl;
    return os.str();
}

ostream& operator<<(ostream& os, const Competition & c)
{
    os << c.getName() << "\n";
    return os;
}
