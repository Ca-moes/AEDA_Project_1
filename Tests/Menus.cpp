//
// Created by Diana Freitas on 20/10/2019.
//

#include "Menus.h"
#include <regex>

using namespace std;

int checkinputchoice(string& test, int lowerlimit, int upperlimit) {
    do {
        getline(cin, test);
        if (cin.eof()){
            cin.clear();
            return 2;//go back on ctrl+d
        }

    } while (test.length() == 0);
    test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
    for (unsigned int i = 0; i < test.length(); i++)
    {
        if (!isdigit(test[i]))//se não for um dígito não é uma opção válida
            return 1;
    }
    if (stoi(test) < lowerlimit || stoi(test) > upperlimit) //se não estiver dentro dos limites
        return 1;
    return 0;
}

//main menu
void mainMenu(Delegation &delegation){
    int testinput = 0;
    string input = "";
    do
    {
        system("cls");
        cout << "_____________________________________________________________________________" << endl << endl;
        cout << "\t\t" << delegation.getCountry() << "'s Olympic Delegation - Tokyo 2020" << endl;
        cout << "_____________________________________________________________________________" << endl << endl;

        cout << "Choose an option by typing a number and pressing Enter." << endl << endl;
        //show the main menu
        cout << "1 - Members" << endl;
        cout << "2 - Sports Competitions" << endl;
        cout << "3 - Results" << endl;
        cout << "0 - EXIT" << endl;
        //checking if option is valid
        do {
            testinput = checkinputchoice(input, 0, 3);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
            input = "0";

        switch (stoi(input)) {
            case 1:
                participantsMenu(delegation);
                break;
            case 2:
                sportsMenu(delegation);
                break;
            case 3:
                resultsMenu(delegation);
                break;
            case 0:
                //delegation.writePeopleFile();
                //delegation.writeTeamFile();
                //delegation.writeCompetitionsFile();
                break;
        }
    } while (stoi(input) != 0);
}

//submenus - participants, sports, results
void participantsMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Members Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Athletes" << endl;
        cout << "2 - Teams" << endl;
        cout << "3 - Staff" << endl;
        cout << "4 - All Members" << endl;
        cout << "0 - BACK (Main Menu)" << endl;

        do {
            testinput = checkinputchoice(input, 0, 4);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
            input = "0";

        switch (stoi(input)) {
            case 1:
                athletesMenu(delegation);
                break;
            case 2:
                teamsMenu(delegation);
                break;
            case 3:
                staffMenu(delegation);
                break;
            case 4:
                try{
                    delegation.showPortugueseMembers();
                }catch(NoMembers & e){
                    cout << e << endl;
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}
void sportsMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t\t\t  Sports Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        for(size_t i=0; i < delegation.getSports().size(); i++){
            cout << i+1 << " - " << delegation.getSports()[i]->getName() << endl;
        }
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, delegation.getSports().size());
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        if(stoi(input) != 0)
            input = "1";
        switch (stoi(input)) {
            case 1:
                try{
                    sportsCompetitionsMenu(delegation,delegation.getSports()[stoi(input)-1]->getName());
                }
                catch(NonExistentSport & s){
                    cout << s;
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}
void resultsMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Sports Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Athletes" << endl;
        cout << "2 - Teams" << endl;
        cout << "3 - Staff" << endl;
        cout << "4 - All Participants" << endl;
        cout << "0 - BACK (Main Menu)" << endl;

        do {
            testinput = checkinputchoice(input, 0, 6);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                //athletesMenu(delegation);
                break;
            case 2:
                //teamsMenu(delegation);
                break;
            case 3:
                //staffMenu(delegation);
                break;
            case 4:
                //showParticipants();
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}

//Participants submenus
void staffMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Staff's Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Add Staff member" << endl;
        cout << "2 - Remove Staff member" << endl;
        cout << "3 - Change Staff member" << endl;
        cout << "4 - Show Staff member" << endl;
        cout << "5 - Show All Staff members" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 5);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                try{
                    delegation.addStaffMember();
                }
                catch(PersonAlreadyExists & e){
                    cout << e << endl;
                }
                break;
            case 2:
                try{
                    delegation.removeStaffMember();
                }
                catch(NonExistentPerson & e){
                    cout << e << endl;
                }
                break;
            case 3:
                try{
                    delegation.changeStaffMember();
                }
                catch(NonExistentPerson & e){
                    cout << e << endl;
                }
                break;
            case 4:
                try{
                    delegation.showStaffMember();
                }
                catch(NonExistentPerson & e){
                    cout << e << endl;
                }
                catch(NoMembers & n){
                    cout << n << endl;
                }
                break;
            case 5:
                try{
                    delegation.showStaffMembers();
                }
                catch(NonExistentPerson & e){
                    cout << e << endl;
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}
void athletesMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Athletes Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Add Athlete" << endl;
        cout << "2 - Change Athlete" << endl;
        cout << "3 - Remove Athlete" << endl;
        cout << "4 - View Athlete Info" << endl;
        cout << "5 - View All Athletes Info" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 5);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                //delegation.addAthlete();
                break;
            case 2:
                //changeClientMenu(delegation);
                break;
            case 3:
                //delegation.removeAthlete();
                break;
            case 4:
                delegation.showAthlete();
                break;
            case 5:
                delegation.showAllAthletes();
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}
void teamsMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Teams Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "1 - Add Team" << endl;
        cout << "2 - Change Team" << endl;
        cout << "3 - Remove Team" << endl;
        cout << "4 - View Team Info" << endl;
        cout << "5 - View All Teams Info" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 5);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                //delegation.addTeam();
                break;
            case 2:
                //changeTeamMenu(delegation);
                break;
            case 3:
                //delegation.removeTeam();
                break;
            case 4:
                try{
                    delegation.showTeam();
                }
                catch(NonExistentTeam & t){
                    cout<< t << endl;
                }
                catch(NoMembers & e){
                    cout<< e << endl;
                }
                break;
            case 5:
                try{
                    delegation.showAllTeams();
                }
                catch(NoMembers & e){
                    cout<< e << endl;
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}

//Sports submenus
void sportsCompetitionsMenu(Delegation & delegation, const string & sport){
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t\t\t\t\t" << sport << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "Choose an option by typing a number and pressing Enter." << endl << endl;
        //show the main menu
        cout << "1 - End Participation" << endl;
        cout << "2 - Competitions" << endl;
        cout << "0 - EXIT" << endl;

        do {
            testinput = checkinputchoice(input, 0, 2);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        if(stoi(input) != 0)
            input = "1";
        switch (stoi(input)) {
            case 1:
                try{
                    delegation.removeSport(sport);
                }
                catch(NonExistentSport & s){
                    throw;
                }
                break;
            case 2:
                //competitionsMenu(delegation,sport);
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}