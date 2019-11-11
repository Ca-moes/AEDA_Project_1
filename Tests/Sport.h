#ifndef PROJECT_1_SPORT_H
#define PROJECT_1_SPORT_H

#include "Competition.h"
#include "Person.h"

class Team;
class Athlete;
class Participant;

class Sport {
protected:
    vector<Competition> competitions;
public:
    string name;
    Sport(){};
    ~Sport();
    Sport(const string &name, const vector<Competition>  & competitions);
    const string & getName() const;
    void setName(string n);
    virtual vector<Participant*> getParticipants() const{vector<Participant*> p; return p;};
    void setCompetitions(const vector<Competition> & competitions);
    const vector<Competition> & getCompetitions() const;
    virtual string info() const;
    virtual bool isTeamSport(){return false;};
    bool operator < (const Sport & left) const;
    friend bool operator== (const Sport & s1,const Sport & s2 );
};

class TeamSport: public Sport{
    vector<Team*> teams;
    unsigned int numberOfElements{};
public:
    ~TeamSport(){};
    TeamSport(){}
    TeamSport(const TeamSport & s);
    void setParticipants(const vector<Team> & teams);
    vector<Participant*> getParticipants() const;
    void setNumberofElements(unsigned int n);
    unsigned int getNumberofElements() const;
    void addTeam(Team* t);
    vector<Team*> getTeams() const;
    bool isTeamSport(){return true;};
};

class IndividualSport: public Sport{
    vector<Athlete*> athletes;
public:
    ~IndividualSport(){};
    IndividualSport(const IndividualSport & s);
    IndividualSport(){};
    void setParticipants(const vector<Athlete*> & athletes);
    vector<Participant*> getParticipants() const;
    void addAthlete(Athlete* a);
    vector<Athlete*> getAthletes() const;
    bool isTeamSport(){return false;};
};


#endif //PROJECT_1_SPORT_H
