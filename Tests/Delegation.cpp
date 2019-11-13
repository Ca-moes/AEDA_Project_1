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
#include <functional>
#include <unistd.h>

Delegation::Delegation() {
    try {
        readDelegationFile();
    }
    catch (FileError &e) {
        cout << e << endl;
        throw;
    }
    catch (FileStructureError &s) {
        cout << s << endl;
        throw;
    }

    mainMenu(*this);
}

Delegation::~Delegation(){
    //Ir a cada um dos nomes de ficheiros em delegation.txt
    // ficheiro a ficheiro escrever para lá os conteudos guadados nos objectos
    // Para fase inicial dar o nome "<nome_ficheiro>_write.txt" aos ficheiros para não dar overwrite"
    writePeopleFile();
    writeCompetitionsFile();
}

//Reading files functions
void Delegation::readDelegationFile() {
    int numline = 0;
    string line, file;
    ifstream delegationFile;
    cout << "Delegation .txt File: ";
    // Falta checar inputs;
    // cin >> file;
    file = "delegation";
    file += ".txt";
    delegationFile.open(file);
    if (delegationFile.fail())
        throw FileError(file);

    while (getline(delegationFile, line)) {
        numline++;
        switch (numline) {
            case 1:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
                if (checkStringInput(line) != 0)
                    throw FileStructureError(file);
                setCountry(line);
                break;
            case 2:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setDailyCostAthlete(stof(line));
                break;
            case 3:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setDailyCostStaff(stof(line));
                break;
            case 4:
                line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkFloatInput(line) != 0)
                    throw FileStructureError(file);
                setTotalCost(stof(line));
                break;
            case 5:
                peopleFilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkStringInput(line) != 0)
                    throw FileStructureError(file);
                break;
            case 6:
                teamsFilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkStringInput(line) != 0)
                    throw FileStructureError(file);
                break;
            case 7:
                competitionsFilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
                if (checkStringInput(line) != 0)
                    throw FileStructureError(file);
                break;
            default:
                throw FileStructureError(file);
        }
    }
    delegationFile.close();
    delegationFile.clear();
    //Read people file
    delegationFile.open(peopleFilename + ".txt");
    if (delegationFile.fail())
        throw FileError(peopleFilename + ".txt");
    readPeopleFile(fileToLineVector(delegationFile));
    delegationFile.close();
    delegationFile.clear();

    calculateTotalCost();
    sort(people.begin(), people.end(), sortPersons);
    sort(athletes.begin(), athletes.end(), sortMembersAlphabetically<Athlete>);

    //Read teams file

    delegationFile.open(teamsFilename + ".txt");
    if (delegationFile.fail())
        throw FileError(teamsFilename + ".txt");
    readTeamsFile(fileToLineVector(delegationFile));
    delegationFile.close();
    delegationFile.clear();

    //for (size_t i = 0; i < teams.size(); i++)
        //(teams[i])->showInfo();

    //Read competitions file
    delegationFile.open(competitionsFilename + ".txt");
    if (delegationFile.fail()) {
        throw FileError(competitionsFilename + ".txt");
    }
    readCompetitionsFile(fileToLineVector(delegationFile));
    delegationFile.clear();

    //set team competitions participants
    for (auto &team: teams) {//corre o vetor de equipas
        vector<Athlete> members = team->getAthletes();//para cada equipa guarda o vetor de membros
        vector<string> comps;//para cada equipa, serve para guarda as competições onde participa
        for(auto & member: members){//corre o vetor de membros de uma equipa
            for(size_t i= 0; i< athletes.size(); i++){//corre o vetor de atletas da delegação
                if(athletes[i]->getName() == member.getName()) { //se encontrar o atleta nos atletas
                    vector<string> appendComps = member.getCompetitions(); // guarda o vetor de competições
                    comps.insert(comps.end(),appendComps.begin(), appendComps.end()); // adiciona o vetor de competições às competições
                    break;
                }
            }
        }
        noRepeatVector(comps);
        team->setCompetitions(comps);
        comps.resize(0);
    }
}

