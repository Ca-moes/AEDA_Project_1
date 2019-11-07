//
// Created by Diana Freitas on 20/10/2019.
//

#include "Delegation.h"
#include "auxiliar.h"
#include "Menus.h"
#include <regex>
#include <sstream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <functional>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

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

    calculateTotalCost();

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
    Athlete *a = nullptr;
    Staff *s = nullptr;
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
                    if(checkAlphaNumericInput(line) != 0)
                        throw FileStructureError(peopleFilename);
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
                    while (getline(competitionsStream, compStr, ' ')){
                        if(checkAlphaNumericInput(line) != 0)
                            throw FileStructureError(peopleFilename);
                        competitions.push_back(compStr);
                    }
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
                    if(checkAlphaNumericInput(line) != 0)
                        throw FileStructureError(peopleFilename);
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
    TeamSport *teamSport = nullptr;
    IndividualSport *individualSport =  nullptr;
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

const vector<Sport*> & Delegation::getSports() const{
    return sports;
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

string Delegation::info() const{
    ostringstream os;
    os <<  left <<setw(17) << "Country" << setw(4) << " "<<  country << setw(3) <<endl;
    os <<  left <<setw(17) << "Staff's Daily Cost" << setw(4) << " "<< dailyCostStaff << setw(3) <<endl;
    os <<  left <<setw(17) << "Athlete's Daily Cost" << setw(4) << " "<< dailyCostAthlete << setw(3) <<endl;
    os <<  left <<setw(17) << "Total Cost" << setw(4) << " "<< totalCost << setw(3) <<endl;
    return os.str();
}

void Delegation::addStaffMember() {
    Staff* novo = new Staff();
    string tmp;
    Date tmp_date;

    int test = 0;
    string input = "";

    cout << "Name: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkStringInput(tmp)){
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    if (findPerson(tmp) != -1){
        cout << "Person already exists!" << endl;
        cout << endl << "0 - BACK" << endl;
        do {
            test = checkinputchoice(input, 0, 0);
            if (test != 0 )
                cerr << "Invalid option! Press 0 to go back." << endl;
        } while (test != 0 && test != 2);
        return;
    }
    novo->setName(tmp);

    cout << "Date of Birth: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkDateInput(tmp, tmp_date)){
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Birth: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setBirth(tmp_date);

    cout << "Passport: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkAlphaNumericInput(tmp)){
        cout << "Invalid Passport. Try again!" << endl;
        cout << "Passport: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setPassport(tmp);

    cout << "Date of Arrival: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())){
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Arrival: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setArrival(tmp_date);

    cout << "Date of Departure: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())){
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Departure: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setDeparture(tmp_date);

    cout << "Function: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkStringInput(tmp) == 1){
        cout << "Invalid Function. Try again!" << endl;
        cout << "Function: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setFunction(tmp);

    people.push_back(novo);
}

void Delegation::showPortugueseMembers() const{
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Portuguese Delegation Members" << endl;
    cout << "_____________________________________________________" << endl << endl;
    if (people.size() != 0) {
        //sort(people.begin(),people.end(),sortMembersAlphabetically);
        vector<Person*>::const_iterator it;
        for(it=people.begin();it != people.end(); it++){
            cout << (*(*it));
            cout << endl;
        }
    }
    else {
        cerr << "No members to show!" << endl;
        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + seconds(1));
    }

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0 )
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

int Delegation::findPerson(const string name) {
    for (int i = 0; i < people.size(); i++){
        if(name == people.at(i)->getName()) return i;
    }
    return -1;
}

void Delegation::removeStaffMember() {
    int test = 0;
    int index;
    string input = "", tmp;

    cout << "Name: ";
    getline(cin,tmp);
    if (cin.eof()){
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while(checkStringInput(tmp)){
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin,tmp);
        if (cin.eof()){
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findPerson(tmp);
    if (index == -1 || people.at(index)->isAthlete()){
        cout << "Staff Member does not exist!" << endl;
        cout << endl << "0 - BACK" << endl;
        do {
            test = checkinputchoice(input, 0, 0);
            if (test != 0 )
                cerr << "Invalid option! Press 0 to go back." << endl;
        } while (test != 0 && test != 2);
        return;
    } else {
        vector<Person*>::iterator it = people.begin() + index;
        delete *it;
        people.erase(it);
        return;
    }
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
NonExistentSport::NonExistentSport(string name){
    this->sport = name;
}

ostream & operator << (ostream & os,  const NonExistentSport & c){
    os << c.sport << " doesn't exist!" << "!\n";
    return os;
}

//competition doesn't exist
NonExistentCompetition::NonExistentCompetition(string name, string sport){
    this->competition = name;
    this->sport = sport;
}

ostream & operator <<(ostream & os, const NonExistentCompetition & c){
    os << c.competition << " doesn't exist in " << c.sport << "!\n";
    return os;
}

//trial doesn't exist
NonExistentTrial::NonExistentTrial(string name, string competition, string sport){
    this->name = name;
    this->competition = competition;
    this->sport = sport;
}

ostream & operator <<(ostream & os, NonExistentTrial & t){
    os << t.name << " doesn't exist in "  << t.competition <<  ", " << t.sport << "!\n";
    return os;
}

//participant doesn't exist
NonExistentParticipant::NonExistentParticipant(string name, string where){
    participant = name;
    this->where = where;
}

ostream & operator <<(ostream & os, NonExistentParticipant & p){
    os << p.participant << " doesn't compete in " << p.where << "!\n";
    return os;
}
