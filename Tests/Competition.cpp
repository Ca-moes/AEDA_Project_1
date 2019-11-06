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

Competition::Competition(const Competition & c){
    name = c.getName();
    begin = c.getBegin();
    end = c.getEnd();
    trials = c.getTrials();
    medals = c.getMedals();
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

const vector<Medal> & Competition::getMedals() const {
    return medals;
}

void Competition::setName(const string &n) {
    this->name = n;
}

void Competition::setBegin(const Date &b) {
    this->begin = b;
}

void Competition::setEnd(const Date &e) {
    this->end = e;
}

void Competition::setTrials(const vector<Trial> & trials){
    this->trials = trials;
}

const vector<Trial> & Competition::getTrials() const{
    return trials;
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
    if(!trials.empty()){
        os <<  left <<setw(17) << "Trials" <<setw(4) << endl;
        for(const auto & trial : trials)
            os << trial.info()<<" ";
        os << endl;
    }
    os <<  left <<setw(17) << "Medals" << setw(4) <<endl;
    for(const auto & medal : getMedals())
        os << medal.info()<<" ";
    os << endl;
    return os.str();
}

ostream& operator<<(ostream& os, const Competition & c)
{
    os << c.getName() << "\n";
    return os;
}
