#ifndef PROJECT_1_SPORT_H
#define PROJECT_1_SPORT_H

#include "Competition.h"
#include "Person.h"

class Team;
class Athlete;
class Participant;

class Sport {
    string name;
    vector<Competition> competitions;
public:
    Sport(){};
    ~Sport();
    Sport(const string &name, const vector<Competition>  & competitions);
    const string & getName() const;
    void setName(const string & n);
    virtual const vector<Participant*> & getParticipants() const {return nullptr;};
    void setCompetitions(const vector<Competition> & competitions);
    const vector<Competition> & getCompetitions() const;
    void addCompetition(const Competition & c); //daqui para baixo provavelmente vão ser virtual por causa dos vetores de atletas e equipas
    void removeCompetition(const string & c);
    void updateCompetition(const string & c);
    void showCompetitions() const;
    void removeParticipant(const string & p);
    void updateParticipant(const string & p);
    void showParticipants() const;
    virtual string info() const;
};

class TeamSport: public Sport{
    vector<Team*> teams;
    unsigned int numberOfElements;
public:
    TeamSport(){}
    TeamSport(const TeamSport & s);
    void setParticipants(const vector<Team> & teams);
    const vector<Participant*> & getParticipants() const;
    void setNumberofElements(unsigned int n);
    void addTeam(Team* t);
    vector<Team*> getTeams() const;
};

class IndividualSport: public Sport{
    vector<Athlete*> athletes;
public:
    IndividualSport(const IndividualSport & s);
    IndividualSport(Sport * sport);
    void setParticipants(const vector<Athlete*> & athletes);
    const vector<Participant*> & getParticipants() const;
    void addAthlete(Athlete* a);
    vector<Athlete*> getAthletes() const;
};


#endif //PROJECT_1_SPORT_H