void Delegation::readPeopleFile(const vector<string> &lines) {
    int numline = 0;
    string line;
    Date d;
    bool readFunc = false;
    Athlete *a = nullptr;
    Staff *s = nullptr;
    //Variables to read Competitions:
    istringstream competitionsStream;
    string compStr;
    vector<string> competitions;

    for (size_t i = 0; i < lines.size(); i++) {
        numline++;
        line = lines[i];

        if (line.empty()) { // Se alinha está vazia voltamos a colocar o numLines a 0 para ler a próxima pessoa
            numline = 1;
            i++;
            line = lines[i];
        }

        if (numline == 1) { // se for a primeira linha de uma pessoa vamos ver se é funcionário ou atleta
            readFunc = lines[i + 6].empty();
            competitions.resize(0);
            a = new Athlete();
            s = new Staff();
            competitionsStream.clear();
        }

        //ler atleta ou funcionario
        if (!readFunc) { // se tiver mais de 6 linha estamos perante um atleta
            //ler atleta
            switch (numline) {
                case 1:
                    if (checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setName(line);
                    break;
                case 2:
                    if (checkDateInput(line, d) !=
                        0) //just needs to check the format and set variables(in class date there is a function to check the validity)
                        throw FileStructureError(peopleFilename);
                    a->setBirth(d);
                    break;
                case 3:
                    if (checkAlphaNumericInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setPassport(line);
                    break;
                case 4:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if (d.isOlimpianDate()) {
                        a->setArrival(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 5:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if (d.isOlimpianDate()) {
                        a->setDeparture(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 6:
                    if (checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setSport(line);
                    break;
                case 7:
                    //ler competições - confirmar estrutura
                    competitionsStream.str(line);
                    while (getline(competitionsStream, compStr, ' ')) {
                        if (checkAlphaNumericInput(line) != 0)
                            throw FileStructureError(peopleFilename);
                        competitions.push_back(compStr);
                    }
                    a->setCompetitions(competitions);
                    break;
                case 8:
                    if (checkFloatInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setWeight(stof(line));
                    break;
                case 9:
                    if (checkFloatInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    a->setHeight(stof(line));
                    people.push_back(new Athlete(*a));
                    athletes.push_back(new Athlete(*a));
                    break;
                default:
                    throw FileStructureError(peopleFilename);
            }

        } else {
            switch (numline) {
                case 1:
                    if (checkStringInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    s->setName(line);
                    break;
                case 2:
                    if (checkDateInput(line, d) !=
                        0) //just needs to check the format and set variables(in class date there is a function to check the validity)
                        throw FileStructureError(peopleFilename);
                    s->setBirth(d);
                    break;
                case 3:
                    if (checkAlphaNumericInput(line) != 0)
                        throw FileStructureError(peopleFilename);
                    s->setPassport(line);
                    break;
                case 4:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if (d.isOlimpianDate()) {
                        s->setArrival(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 5:
                    if (checkDateInput(line, d) != 0)
                        throw FileStructureError(peopleFilename);
                    if (d.isOlimpianDate()) {
                        s->setDeparture(d);
                    } else {
                        throw FileStructureError(peopleFilename);
                    }
                    break;
                case 6:
                    if (checkStringInput(line) != 0)
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

void Delegation::writePeopleFile(){
    ofstream myfile ("people_write.txt");
    if (myfile.is_open())
    {
        for (unsigned int i = 0; i<people.size(); ++i) {
            myfile << people.at(i)->getName() << endl << people.at(i)->getBirth() << endl << people.at(i)->getPassport() << endl << people.at(i)->getArrival() << endl << people.at(i)->getDeparture() << endl;
            if(people.at(i)->isAthlete()){
                Athlete* a = dynamic_cast<Athlete *> (people.at(i));
                myfile << a->getSport() << endl;
                for (const auto & j : a->getCompetitions())
                    myfile << j << " ";
                myfile << endl << a->getWeight() << endl << a->getHeight();
            }
            else{
                Staff* a = dynamic_cast<Staff *> (people.at(i));
                myfile << a->getFunction();
            }
            if (i != people.size()-1)
                myfile << endl << endl;
        }
        myfile.close();
    }
    else cerr << "Unable to open file";
}

void Delegation::readCompetitionsFile(const vector<string> &lines) {
    int numline = 0;
    string line;
    Date d;
    char read = 's'; // auxiliar para saber se vamos ler um sport, uma competition ou um trial (s,c ou t)
    //objects to create a sport
    bool isTeamSport = false;
    TeamSport *teamSport = nullptr;
    IndividualSport *individualSport = nullptr;
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
    for (size_t i = 0; i < lines.size() + 1; i++) {
        if (i != lines.size())
            line = lines[i];
        numline++;
        if (numline == 1) {// se for a primeira linha de uma pessoa vamos ver se é uma nova modalidade, competição ou jogo
            if (line.empty()) {// Se alinha está vazia vamos ler a próxima competição
                if (read == 'c' || read == 't') {
                    if (read == 't') {
                        for (auto &athlete :athletes) {
                            for (auto &comp : athlete->getCompetitions()) {
                                if (comp == competition.getName())
                                    competition.addParticipant(athlete->getName());
                            }
                        }
                        competition.setTrials(trials);
                    }
                    competition.setMedals(medals);
                    competitions.push_back(competition);
                    medals.resize(0);
                    trials.resize(0);
                }
                competition = Competition();
                trial = Trial();
                medal = Medal();
                read = 'c';
                i++;
                numline = 1;
                line = lines[i];
            } else if (line == "////////" || i == lines.size()) {//novo desporto - guardar os dados das competições e jogos e limpar variáveis auxiliares; ou útlima linha do ficheiro
                if (read == 't' || read == 'c'){
                    if (read == 't') {
                        for (auto &athlete :athletes) {
                            for (auto &comp : athlete->getCompetitions()) {
                                if (comp == competition.getName())
                                    competition.addParticipant(athlete->getName());
                            }
                        }
                        competition.setTrials(trials);
                    }
                    competition.setMedals(medals);
                    competitions.push_back(competition);
                }
                if (isTeamSport){
                    teamSport->setCompetitions(competitions);
                    for (auto &team : teams) {
                        if (team->getSport() == teamSport->getName())
                            teamSport->addTeam(team);
                    }
                    sports.push_back(new TeamSport(*teamSport));
                } else {
                    individualSport->setCompetitions(competitions);
                    for (auto &athlete : athletes) {
                        if (athlete->getSport() == individualSport->getName())
                            individualSport->addAthlete(athlete);
                    }
                    sports.push_back(new IndividualSport(*individualSport));
                }
                competitions.resize(0);
                trials.resize(0);
                medals.resize(0);
                if (lines.size() == i) break;
                read = 's';
                numline = 1;
                i++;
                line = lines[i];
            } else if (line == "//") { //novo trial
                read = 't';
                trial =Trial();
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
                        throw FileStructureError(competitionsFilename);
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

void Delegation::writeCompetitionsFile(){

    ofstream myfile ("competitions_write.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < sports.size(); ++i) {
            myfile << sports.at(i)->getName() << endl;
            if (sports.at(i)->isTeamSport()) {
                TeamSport *sport = dynamic_cast<TeamSport *> (sports.at(i));
                myfile << sport->getNumberofElements() << "\n\n";
            } else {
                IndividualSport *sport = dynamic_cast<IndividualSport *> (sports.at(i));
                myfile << 1 << "\n\n";
            }
            for (int j = 0; j < sports.at(i)->getCompetitions().size(); ++j) {
                myfile << sports.at(i)->getCompetitions().at(j).getName() << endl;
                myfile << sports.at(i)->getCompetitions().at(j).getBegin() << endl;
                myfile << sports.at(i)->getCompetitions().at(j).getEnd() << endl;
                for (int k = 0; k < sports.at(i)->getCompetitions().at(j).getMedals().size(); ++k) {
                    myfile << sports.at(i)->getCompetitions().at(j).getMedals().at(k).getCountry() << "-"
                           << sports.at(i)->getCompetitions().at(j).getMedals().at(k).getWinner();
                    if (k != sports.at(i)->getCompetitions().at(j).getMedals().size() - 1)
                        myfile << ",";
                    else{
                        if (i != sports.size() -1)  // se não for o ultimo deporto adicona nova linha depois ds medalhas da competiçaõ
                            myfile << "\n";
                        if (i == sports.size() -1)  // se for o ultimo desporto
                        {
                            if(j != sports.at(i)->getCompetitions().size() - 1)
                                myfile << "\n";
                        }
                    }

                }
                if (sports.at(i)->getCompetitions().at(j).getTrials().size() != 0) {
                    for (int k = 0; k < sports.at(i)->getCompetitions().at(j).getTrials().size(); ++k) {
                        myfile << "//" << endl;
                        myfile << sports.at(i)->getCompetitions().at(j).getTrials().at(k).getName() << endl;
                        myfile << sports.at(i)->getCompetitions().at(j).getTrials().at(k).getParticipants().size()
                               << endl;
                        myfile << sports.at(i)->getCompetitions().at(j).getTrials().at(k).getDate() << endl;
                        for (int l = 0; l < sports.at(i)->getCompetitions().at(j).getTrials().at(
                                k).getParticipants().size(); ++l) {
                            myfile << sports.at(i)->getCompetitions().at(j).getTrials().at(k).getParticipants().at(l);
                            if (l !=
                                sports.at(i)->getCompetitions().at(j).getTrials().at(k).getParticipants().size() - 1)
                                myfile << ",";
                            else {
                                myfile << "\n";
                            }

                        }
                        myfile << sports.at(i)->getCompetitions().at(j).getTrials().at(k).getWinner() << endl;
                        if (k == sports.at(i)->getCompetitions().at(j).getTrials().size() - 1 && j != sports.at(i)->getCompetitions().size() -1)
                            myfile << "\n";
                    }
                } else {
                    if (j != sports.at(i)->getCompetitions().size() - 1)
                        myfile << "\n";
                }
            }
            if (i != sports.size()-1)
                myfile << "////////" << endl;
        }
    }
}

void Delegation::readTeamsFile(const vector<string> &lines) {
    int numline = 0;
    string line;
    Date d;
    bool readNewTeam = false;
    Team *t = nullptr;
    //Variables to read Athletes:
    istringstream membersStream;
    string memberStr;
    vector<Athlete> members;
    vector<Athlete *>::iterator it;
    Athlete a;
    string sport;

    for (size_t i = 0; i < lines.size(); i++) {
        numline++;
        line = lines[i];
        if (line == "&&&&") {
            teams.push_back(new Team(*t));
            break;
        }

        if (line.empty()) { // Se alinha está vazia voltamos a colocar o numLines a 0 para ler a próxima equipa
            teams.push_back(new Team(*t));
            numline = 1;
            i++;
            line = lines[i];
            readNewTeam = true;
            membersStream.clear();
            members.resize(0);
        } else if (line == "--------") {
            teams.push_back(new Team(*t));
            numline = 1;
            i++;
            line = lines[i];
            membersStream.clear();
            members.resize(0);
            readNewTeam = false;
        }

        if (numline == 1) {
            t = new Team();
        }

        //ler equipa do desporto atual ou equipas de desporto novo
        if (!readNewTeam) { // ler desporto novo
            switch (numline) {
                case 1:
                    if (checkStringInput(line) != 0)
                        throw FileStructureError(teamsFilename);
                    sport = line;
                    readNewTeam = true;
                    numline=0;
                    break;
            }
        } else {
            // ler equipa nova
            switch (numline) {
                case 1:
                    if (checkAlphaNumericInput(line) != 0) //check team name input - can have numbers
                        throw FileStructureError(teamsFilename);
                    t->setName(line);
                    t->setSport(sport);
                    break;
                case 2:
                    //ler competições - confirmar estrutura
                    membersStream.str(line);
                    while (getline(membersStream, memberStr, ',')) {
                        memberStr = regex_replace(memberStr, regex("^ +| +$|( ) +"), "$1");
                        if (checkStringInput(memberStr) != 0)
                            throw FileStructureError(teamsFilename);
                        for (it = athletes.begin(); it != athletes.end(); it++) {
                            if ((*it)->getName() == memberStr){
                                a = Athlete(**it);
                                members.push_back(a);
                            }
                        }
                    }
                    t->setAthletes(members);
                    break;
            }
        }
    }
}

//Acessors and mutators
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

const vector<Sport *> &Delegation::getSports() const {
    return sports;
}

void Delegation::calculateTotalCost() {
    float result = 0;

    for (auto &i : people) {
        if (i->isAthlete()) {
            result += (float) daysBetween(i->getArrival(), i->getDeparture()) * dailyCostAthlete;
        } else {
            result += (float) daysBetween(i->getArrival(), i->getDeparture()) * dailyCostStaff;
        }
    }

    this->totalCost = result;
}

string Delegation::info() const {
    ostringstream os;
    os << left << setw(17) << "Country" << setw(4) << " " << country << setw(3) << endl;
    os << left << setw(17) << "Staff's Daily Cost" << setw(4) << " " << dailyCostStaff << setw(3) << endl;
    os << left << setw(17) << "Athlete's Daily Cost" << setw(4) << " " << dailyCostAthlete << setw(3) << endl;
    os << left << setw(17) << "Total Cost" << setw(4) << " " << totalCost << setw(3) << endl;
    return os.str();
}

void Delegation::showMembers() {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Portuguese Delegation Members" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!people.empty()) {
        vector<Person *>::const_iterator it;
        for (it = people.begin(); it != people.end(); it++) {
            (*it)->showInfoPerson();
            cout << endl;
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

int Delegation::findPerson(const string & name) const {
    for (int i = 0; i < people.size(); i++) {
        if (name == people.at(i)->getName()) return i;
    }
    return -1;
}

//Staff Functions
void Delegation::addStaffMember() {
    Staff *novo = new Staff();
    string tmp;
    Date tmp_date;

    int test = 0;
    string input = "";

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cerr << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    if (findPerson(tmp) != -1) {
        throw PersonAlreadyExists(tmp);
    }
    novo->setName(tmp);

    cout << "Date of Birth: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date)) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Birth: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setBirth(tmp_date);

    cout << "Passport: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkAlphaNumericInput(tmp)) {
        cout << "Invalid Passport. Try again!" << endl;
        cout << "Passport: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setPassport(tmp);

    cout << "Date of Arrival: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Arrival: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setArrival(tmp_date);

    cout << "Date of Departure: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Departure: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setDeparture(tmp_date);

    cout << "Function: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp) == 1) {
        cout << "Invalid Function. Try again!" << endl;
        cout << "Function: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setFunction(tmp);

    people.push_back(novo);
}

void Delegation::removeStaffMember() {
    int test = 0;
    int index;
    string input = "", tmp;

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findPerson(tmp);
    if (index == -1 || people.at(index)->isAthlete()) {
        throw NonExistentStaff(tmp);
    } else {
        vector<Person *>::iterator it = people.begin() + index;
        delete *it;
        people.erase(it);
        return;
    }
}

void Delegation::changeStaffMember() {
    int test = 0;
    int index;
    string input = "", tmp;

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findPerson(tmp);
    if (index == -1 || people.at(index)->isAthlete()) {
        throw NonExistentStaff(tmp);
    } else {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   What do you want to change?" << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Name" << endl;
        cout << "2 - Date of Birth" << endl;
        cout << "3 - Passport" << endl;
        cout << "4 - Date of Arrival" << endl;
        cout << "5 - Date of Departure" << endl;
        cout << "6 - Function" << endl;
        cout << "0 - BACK" << endl;

        do {
            test = checkinputchoice(input, 0, 6);
            if (test != 0 && test != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (test != 0 && test != 2);
        if (test == 2) { input = "0"; }

        Date tmp_date;

        switch (stoi(input)) {
            case 1:
                cout << "New name: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkStringInput(tmp) || findPerson(tmp) != -1) {
                    cout << "Invalid Name. Try again!" << endl;
                    cout << "New name: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setName(tmp);
                break;
            case 2:
                cout << "Date of Birth: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date)) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Birth: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setBirth(tmp_date);
                break;
            case 3:
                cout << "Passport: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkAlphaNumericInput(tmp)) {
                    cout << "Invalid Passport. Try again!" << endl;
                    cout << "Passport: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setPassport(tmp);
                break;
            case 4:
                cout << "Date of Arrival: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Arrival: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setArrival(tmp_date);
                break;
            case 5:
                cout << "Date of Departure: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Departure: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setDeparture(tmp_date);
                break;
            case 6:
                cout << "Function: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkStringInput(tmp)) {
                    cout << "Invalid Function. Try again!" << endl;
                    cout << "Function: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                if (!people.at(index)->isAthlete()) {
                    Staff *s = dynamic_cast<Staff *> (people.at(index));
                    if (s == NULL) {
                        cout << "Couldn't change function!" << endl;
                    } else {
                        s->setFunction(tmp);
                    }
                }
                break;
            case 0:
                break;
            default:
                break;
        }
    }
}

void Delegation::showStaffMember() const {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t   Information about a Staff Member" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!people.empty()) {
        int test = 0;
        int index;
        string input = "", tmp;

        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
        while (checkStringInput(tmp)) {
            cerr << "Invalid Name. Try again!" << endl;
            cout << "Name: ";
            getline(cin, tmp);
            if (cin.eof()) {
                cin.clear();
                return; //go back on ctrl+d
            }
            cin.clear();
        }
        index = findPerson(tmp);
        if (index == -1 || people.at(index)->isAthlete())
            throw NonExistentStaff(tmp);
        else {
            cout << endl;
            (*(people.begin() + index))->showInfoPerson();
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showStaffMembers() {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t  Information about Staff Members" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!people.empty()) {
        sort(people.begin(), people.end(), sortMembersAlphabetically<Person>);
        vector<Person *>::const_iterator it;
        for (it = people.begin(); it != people.end(); it++) {
            if (!(*it)->isAthlete()) {
                (*it)->showInfoPerson();
                cout << endl;
            }
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0 && test != 2)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

//Athletes Functions

void Delegation::addAthlete() {
    Athlete *novo = new Athlete();
    string tmp;
    Date tmp_date;
    vector<Competition> competitions;
    vector<string> competition_names;
    int index;

    int test = 0;
    string input = "";

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cerr << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    if (findPerson(tmp) != -1) {
        throw PersonAlreadyExists(tmp);
    }
    novo->setName(tmp);

    cout << "Date of Birth: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date)) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Birth: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setBirth(tmp_date);

    cout << "Passport: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkAlphaNumericInput(tmp)) {
        cout << "Invalid Passport. Try again!" << endl;
        cout << "Passport: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setPassport(tmp);

    cout << "Date of Arrival: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Arrival: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setArrival(tmp_date);

    cout << "Date of Departure: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
        cout << "Invalid Date. Try again!" << endl;
        cout << "Date of Departure: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setDeparture(tmp_date);

    cout << "Sport: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp) == 1) {
        cout << "Invalid Sport. Try again!" << endl;
        cout << "Sport: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findSport(tmp);
    if (index == -1){
        throw NonExistentSport(tmp);
    } else {
        novo->setSport(tmp);
        competitions = sports.at(index)->getCompetitions();
        for (int i = 0; i < competitions.size(); i++){
            competition_names.push_back(competitions.at(i).getName());
        }
        novo->setCompetitions(competition_names);
    }

    cout << "Weight: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkFloatInput(tmp)) {
        cerr << "Invalid Weight. Try again!" << endl;
        cout << "Weight: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setWeight(stof(tmp));

    cout << "Height: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkPositiveIntInput(tmp)) {
        cerr << "Invalid Height. Try again!" << endl;
        cout << "Height: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    novo->setHeight(stoi(tmp));

    people.push_back(novo);
    athletes.push_back(novo);
}

void Delegation::removeAthlete(){
    int test = 0;
    int index;
    string input = "", tmp;

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findPerson(tmp);
    if (index == -1 || !(people.at(index)->isAthlete())) {
        throw NonExistentAthlete(tmp);
    } else {
        vector<Person *>::iterator it = people.begin() + index;
        vector<Athlete*>::iterator it_a = athletes.begin() + index;
        athletes.erase(it_a);
        delete *it;
        people.erase(it);
        return;
    }
}

void Delegation::changeAthlete() {
    int test = 0;
    int index;
    string input = "", tmp;

    cout << "Name: ";
    getline(cin, tmp);
    if (cin.eof()) {
        cin.clear();
        return; //go back on ctrl+d
    }
    cin.clear();
    while (checkStringInput(tmp)) {
        cout << "Invalid Name. Try again!" << endl;
        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
    }
    index = findPerson(tmp);
    if (index == -1 || !(people.at(index)->isAthlete())) {
        throw NonExistentAthlete(tmp);
    } else {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   What do you want to change?" << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Name" << endl;
        cout << "2 - Date of Birth" << endl;
        cout << "3 - Passport" << endl;
        cout << "4 - Date of Arrival" << endl;
        cout << "5 - Date of Departure" << endl;
        cout << "6 - Sport" << endl;
        cout << "7 - Weight" << endl;
        cout << "8 - Height" << endl;
        cout << "0 - BACK" << endl;

        do {
            test = checkinputchoice(input, 0, 8);
            if (test != 0 && test != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (test != 0 && test != 2);
        if (test == 2) { input = "0"; }

        Date tmp_date;
        int s_index;
        vector<Competition> competitions;
        vector<string> competition_names;

        switch (stoi(input)) {
            case 1:
                cout << "New name: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkStringInput(tmp) || findPerson(tmp) != -1) {
                    cout << "Invalid Name. Try again!" << endl;
                    cout << "New name: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setName(tmp);
                athletes.at(index)->setName(tmp);
                break;
            case 2:
                cout << "Date of Birth: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date)) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Birth: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setBirth(tmp_date);
                athletes.at(index)->setBirth(tmp_date);
                break;
            case 3:
                cout << "Passport: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkAlphaNumericInput(tmp)) {
                    cout << "Invalid Passport. Try again!" << endl;
                    cout << "Passport: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setPassport(tmp);
                athletes.at(index)->setPassport(tmp);
                break;
            case 4:
                cout << "Date of Arrival: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Arrival: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setArrival(tmp_date);
                athletes.at(index)->setArrival(tmp_date);
                break;
            case 5:
                cout << "Date of Departure: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkDateInput(tmp, tmp_date) || !(tmp_date.isOlimpianDate())) {
                    cout << "Invalid Date. Try again!" << endl;
                    cout << "Date of Departure: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                people.at(index)->setDeparture(tmp_date);
                athletes.at(index)->setDeparture(tmp_date);
                break;
            case 6:
                cout << "Sport: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkStringInput(tmp) || findSport(tmp) == -1) {
                    cout << "Invalid Sport. Try again!" << endl;
                    cout << "Sport: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                if (people.at(index)->isAthlete()) {
                    Athlete *a = dynamic_cast<Athlete *> (people.at(index));
                    if (a == NULL) {
                        cout << "Couldn't change Sport!" << endl;
                    } else {
                        s_index = findSport(tmp);
                        athletes.at(index)->setSport(tmp);
                        a->setSport(tmp);
                        competitions = sports.at(s_index)->getCompetitions();
                        for (int i = 0; i < competitions.size(); i++) {
                            competition_names.push_back(competitions.at(i).getName());
                        }
                        a->setCompetitions(competition_names);
                        athletes.at(index)->setCompetitions(competition_names);
                    }
                }
                break;
            case 7:
                cout << "Weight: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkFloatInput(tmp)) {
                    cerr << "Invalid Weight. Try again!" << endl;
                    cout << "Weight: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                if (people.at(index)->isAthlete()) {
                    Athlete *a = dynamic_cast<Athlete *> (people.at(index));
                    if (a == NULL) {
                        cout << "Couldn't change Weight!" << endl;
                    } else {
                        athletes.at(index)->setWeight(stof(tmp));
                        a->setWeight(stof(tmp));
                    }
                }
                break;
            case 8:
                cout << "Height: ";
                getline(cin, tmp);
                if (cin.eof()) {
                    cin.clear();
                    return; //go back on ctrl+d
                }
                cin.clear();
                while (checkPositiveIntInput(tmp)) {
                    cerr << "Invalid Height. Try again!" << endl;
                    cout << "Height: ";
                    getline(cin, tmp);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                }
                if (people.at(index)->isAthlete()) {
                    Athlete *a = dynamic_cast<Athlete *> (people.at(index));
                    if (a == NULL) {
                        cout << "Couldn't change Height!" << endl;
                    } else {
                        athletes.at(index)->setHeight(stof(tmp));
                        a->setHeight(stoi(tmp));
                    }
                }
                break;
            case 0:
                break;
            default:
                break;
        }
    }
}

void Delegation::showAthlete() const {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t   Information about an Athlete" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!people.empty()) {
        int test = 0;
        int index;
        string input = "", tmp;

        cout << "Name: ";
        getline(cin, tmp);
        if (cin.eof()) {
            cin.clear();
            return; //go back on ctrl+d
        }
        cin.clear();
        while (checkStringInput(tmp)) {
            cout << "Invalid Name. Try again!" << endl;
            cout << "Name: ";
            getline(cin, tmp);
            if (cin.eof()) {
                cin.clear();
                return; //go back on ctrl+d
            }
            cin.clear();
        }
        index = findPerson(tmp);
        if (index == -1 || !people.at(index)->isAthlete())
            throw NonExistentAthlete(tmp);
        else {
            cout << endl;
            (*(people.begin() + index))->showInfo();
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showAllAthletes() {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t  Information about Athletes" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!athletes.empty()) {
        vector<Athlete *>::const_iterator it;
        for (it = athletes.begin(); it != athletes.end(); it++) {
            (*it)->showInfo();
            cout << endl;
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

//Teams Functions
void Delegation::showTeam() const {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\tInformation about a Team" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!teams.empty()) {
        int test = 0;
        int index;
        string input = "", nm;
        bool found = false;

        do {
            cout << "Name: ";
            getline(cin, nm);
            if (cin.eof()) {
                cin.clear();
                return; //go back on ctrl+d
            }
            cin.clear();
        } while (cin.fail());


        vector<Team *>::const_iterator t;
        for (t = teams.begin(); t != teams.end(); t++) {
            if ((*t)->getName() == nm) {
                (*t)->showInfo();
                found = true;
            }
        }
        if (!found)
            throw NonExistentTeam(nm);

    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showAllTeams() {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Information about Teams" << endl;
    cout << "_____________________________________________________" << endl << endl;


    if (!teams.empty()) {
        sort(teams.begin(), teams.end(), sortMembersAlphabetically<Team>);
        vector<Team *>::const_iterator it;
        for (it = teams.begin(); it != teams.end(); it++) {
            (*it)->showInfo();
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

//Sports Functions
void Delegation::removeSport(const string &sport) {
    vector<Sport *>::iterator s;
    int test = 0, index = 0;
    string input = "";


    cout << "This option will also remove all athletes/teams who actually play " << sport << "!" << endl;
    cout << "Are you sure you want to proceed?" << endl;

    cout << "1 - Yes" << endl;
    cout << "2 - No" << endl;

    do {
        test = checkinputchoice(input, 1, 2);
        if (test != 0)
            cerr << "Invalid option! Please try again." << endl;
    } while (test != 0);

    if (stoi(input) == 1) {
        for (s = sports.begin(); s != sports.end(); s++) {
            if ((*s)->getName() == sport) {
                //remove every team who plays the sport
                if ((*s)->isTeamSport()) {
                    vector<Team *>::iterator t;
                    for (t = teams.begin(); t != teams.end(); t++) {
                        if ((*t)->getSport() == sport) {
                            //elimina os membros da equipa
                            Team *n = new Team(**t);
                            oldTeams.push_back(*n);
                            vector<Athlete>::iterator a;
                            vector<Athlete> teamMembers = (*t)->getAthletes();
                            for (a = teamMembers.begin(); a != teamMembers.end(); a++) {
                                oldAthletes.push_back(*a);
                                a = teamMembers.erase(a);
                                a--;
                            }
                            t = teams.erase(t);
                            t--;
                        }
                    }
                }
                sports.erase(s);
                //remove every athlete who plays
                vector<Athlete *>::iterator a;
                for (a = athletes.begin(); a != athletes.end(); a++) {
                    if ((*a)->getSport() == sport) {
                        if (find(oldAthletes.begin(), oldAthletes.end(), **a) == oldAthletes.end())
                            oldAthletes.push_back(**a);
                        athletes.erase(a);
                        a--;
                    }
                }
                vector<Person *>::iterator p;
                for (p = people.begin(); p != people.end(); p++) {
                    if ((*p)->isAthlete()) {
                        if (find(oldAthletes.begin(), oldAthletes.end(), **p) != oldAthletes.end()) {
                            people.erase(p);
                            p--;
                        }
                    }
                }
                break;
            }
        }
        throw NonExistentSport(sport);
    }
}

void Delegation::showCompetition(const string & sport){
    int test = 0;
    string input = "";
    int testinput=0;
    vector<Competition>::const_iterator cit;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t" << sport<<" Competition Info" << endl;
    cout << "_____________________________________________________" << endl << endl;

    vector<Sport * >::iterator s = sports.begin();
    string nm;

    while(s!= sports.end()){
        if((*s)->getName() == sport){
            vector<Competition> c = (*s)->getCompetitions();
            if(!c.empty()){
                bool found = false;

                do {
                    cout << "Competition's name: ";
                    getline(cin, nm);
                    if (cin.eof()) {
                        cin.clear();
                        return; //go back on ctrl+d
                    }
                    cin.clear();
                } while (cin.fail());

                for (cit = c.begin(); cit != c.end(); cit++) {
                    if (cit->getName() == nm) {
                        cout << endl;
                        cit->showInfo();
                        found = true;
                        break;
                    }
                }
                if (!found)
                    throw NonExistentCompetition(nm,sport);
            }
            else
                throw NoCompetitions(sport);
        }
        s++;
    }

    cout << endl << "1 - Trials Details";
    cout << endl << "0 - BACK" << endl;

    do {
        test = checkinputchoice(input, 0, 1);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
    if (testinput == 2)
    { input = "0"; }

    switch (stoi(input)) {
        case 1:
            try{
                showTrials(nm,sport);
            }
            catch(NoTrials & t){
                cout << t;
                exceptionHandler();
            }
            break;
        case 0:
            break;
    }
}

void Delegation::showAllCompetitions(const string & sport){
    int test = 0;
    string input = "";
    vector<Competition> competitions;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t" << sport << " Competitions" << endl;
    cout << "_____________________________________________________" << endl << endl;

    for(size_t i=0; i< sports.size(); i++){
        if(sport == sports[i]->getName()){
            competitions = sports[i]->getCompetitions();
            break;
        }
    }
    if (!competitions.empty()) {
        sort(competitions.begin(), competitions.end(), sortCompetitionsByDate);
        vector<Competition>::const_iterator it;
        for (it = competitions.begin(); it != competitions.end(); it++) {
            it->showInfo();
            cout << endl;
        }
    } else
        throw NoCompetitions(sport);

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showAllTrials(const string & sport){
    int test = 0;
    string input = "";
    vector<Competition> competitions;
    int nTrials=0;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t" << sport << " Trials" << endl;
    cout << "_____________________________________________________" << endl << endl;

    for(size_t i=0; i< sports.size(); i++){
        if(sport == sports[i]->getName()){
            competitions = sports[i]->getCompetitions();
            break;
        }
    }
    if (!competitions.empty()) {
        sort(competitions.begin(), competitions.end(), sortCompetitionsByDate);
        vector<Competition>::const_iterator it;
        for (it = competitions.begin(); it != competitions.end(); it++) {
            vector<Trial> trials = it->getTrials();
            if(!trials.empty()){
                cout << it->getName()<< " competition:" << endl;
                for(size_t i=0; i< trials.size(); i++){
                    trials[i].showInfo();
                    cout << endl;
                }
                nTrials++;
            }
        }
        if(nTrials == 0)
            throw NoTrials(sport);
    } else
        throw NoCompetitions(sport);

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showAllTrials(){
    int test = 0;
    string input = "";
    vector<Trial> allTrials;
    vector<Competition>::const_iterator it;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t  Trials Calendar" << endl;
    cout << "_____________________________________________________" << endl << endl;

    if (!sports.empty()) {
        for (size_t i = 0; i < sports.size(); i++) {
            vector<Competition> competitions;
            competitions = sports[i]->getCompetitions();
            if (!competitions.empty()) {
                sort(competitions.begin(), competitions.end(), sortCompetitionsByDate);
                for (it = competitions.begin(); it != competitions.end(); it++) {
                    vector<Trial> trials = it->getTrials();
                    if (!trials.empty()){
                        allTrials.insert(allTrials.end(),trials.begin(),trials.end());
                    }
                }
            }
        }
        if(allTrials.empty())
            throw NoTrials();
    } else throw NoSports();

    sort(allTrials.begin(),allTrials.end(),sortTrialsByDate);
    vector<Date> dates;

    for(size_t i=0; i< allTrials.size(); i++){
        if(i==0) dates.push_back(allTrials[i].getDate());
        else{
            if(find(dates.begin(),dates.end(),allTrials[i].getDate()) == dates.end())
                dates.push_back(allTrials[i].getDate());
        }
    }

    int tmp=0;
    for(size_t j=0; j<dates.size();j++){
        cout << "--------------"<<endl;
        cout << "  " << dates[j] <<endl;
        cout << "--------------"<<endl;
        for(size_t i=tmp; i< allTrials.size(); i++){
            if(allTrials[i].getDate() == dates[j]){
                allTrials[i].showInfoNoDate();
                cout <<endl;
            }
            else{
                tmp=i;
                break;
            }
        }
    }

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showTrials(const string & comp,const string & sport) const{
    int test = 0;
    string input = "";
    vector<Competition> competitions;

    for(size_t i=0; i< sports.size(); i++){
        if(sport == sports[i]->getName()){
            competitions = sports[i]->getCompetitions();
            break;
        }
    }
    if (!competitions.empty()) {
        sort(competitions.begin(), competitions.end(), sortCompetitionsByDate);
        vector<Competition>::const_iterator it;
        for (it = competitions.begin(); it != competitions.end(); it++) {
            if(it->getName() == comp){
                vector<Trial> trials = it->getTrials();
                sort(trials.begin(),trials.end(),sortTrialsByDate);
                if(!trials.empty()){
                    cout << it->getName()<< " trials:" << endl;
                    for(size_t i=0; i< trials.size(); i++){
                        trials[i].showInfo();
                        cout << endl;
                    }
                    cout << endl << "0 - BACK" << endl;
                    do {
                        test = checkinputchoice(input, 0, 0);
                        if (test != 0)
                            cerr << "Invalid option! Press 0 to go back." << endl;
                    } while (test != 0 && test != 2);
                    return;
                }
                else
                    throw NoTrials(comp);
            }
        }
    } else
        throw NoCompetitions(sport);

}

void Delegation::showTrialsInDay(){
    int test = 0;
    string input = "";
    vector<Trial> allTrials;
    vector<Competition>::const_iterator it;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t  Trials Calendar" << endl;
    cout << "_____________________________________________________" << endl << endl;

    if (!sports.empty()) {
        for (size_t i = 0; i < sports.size(); i++) {
            vector<Competition> competitions;
            competitions = sports[i]->getCompetitions();
            if (!competitions.empty()) {
                sort(competitions.begin(), competitions.end(), sortCompetitionsByDate);
                for (it = competitions.begin(); it != competitions.end(); it++) {
                    vector<Trial> trials = it->getTrials();
                    if (!trials.empty()){
                        allTrials.insert(allTrials.end(),trials.begin(),trials.end());
                    }
                }
            }
        }
        if(allTrials.empty())
            throw NoTrials();
    } else throw NoSports();

    sort(allTrials.begin(),allTrials.end(),sortTrialsByDate);
    vector<Date> dates;

    for(size_t i=0; i< allTrials.size(); i++){
        if(i==0) dates.push_back(allTrials[i].getDate());
        else{
            if(find(dates.begin(),dates.end(),allTrials[i].getDate()) == dates.end())
                dates.push_back(allTrials[i].getDate());
        }
    }

    string date;
    Date d;
    bool valid =false;
    do{
        cout << "Date:";
        getline(cin,date);
        if(cin.eof()){
            cin.clear();
            return;
        }
        if(checkDateInput(date,d))
            cerr << "Invalid date, please try again!"<<endl;
        else{
            if (!d.isOlimpianDate())
                cerr << "Invalid date, please try again!"<<endl;
            else
                valid=true;
        }
        }while(checkDateInput(date,d) || !valid);

    bool noTrialsInDay=true;
    cout<<endl;
    cout << "--------------"<<endl;
    cout << "  " << d <<endl;
    cout << "--------------"<<endl;
    for(size_t i=0; i< allTrials.size(); i++){
        if(allTrials[i].getDate() == d){
            noTrialsInDay=false;
            allTrials[i].showInfoNoDate();
            cout <<endl;
        }
    }


    if(noTrialsInDay)
        cout << "No Trials occur in that Day!"<<endl;

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

int Delegation::findSport(const string & name) const {
    for (int i = 0; i < sports.size(); i++) {
        if (name == sports.at(i)->getName()) return i;
    }
    return -1;
}

//Sort People
void Delegation::sortAllPeople() {
    sort(people.begin(), people.end(), sortPersons);
    sort(athletes.begin(), athletes.end(), sortPersons);
}

//Medals Functions
void Delegation::showAllMedals() const {
    int test = 0;
    string input = "",sport="";

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t  All Medals " << endl;
    cout << "_____________________________________________________" << endl << endl;

    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            sort(comps.begin(), comps.end(),sortCompetitionsByDate);
            if(!comps.empty()) {
                sport = (*s)->getName();
                transform(sport.begin(), sport.end(), sport.begin(), ::toupper);
                cout <<sport<<endl;
                for (c = comps.begin(); c != comps.end(); c++) {
                    cout << c->getName()<<endl;
                    c->showMedals();
                    cout << endl;

                }
            }
        }
    } else
        throw NoMedals();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

//Most awarded countries(total medals)
void Delegation::showCountryMedals() const{
    int test = 0;
    string input = "",sport="", cntr;
    bool noMedals = true,noMedalsInComp,noMedalsInSport;
    int g=0,sil=0,b=0;

    cout << "Country: ";
    do{
        getline(cin,cntr);
        if(cin.eof()){
            cin.clear();
            return;
        }
        if(checkStringInput(cntr))
            cerr << "Invalid number, please try again!"<<endl;
    }while(checkStringInput(cntr));

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t" << country <<  " Medals " << endl;
    cout << "_____________________________________________________" << endl << endl;

    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                noMedalsInSport = true;
                for (c = comps.begin(); c != comps.end(); c++) {
                    vector<Medal>medals = c->getMedals();
                    insertionSort(medals);
                    noMedalsInComp = true;
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(caseInSensStringCompare(m->getCountry(),cntr)){
                            if(noMedalsInSport){
                                sport = (*s)->getName();
                                transform(sport.begin(), sport.end(), sport.begin(), ::toupper);
                                cout <<sport<<endl;
                                noMedalsInSport=false;
                            }
                            if(noMedalsInComp){
                                noMedalsInComp = false;
                               cout << c->getName()<<endl;
                            }
                            m->showInfo();
                            noMedals = false;
                            //count number of medals
                            if(m->getType() == 'g')
                                g++;
                            else if(m->getType() == 's')
                                sil++;
                            else
                                b++;
                        }
                    }
                    if(!noMedalsInComp)
                        cout << endl;
                }
            }
        }
        if(noMedals)
            throw NoMedals(cntr);
    } else
        throw NoMedals();

    cout<< country << " won "<< g+sil+b << " medals: " <<endl;
    cout << left << setw(18) << "->Gold Medals "<<g<<endl;
    cout << left << setw(18)<< "->Silver Medals "<<sil<<endl;
    cout << left << setw(18)<< "->Bronze Medals "<<b<<endl;

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

void Delegation::showCountryMedals(const string & c) const{
    int test = 0;
    string input = "",sport="";
    bool noMedals = true,noMedalsInComp,noMedalsInSport;
    int g=0,sil=0,b=0;

    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator cit;
    vector<Medal>::iterator m;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                noMedalsInSport = true;
                for (cit = comps.begin(); cit != comps.end(); cit++) {
                    vector<Medal>medals = cit->getMedals();
                    insertionSort(medals);
                    noMedalsInComp = true;
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(caseInSensStringCompare(m->getCountry(),c)){
                            if(noMedalsInSport){
                                sport = (*s)->getName();
                                transform(sport.begin(), sport.end(), sport.begin(), ::toupper);
                                cout <<sport<<endl;
                                noMedalsInSport=false;
                            }
                            if(noMedalsInComp){
                                noMedalsInComp = false;
                                cout << cit->getName()<<endl;
                            }
                            m->showInfo();
                            //count number of medals
                            if(m->getType() == 'g')
                                g++;
                            else if(m->getType() == 's')
                                sil++;
                            else
                                b++;
                        }
                    }
                    if(!noMedalsInComp)
                        cout << endl;
                }
            }
        }
    }

    cout<< country << " won "<< g+sil+b << " medals: " <<endl;
    cout << left << setw(18) << "->Gold Medals "<<g<<endl;
    cout << left << setw(18)<< "->Silver Medals "<<sil<<endl;
    cout << left << setw(18)<< "->Bronze Medals "<<b<<endl;

}

int Delegation::numberOfMedalsCountry(const string & name) const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;
    bool noMedals=true;
    int n=0;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                for (c = comps.begin(); c != comps.end(); c++) {
                    vector<Medal>medals = c->getMedals();
                    insertionSort(medals);
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(caseInSensStringCompare(m->getCountry(),name)){
                            n++;
                            noMedals =false;
                        }
                    }
                }
            }
        }
        if(noMedals)
            throw NoMedals(country);
    } else
        throw NoMedals();

    return n;
}

vector<string> Delegation::getCountriesWithMedals() const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;

    vector<string> countries;
    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                for (c = comps.begin(); c != comps.end(); c++) {
                    vector<Medal>medals = c->getMedals();
                    insertionSort(medals);
                    for(m=medals.begin(); m!=medals.end();m++){
                        countries.push_back(m->getCountry());
                    }
                }
            }
        }
    } else
        throw NoMedals();

    noRepeatVector(countries);
    return countries;
}

void countriesSort(const Delegation & d,vector<string> & countries){
    for (unsigned int p = 1; p < countries.size(); p++)
    {
        string tmp = countries[p];
        int j;
        for (j = p; j > 0 && d.compareCountriesByMedals(tmp,countries[j-1]); j--)
            countries[j] = countries[j-1];
        countries[j] = tmp;
    }
}

void Delegation::mostAwardedCountries() const{
    int test = 0,nMax;
    string input = "",n="",temp="";
    vector<string> countries;
    bool notValid=false;
    int g=0,sil=0,b=0;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t Most Awarded Countries " << endl;
    cout << "_____________________________________________________" << endl << endl;

    try{
        countries = getCountriesWithMedals();
    }catch(NoMedals & e){throw;}

    countriesSort((*this),countries);
    nMax=countries.size();

    cout << "Show countries ranking positions from 1st to nth positions."<<endl;
    cout<< "Choose n from 1 to " << nMax << ": ";

    do{
        getline(cin,n);
        if(cin.eof()){
            cin.clear();
            return;
        }
        if(checkPositiveIntInput(n))
            cerr << "Invalid number, please try again!"<<endl;
        else
            notValid = stoi(n) < 1 || stoi(n) > nMax;
        if(notValid) cerr << "Invalid number, please try again!"<<endl;
    }while(checkPositiveIntInput(n) || notValid);


    cout<< endl<< left << setw(4) << " " << setw(10) <<  "COUNTRY" << left << setw(4) << "|"<< setw(4) << "MEDALS" <<endl;
    cout << "______________|__________"<<endl;
    for(size_t i= 0; i<stoi(n); i++){
        cout<< left << setw(4) << " " << setw(10)<<  countries[i] << left << setw(4) << "|"<< setw(4) << (*this).numberOfMedalsCountry(countries[i]) << endl;
    }

    cout << endl << "1 - Medals Details";
    cout << endl << "0 - BACK" << endl;

    do {
        test = checkinputchoice(input, 0, 1);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
    if (test == 2)
    { input = "0"; }

    switch (stoi(input)) {
        case 1:
            cout << endl;
            for (size_t i = 0; i < stoi(n); i++) {
                temp = countries[i];
                transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                for (int j = 0; j < temp.size(); j++)cout << " ";
                cout << temp << endl;
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                showCountryMedals(countries[i]);
                cout << endl;
            }
            cout << endl << "0 - BACK" << endl;
            do {
                test = checkinputchoice(input, 0, 0);
                if (test != 0)
                    cerr << "Invalid option! Press 0 to go back." << endl;
            } while (test != 0 && test != 2);
            break;
        case 0:
            break;
    }
}

bool Delegation::compareCountriesByMedals(const string &left, const string & right) const{
    return numberOfMedalsCountry(left) > numberOfMedalsCountry(right);
}
//Most awarded countries(gold medals)
void Delegation::mostAwardedGold() const{
    int test = 0,nMax;
    string input = "",n="",temp="";
    vector<string> countries;
    bool notValid=false;
    int g=0,sil=0,b=0;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t Most Awarded Countries - Gold Medals " << endl;
    cout << "_____________________________________________________" << endl << endl;

    try{
        countries = getCountriesWithGoldMedals();
    }catch(NoMedals & e){throw;}

    countriesSortGold((*this),countries);
    nMax=countries.size();

    cout << "Show countries ranking positions from 1st to nth positions."<<endl;
    cout<< "Choose n from 1 to " << nMax << ": ";

    do{
        getline(cin,n);
        if(cin.eof()){
            cin.clear();
            return;
        }
        if(checkPositiveIntInput(n))
            cerr << "Invalid number, please try again!"<<endl;
        else
            notValid = stoi(n) < 1 || stoi(n) > nMax;
        if(notValid) cerr << "Invalid number, please try again!"<<endl;
    }while(checkPositiveIntInput(n) || notValid);


    cout<< endl<< left << setw(4) << " " << setw(10) <<  "COUNTRY" << left << setw(4) << "|"<< setw(4) << "GOLD MEDALS" <<endl;
    cout << "______________|______________"<<endl;
    for(size_t i= 0; i<stoi(n); i++){
        cout<< left << setw(4) << " " << setw(10)<<  countries[i] << left << setw(4) << "|"<< setw(4) << (*this).numberOfGoldMedalsCountry(countries[i]) << endl;
    }

    cout << endl << "1 - Medals Details";
    cout << endl << "0 - BACK" << endl;

    do {
        test = checkinputchoice(input, 0, 1);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
    if (test == 2)
    { input = "0"; }

    switch (stoi(input)) {
        case 1:
            cout << endl;
            for (size_t i = 0; i < stoi(n); i++) {
                temp = countries[i];
                transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                for (int j = 0; j < temp.size(); j++)cout << " ";
                cout << temp << endl;
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                showCountryGoldMedals(countries[i]);
            }
            cout << endl << "0 - BACK" << endl;
            do {
                test = checkinputchoice(input, 0, 0);
                if (test != 0)
                    cerr << "Invalid option! Press 0 to go back." << endl;
            } while (test != 0 && test != 2);
            break;
        case 0:
            break;
    }
}

vector<string> Delegation::getCountriesWithGoldMedals() const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;

    vector<string> countries;
    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                for (c = comps.begin(); c != comps.end(); c++) {
                    vector<Medal>medals = c->getMedals();
                    insertionSort(medals);
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(m->getType() == 'g')
                            countries.push_back(m->getCountry());
                    }
                }
            }
        }
    } else
        throw NoMedals();

    noRepeatVector(countries);
    return countries;
}

bool Delegation::compareCountriesByGoldMedals(const string &left, const string & right) const{
    return numberOfGoldMedalsCountry(left) > numberOfGoldMedalsCountry(right);
}

void countriesSortGold(const Delegation & d,vector<string> & countries){
    for (unsigned int p = 1; p < countries.size(); p++)
    {
        string tmp = countries[p];
        int j;
        for (j = p; j > 0 && d.compareCountriesByGoldMedals(tmp,countries[j-1]); j--)
            countries[j] = countries[j-1];
        countries[j] = tmp;
    }
}

int Delegation::numberOfGoldMedalsCountry(const string & name) const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;
    bool noMedals=true;
    int n=0;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                for (c = comps.begin(); c != comps.end(); c++) {
                    vector<Medal>medals = c->getMedals();
                    insertionSort(medals);
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(caseInSensStringCompare(m->getCountry(),name) && m->getType() == 'g'){
                            n++;
                            noMedals =false;
                        }
                    }
                }
            }
        }
        if(noMedals)
            throw NoMedals(country);
    } else
        throw NoMedals();

    return n;
}

void Delegation::showCountryGoldMedals(const string & c) const{
    int test = 0;
    string input = "",sport="";
    bool noMedalsInComp,noMedalsInSport;

    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator cit;
    vector<Medal>::iterator m;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                noMedalsInSport = true;
                for (cit = comps.begin(); cit != comps.end(); cit++) {
                    vector<Medal>medals = cit->getMedals();
                    insertionSort(medals);
                    noMedalsInComp = true;
                    for(m=medals.begin(); m!=medals.end();m++){
                        if(caseInSensStringCompare(m->getCountry(),c) && m->getType() == 'g'){
                            if(noMedalsInSport){
                                sport = (*s)->getName();
                                transform(sport.begin(), sport.end(), sport.begin(), ::toupper);
                                cout << sport<<endl;
                                noMedalsInSport=false;
                            }
                            if(noMedalsInComp){
                                noMedalsInComp = false;
                                cout << left << setw(23) <<cit->getName();
                            }
                            cout << left << m->getWinner();
                        }
                    }
                    if(!noMedalsInComp)
                        cout << endl;
                }
            }
        }
    }
}

//Most awarded athletes
void Delegation::showAthleteMedals(const string & c) const{
    int test = 0;
    string input = "",sport="";
    bool noMedals = true,noMedalsInComp,noMedalsInSport;
    int g=0,sil=0,b=0;
    string nm;

    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator cit;
    vector<Medal>::iterator m;

    if (!sports.empty()) {
        vector<Sport *>sp = sports;
        sort(sp.begin(), sp.end(),sortMembersAlphabetically<Sport>);
        for(s = sp.begin(); s != sp.end(); s++){
            vector<Competition>comps = (*s)->getCompetitions();
            if(!comps.empty()) {
                noMedalsInSport = true;
                for (cit = comps.begin(); cit != comps.end(); cit++) {
                    vector<Medal>medals = cit->getMedals();
                    insertionSort(medals);
                    noMedalsInComp = true;
                    for(m=medals.begin(); m!=medals.end();m++){
                        if((*s)->isTeamSport()) nm=getAthleteTeam(c)->getName();
                        else nm=c;
                        if(caseInSensStringCompare(m->getWinner(),nm)){
                            if(noMedalsInSport){
                                sport = (*s)->getName();
                                transform(sport.begin(), sport.end(), sport.begin(), ::toupper);
                                cout <<sport<<endl;
                                noMedalsInSport=false;
                            }
                            if(noMedalsInComp){
                                noMedalsInComp = false;
                                cout << left << setw(15) << cit->getName();
                            }
                            m->showType();
                            //count number of medals
                            if(m->getType() == 'g')
                                g++;
                            else if(m->getType() == 's')
                                sil++;
                            else
                                b++;
                        }
                    }
                    if(!noMedalsInComp)
                        cout << endl;
                }
            }
        }
    }

    cout<< c << " won "<< g+sil+b << " medals: " <<endl;
    cout << left << setw(18) << "->Gold Medals "<<g<<endl;
    cout << left << setw(18)<< "->Silver Medals "<<sil<<endl;
    cout << left << setw(18)<< "->Bronze Medals "<<b<<endl;
}

int Delegation::numberOfMedalsAthlete(const string & name) const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;
    bool noMedals = true;
    vector<string> ats;
    int n=0;

    //verifica se os atletas têm medalhas em desportos individuais e, se tiverem, adiciona-os a outro vetor
    if (!sports.empty()) {
        vector<Sport *> sp = sports;
        sort(sp.begin(), sp.end(), sortMembersAlphabetically<Sport>);
        for (s = sp.begin(); s != sp.end(); s++) {
            if (!(*s)->isTeamSport()) {
                vector<Competition> comps = (*s)->getCompetitions();
                if (!comps.empty()) {
                    for (c = comps.begin(); c != comps.end(); c++) {
                        vector<Medal> medals = c->getMedals();
                        insertionSort(medals);
                        for (m = medals.begin(); m != medals.end(); m++) {
                            if (m->getWinner() == name)
                                n++;
                        }
                    }
                }
                noMedals = false;
            }else{
                Team * t = getAthleteTeam(name);
                vector<Competition> comps = (*s)->getCompetitions();
                if (!comps.empty()) {
                    for (c = comps.begin(); c != comps.end(); c++) {
                        vector<Medal> medals = c->getMedals();
                        insertionSort(medals);
                        for (m = medals.begin(); m != medals.end(); m++) {
                            if (t->getName() == m->getWinner())
                                n++;
                        }
                    }
                }
                noMedals = false;
            }
        }
        if (noMedals)
            throw NoMedals();
    } else
        throw NoMedals();

    return n;
}

vector<string> Delegation::getAthletesWithMedals() const{
    vector<Sport*>::const_iterator s;
    vector<Competition>::iterator c;
    vector<Medal>::iterator m;
    bool noMedals = true;
    vector<string> ats;
    vector<string> aWithMedals;

    //costrói vetor de strings com todos os atletas
    for(size_t i=0; i< athletes.size();i++)
        ats.push_back(athletes[i]->getName());

    //verifica se os atletas têm medalhas em desportos individuais e, se tiverem, adiciona-os a outro vetor
    for(size_t a=0; a < ats.size(); a++) {
        if (!sports.empty()) {
            vector<Sport *> sp = sports;
            sort(sp.begin(), sp.end(), sortMembersAlphabetically<Sport>);
            for (s = sp.begin(); s != sp.end(); s++) {
                if (!(*s)->isTeamSport()) {
                    vector<Competition> comps = (*s)->getCompetitions();
                    if (!comps.empty()) {
                        for (c = comps.begin(); c != comps.end(); c++) {
                            vector<Medal> medals = c->getMedals();
                            insertionSort(medals);
                            for (m = medals.begin(); m != medals.end(); m++) {
                                if (ats[a] == m->getWinner())
                                    aWithMedals.push_back(ats[a]);
                            }
                        }
                    }
                    noMedals = false;
                }
                else{
                    Team * t = getAthleteTeam(ats[a]);
                    vector<Competition> comps = (*s)->getCompetitions();
                    if (!comps.empty()) {
                        for (c = comps.begin(); c != comps.end(); c++) {
                            vector<Medal> medals = c->getMedals();
                            insertionSort(medals);
                            for (m = medals.begin(); m != medals.end(); m++) {
                                if (t->getName() == m->getWinner())
                                    aWithMedals.push_back(ats[a]);
                            }
                        }
                    }
                    noMedals = false;
                }
            }
            if (noMedals)
                throw NoMedals();
        } else
            throw NoMedals();
    }

    noRepeatVector(aWithMedals);
    return aWithMedals;
}

Team * Delegation::getAthleteTeam(const string & at) const{
    //find athletes team
    bool found=false;
    Team * emptyTeam = new Team();

    for(size_t j=0; j<teams.size();j++){
        vector<Athlete>participants=teams[j]->getAthletes();
        for(size_t i=0;i<participants.size(); i++){
            if(participants[i].getName() == at)
               found=true;
            break;
        }
        if(found) return teams[j];
    }
    return emptyTeam;
}

bool Delegation::compareAthletesByMedals(const string &left, const string & right) const{
    return numberOfMedalsAthlete(left) > numberOfMedalsAthlete(right);
}

void athletesSort(const Delegation & d,vector<string> & ats){
    for (unsigned int p = 1; p < ats.size(); p++)
    {
        string tmp = ats[p];
        int j;
        for (j = p; j > 0 && d.compareAthletesByMedals(tmp,ats[j-1]); j--)
            ats[j] = ats[j-1];
        ats[j] = tmp;
    }
}

void Delegation::mostAwardedAthletes() const{
    int test = 0,nMax;
    string input = "",n="",temp="";
    vector<string> ats;
    bool notValid=false;
    int g=0,sil=0,b=0;

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t Most Awarded Atheltes " << endl;
    cout << "_____________________________________________________" << endl << endl;

    try{
        ats = getAthletesWithMedals();
    }catch(NoMedals & e){throw;}
    athletesSort((*this),ats);
    nMax=ats.size();

    cout << "Show athletes ranking positions from 1st to nth positions."<<endl;
    cout<< "Choose n from 1 to " << nMax << ": ";

    do{
        getline(cin,n);
        if(cin.eof()){
            cin.clear();
            return;
        }
        if(checkPositiveIntInput(n))
            cerr << "Invalid number, please try again!"<<endl;
        else
            notValid = stoi(n) < 1 || stoi(n) > nMax;
        if(notValid) cerr << "Invalid number, please try again!"<<endl;
    }while(checkPositiveIntInput(n) || notValid);


    cout<< endl<< left << setw(4) << " " << setw(20) <<  "ATHLETE" << left << setw(4) << "|"<< setw(4) << "MEDALS" <<endl;
    cout << "________________________|__________"<<endl;
    for(size_t i= 0; i<stoi(n); i++){
        cout<< left << setw(4) << " " << setw(20)<<  ats[i] << left << setw(4) << "|"<< setw(4) << (*this).numberOfMedalsAthlete(ats[i]) << endl;
    }

    cout << endl << "1 - Medals Details";
    cout << endl << "0 - BACK" << endl;

    do {
        test = checkinputchoice(input, 0, 1);
        if (test != 0 && test != 2)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
    if (test == 2)
    { input = "0"; }

    switch (stoi(input)) {
        case 1:
            cout << endl;
            for (size_t i = 0; i < stoi(n); i++) {
                temp = ats[i];
                transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                for (int j = 0; j < temp.size(); j++)cout << " ";
                cout << temp << endl;
                for (int j = 0; j < temp.size() * 3; j++)cout << "-";
                cout << endl;
                showAthleteMedals(ats[i]);
                cout << endl;
            }
            cout << endl << "0 - BACK" << endl;
            do {
                test = checkinputchoice(input, 0, 0);
                if (test != 0)
                    cerr << "Invalid option! Press 0 to go back." << endl;
            } while (test != 0 && test != 2);
            break;
        case 0:
            break;
    }
}

//History
/*void Delegation::athletesHistory() {
    int test = 0;
    string input = "";

    system("cls");
    cout << "_______________________________________________________" << endl << endl;
    cout << "  Athletes that don't compete in the Olympics anymore  " << endl;
    cout << "_______________________________________________________" << endl << endl;


    if (!oldAthletes.empty()) {
        vector<Athlete *>::const_iterator it;
        for (it = athletes.begin(); it != athletes.end(); it++) {
            (*it)->showInfo();
            cout << endl;
        }
    } else
        throw NoMembers();

    cout << endl << "0 - BACK" << endl;
    do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
            cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}*/

//File Errors - Exceptions
FileError::FileError(string file) : file(move(file)) {}

ostream &operator<<(ostream &os, const FileError &file) {
    os << "Error opening file " << file.file << "!" << endl;
    return os;
}

FileStructureError::FileStructureError(string file) : file(move(file)) {}

ostream &operator<<(ostream &os, const FileStructureError &file) {
    os << "The structure of file " << file.file << " is not the expected!" << endl;
    return os;
}

//sport doesn't exist
NonExistentSport::NonExistentSport(string name) {
    this->sport = name;
}

ostream &operator<<(ostream &os, const NonExistentSport &c) {
    os << "The Delegation does not take part in " << c.sport << "!\n";
    return os;
}

//competition doesn't exist
NonExistentCompetition::NonExistentCompetition(string name, string sport) {
    this->competition = name;
    this->sport = sport;
}

ostream &operator<<(ostream &os, const NonExistentCompetition &c) {
    os << c.competition << " doesn't exist in " << c.sport << "!\n";
    return os;
}

//trial doesn't exist
NonExistentTrial::NonExistentTrial(string name, string competition, string sport) {
    this->name = name;
    this->competition = competition;
    this->sport = sport;
}

ostream &operator<<(ostream &os, NonExistentTrial &t) {
    os << t.name << " doesn't exist in " << t.competition << ", " << t.sport << "!\n";
    return os;
}

NonExistentPerson::NonExistentPerson(string name) {
    person = name;
}

ostream &operator<<(ostream &os, NonExistentPerson &p) {
    os << p.person << " doesn't exist!\n";
    return os;
}

NonExistentAthlete::NonExistentAthlete(string name) {
    person = name;
}

ostream &operator<<(ostream &os, NonExistentAthlete &p) {
    os << p.person << " is not an athlete!\n";
    return os;
}

NonExistentStaff::NonExistentStaff(string name) {
    person = name;
}

ostream &operator<<(ostream &os, NonExistentStaff &p) {
    os << p.person << " is not a member of the staff!\n";
    return os;
}
NonExistentTeam::NonExistentTeam(string name) {
    team = name;
}

ostream &operator<<(ostream &os, NonExistentTeam &p) {
    os << p.team << " doesn't exist!\n";
    return os;
}

PersonAlreadyExists::PersonAlreadyExists(string person) {
    this->person = person;
}

ostream &operator<<(ostream &os, PersonAlreadyExists &p) {
    os << p.person << " already exists!\n";
    return os;
}

TeamAlreadyExists::TeamAlreadyExists(string team) {
    this->team = team;
}

ostream &operator<<(ostream &os, TeamAlreadyExists &p) {
    os << p.team << " already exists!\n";
    return os;
}

NoMembers::NoMembers() {}

ostream &operator<<(ostream &os, NoMembers &p) {
    os << " No members to show!\n";
    return os;
}

NoSports::NoSports(){}

ostream & operator <<(ostream & os, const NoSports & s) {
    os << " No sports to show!\n";
    return os;
}

NoCompetitions::NoCompetitions(const string & sport){this->sport = sport;}

ostream &operator<<(ostream &os, NoCompetitions &p) {
    os << " No " << p.sport << " competitions to show!\n";
    return os;
}

NoTrials::NoTrials(const string & sport){this->sport = sport;}

ostream &operator<<(ostream &os, NoTrials &p) {
    if(p.sport!="")
        os << p.sport << " competitions don't have any trials!\n";
    else
        os << "The Sports of the Delegation don't have Trials!"<<endl;
    return os;
}

NoMedals::NoMedals() {country="";}

NoMedals::NoMedals(const string & c){country=c;}

ostream &operator<<(ostream &os, NoMedals &m) {
    if(m.country=="")
        os << " No medals to show!\n";
    else
        os << m.country << " didn't win any medals!\n";
    return os;
}
