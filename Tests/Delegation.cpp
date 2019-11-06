//
// Created by Diana Freitas on 20/10/2019.
//

#include "Delegation.h"
#include "auxiliar.h"
#include "Menus.h"
#include <regex>
#include <sstream>
#include <utility>

Delegation::Delegation(){
    try{
        readDelegationFile();
    }
    catch(FileError & e){
        cout << e << endl;
        throw;
    }
    catch(FileStructureError & s){
        cout << s << endl;
        throw;
    }

    mainMenu(*this);
}

void Delegation::readDelegationFile(){
    int numline = 0;
    string line,file;
    ifstream delegationFile;
    cout << "Delegation .txt File: ";
    // Falta checar inputs;
    cin >> file;
    file += ".txt";
    delegationFile.open(file);
    if(delegationFile.fail())
        throw FileError(file);

    while (getline(delegationFile, line))
    {
        numline++;
        switch (numline)
        {
            case 1:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
                if(checkStringInput(line) != 0)
                    throw FileStructureError(file);
                setCountry(line);
                break;
            case 2:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if(checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setDailyCostAthlete(stof(line));
                break;
            case 3:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if(checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setDailyCostStaff(stof(line));
                break;
            case 4:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if(checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setTotalCost(stof(line));
                break;
            case 5:
                peopleFilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if(checkStringInput(line) != 0)
                    throw FileStructureError(file);
                break;
            case 6:
                competitionsFilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if(checkStringInput(line) != 0)
                    throw FileStructureError(file);
                break;
            default:
                throw FileStructureError(file);
        }
    }
    delegationFile.close();
    delegationFile.clear();
    //Read people file
    delegationFile.open(peopleFilename+".txt");
    if(delegationFile.fail())
        throw FileError(peopleFilename+".txt");
    readPeopleFile(fileToLineVector(delegationFile));
    delegationFile.close();
    delegationFile.clear();
    //for testing purposes
    //print delegation info
    //cout << info();
    //print people
    //for(size_t i = 0; i< people.size(); i++)
        //cout << (people[i])->info() << endl;

    //Read teams file - necessário ler mais uma linha no ficheiro da delegação(adicionar no ficheiro), completar ficheiro das equipas e criar função para as ler
    //delegationFile.open(peopleFilename+".txt");
    //if(delegationFile.fail())
        //throw FileError(peopleFilename+".txt");
    //readPeopleFile(fileToLineVector(delegationFile));
    //delegationFile.close();
    //delegationFile.clear();

    //Read competitions file
    delegationFile.open(competitionsFilename+".txt");
    if(delegationFile.fail()) {
        throw FileError(competitionsFilename + ".txt");
    }
    readCompetitionsFile(fileToLineVector(delegationFile));
    delegationFile.clear();

    //for testing purposes - print sports
    //for(auto & sport : sports)
        //cout << sport->info()<<endl;
}

void Delegation::readPeopleFile(const vector<string> & lines) {
    int numline=0;
    string line;
    Date d;
    bool readFunc = false;
    Athlete *a;
    Staff *s;
    //Variables to read Competitions:
    istringstream competitionsStream;
    string compStr;
    vector<string> competitions;

    for(size_t i=0; i < lines.size(); i++){
        numline++;
        line = lines[i];

        if(line.empty()){ // Se alinha está vazia voltamos a colocar o numLines a 0 para ler a próxima pessoa
            numline = 1;
            i++;
            line = lines[i];
        }

        if(numline == 1){ // se for a primeira linha de uma pessoa vamos ver se é funcionário ou atleta
            readFunc = lines[i + 6].empty();
            competitions.resize(0);
            a=new Athlete();
            s=new Staff();
            competitionsStream.clear();
        }

        //ler atleta ou funcionario
        if(!readFunc){ // se tiver mais de 6 linha estamos perante um atleta
            //ler atleta
            switch (numline)
            {
                case 1:
                    if(checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setName(line);
                    break;
                case 2:
                    if(checkDateInput(line, d) != 0) //just needs to check the format and set variables(in class date there is a function to check the validity)
                        throw FileStructureError(peopleFilename);
                    a->setBirth(d);
                    break;
                case 3:
                    //if(checkStringInput(line) != 0) // create a function to check passport's formats
                        //throw FileStructureError(peopleFilename);
                    a->setPassport(line);
                    break;
                case 4:
                    if(checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if(d.isOlimpianDate()) {
                        a->setArrival(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 5:
                    if(checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if(d.isOlimpianDate()) {
                        a->setDeparture(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 6:
                    if(checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setSport(line);
                    break;
                case 7:
                    //ler competições - confirmar estrutura
                    competitionsStream.str(line);
                    while (getline(competitionsStream, compStr, ' '))
                        competitions.push_back(compStr);
                    a->setCompetitions(competitions);
                    break;
                case 8:
                    if(checkFloatInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setWeight(stof(line));
                    break;
                case 9:
                    if(checkFloatInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setHeight(stof(line));
                    people.push_back(new Athlete(*a));
                    athletes.push_back(new Athlete(*a));
                    break;
                default:
                    throw FileStructureError(peopleFilename);
            }

        }
        else{
            switch (numline)
            {
                case 1:
                    if(checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    s->setName(line);
                    break;
                case 2:
                    if(checkDateInput(line, d) != 0) //just needs to check the format and set variables(in class date there is a function to check the validity)
                        throw FileStructureError(peopleFilename);
                    s->setBirth(d);
                    break;
                case 3:
                    //if(checkStringInput(line) != 0) // create a function to check passport's formats
                    //throw FileStructureError(peopleFilename);
                    s->setPassport(line);
                    break;
                case 4:
                    if(checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if(d.isOlimpianDate()) {
                        s->setArrival(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 5:
                    if(checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if(d.isOlimpianDate()) {
                        s->setDeparture(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 6:
                    if(checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    s->setFunction(line);
                    people.push_back(new Staff(*s));
                    break;
                default:
                    throw FileStructureError(peopleFilename);
            }
        }
    }
}

void Delegation::readCompetitionsFile(const vector<string> & lines) {
    int numline = 0;
    string line;
    Date d;
    char read = 's'; // auxiliar para saber se vamos ler um sport, uma competition ou um trial (s,c ou t)
    //objects to create a sport
    bool isTeamSport = false;
    TeamSport *teamSport;
    IndividualSport *individualSport;
    string name, participant, pCountry;
    Competition competition;
    vector<Competition> competitions;
    istringstream participantsStream;
    vector<Medal> medals;
    Medal medal;
    int medalCount = 0;
    Trial trial;
    vector<string> trialPlayers;
    vector<Trial> trials;
    for (size_t i = 0; i < lines.size()+1; i++) {
        if(i!=lines.size())
            line = lines[i];
        numline++;

        if (numline == 1) {// se for a primeira linha de uma pessoa vamos ver se é uma nova modalidade, competição ou jogo
            if (line.empty()) {// Se alinha está vazia vamos ler a próxima competição
                if (read == 'c' || read == 't') {
                    if (read == 't'){
                        for(auto &athlete :athletes){
                           for(auto & comp : athlete->getCompetitions()){
                               if(comp == competition.getName())
                                   competition.addParticipant(athlete->getName());
                           }
                        }
                        competition.setTrials(trials);
                    }
                    competition.setMedals(medals);
                    competitions.push_back(competition);
                    medals.resize(0);
                }
                read = 'c';
                i++;
                numline = 1;
                line = lines[i];
            } else if (line =="////////" || i==lines.size()){//novo desporto - guardar os dados das competições e jogos e limpar variáveis auxiliares; ou útlima linha do ficheiro
                if (read == 't' || read == 'c')
                    competitions.push_back(competition);
                if (isTeamSport){
                    teamSport->setCompetitions(competitions);
                    for (auto &team : teams) {
                        if (team->getSport() == teamSport->getName())
                            teamSport->addTeam(team);
                    }
                    sports.push_back(new TeamSport(*teamSport));
                    competitions.resize(0);
                    trials.resize(0);
                    medals.resize(0);
                } else {
                    individualSport->setCompetitions(competitions);
                    for (auto &athlete : athletes) {
                        if (athlete->getSport() == individualSport->getName())
                            individualSport->addAthlete(athlete);
                    }
                    sports.push_back(new IndividualSport(*individualSport));
                }
                if(lines.size() == i) break;
                read = 's';
                numline = 1;
                i++;
                line = lines[i];
            } else if (line == "//") { //novo trial
                read = 't';
                numline = 1;
                i++;
                line = lines[i];
                trialPlayers.resize(0);
            }
        }
        //ler sport
        if (read == 's') {
            switch (numline) {
                case 1:
                    if (checkStringInput(line) != 0)
                        throw FileStructureError(competitionsFilename);
                    name = line;
                    break;
                case 2:
                    if (checkPositiveIntInput(line) != 0) //check int input
                        throw FileStructureError(competitionsFilename);
                    if (stoi(line) == 1) {
                        //individual sport
                        individualSport = new IndividualSport();
                        individualSport->setName(name);
                        isTeamSport = false;
                    } else if (stoi(line) > 1) {
                        //team Sport
                        teamSport = new TeamSport();
                        teamSport->setName(name);
                        teamSport->setNumberofElements(stoi(line));
                        isTeamSport = true;
                    } else // se for 0
                        throw FileStructureError(competitionsFilename);
                    numline = 0;
                    break;
                default:
                    throw FileStructureError(competitionsFilename);
            }
        }
        //ler competição
        if (read == 'c') {
            switch (numline) {
                case 1:
                    competition.setName(line);
                    break;
                case 2:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(competitionsFilename);
                    if (d.isOlimpianDate())
                        competition.setBegin(d);
                    else
                        throw FileStructureError(peopleFilename);
                    break;
                case 3:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(competitionsFilename);
                    if (d.isOlimpianDate()) {
                        competition.setEnd(d);
                    } else {
                        throw FileStructureError(competitionsFilename);
                    }
                    break;
                case 4:
                    //ler competições - confirmar estrutura
                    participantsStream.str(line);
                    while (getline(participantsStream, name, ',')) {
                        if (name.find('-') != string::npos) {
                            pCountry = name.substr(0, name.find('-'));
                            participant = name.substr(name.find('-') + 1, name.size());
                            medal.setWinner(participant);
                            medal.setCountry(pCountry);
                            if (medalCount == 0)
                                medal.setType('g');
                            else if (medalCount == 1)
                                medal.setType('s');
                            else
                                medal.setType('b');
                            medals.push_back(medal);
                            medalCount++;
                        }
                    }
                    participantsStream.clear();
                    numline = 0;
                    medalCount = 0;
                    break;
                default:
                    throw FileStructureError(competitionsFilename);
            }
        }
        //ler jogo
        if (read == 't') {
            switch (numline) {
                case 1:
                    trial.setName(line);
                    break;
                case 2:
                    if (checkPositiveIntInput(line) != 0)
                        throw FileStructureError(competitionsFilename);
                    if (stoi(line) != 0)
                        trial.setNumberOfElements(stoi(line));
                    break;
                case 3:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(competitionsFilename);
                    trial.setDate(d);
                    break;
                case 4:
                    participantsStream.str(line);
                    while (getline(participantsStream, name, ','))
                        trialPlayers.push_back(name);
                    trial.setPlayers(trialPlayers);
                    participantsStream.clear();
                    break;
                case 5:
                    trial.setWinner(line);
                    numline = 0;
                    trials.push_back(trial);
                    break;
                default:
                    throw FileStructureError(competitionsFilename);
            }
        }
    }
}
const string &Delegation::getCountry() const {
    return country;
}

void Delegation::setCountry(const string &count) {
    this->country = count;
}

float Delegation::getDailyCostAthlete() const {
    return dailyCostAthlete;
}

void Delegation::setDailyCostAthlete(float dailyCost) {
    this->dailyCostAthlete = dailyCost;
}

float Delegation::getDailyCostStaff() const {
    return dailyCostStaff;
}

void Delegation::setDailyCostStaff(float dailyCost) {
    this->dailyCostStaff = dailyCost;
}

float Delegation::getTotalCost() const {
    return totalCost;
}

void Delegation::setTotalCost(float totalcost) {
    this->totalCost = totalcost;
}


void Delegation::calculateTotalCost() {
    float result = 0;

    for(auto & i : people){
        if(i->isAthlete()){
            result += (float)daysBetween(i->getArrival(), i->getDeparture()) * dailyCostAthlete;
        } else {
            result += (float)daysBetween(i->getArrival(), i->getDeparture()) * dailyCostStaff;
        }
    }

    this->totalCost = result;
}

string Delegation::info(){
    ostringstream os;
    os <<  left <<setw(17) << "Country" << setw(4) << " "<<  country << setw(3) <<endl;
    os <<  left <<setw(17) << "Staff's Daily Cost" << setw(4) << " "<< dailyCostStaff << setw(3) <<endl;
    os <<  left <<setw(17) << "Athlete's Daily Cost" << setw(4) << " "<< dailyCostAthlete << setw(3) <<endl;
    os <<  left <<setw(17) << "Total Cost" << setw(4) << " "<< totalCost << setw(3) <<endl;
    return os.str();
}
//File Errors - Exceptions

FileError::FileError(string file) : file(move(file)){}

ostream & operator << (ostream & os, const FileError & file){
    os <<"Error opening file " << file.file << "!"<<endl;
    return os;
}

FileStructureError::FileStructureError(string file) : file(move(file)){}

ostream & operator << (ostream & os, const FileStructureError & file){
    os <<"The structure of file " << file.file << " is not the expected!"<<endl;
    return os;
}

//sport doesn't exist

template <class Participant>
NonExistentSport<Participant>::NonExistentSport(string name){
    this->name = name;
}

template <class Participant>
ostream & operator << (ostream & os,  const NonExistentSport<Participant> & c){
    os << c.competition << " doesn't exist in " << c.sport << "!\n";
    return os;
}

//competition doesn't exist
template <class Participant>
NonExistentCompetition<Participant>::NonExistentCompetition(string name, string sport){
    this->name = name;
    this->sport = sport;
}

template <class Participant>
ostream & operator <<(ostream & os, const NonExistentCompetition<Participant> & c){
    os << c.competition << " doesn't exist in " << c.sport << "!\n";
    return os;
}

//trial doesn't exist
template <class Participant>
NonExistentTrial<Participant>::NonExistentTrial(string name, string competition, string sport){
    this->name = name;
    this->competition = competition;
    this->sport = sport;
}

template <class Participant>
ostream & operator << (ostream & os, const NonExistentTrial<Participant> & t){
    os << t << " doesn't exist in "  << t.competition <<  ", " << t.sport << "!\n";
    return os;
}

//participant doesn't exist
template <class Participant>
NonExistentParticipant<Participant>::NonExistentParticipant(string name, string where){
    participant = name;
    this->where = where;
}

template <class Participant>
ostream & operator <<(ostream & os, const NonExistentParticipant<Participant> & p){
    os << p << " doesn't compete in " << p.where << "!\n";
    return os;
}
