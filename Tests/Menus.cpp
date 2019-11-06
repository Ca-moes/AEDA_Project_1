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

        //show client's menu
        cout << "1 - Athletes" << endl;
        cout << "2 - Teams" << endl;
        cout << "3 - Staff" << endl;
        cout << "4 - All Participants" << endl;
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
                //showPortugueseMembers();
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
        cout << "\t\t   Sports Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        //show client's menu
        cout << "1 - Athletes" << endl;
        cout << "2 - Teams" << endl;
        cout << "3 - Staff" << endl;
        cout << "4 - All Participants" << endl;
        cout << "0 - BACK" << endl;

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
                staffMenu(delegation);
                break;
            case 4:
                //showParticipants();
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

        //show client's menu
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

        //show client's menu
        cout << "1 - Add Staff member" << endl;
        cout << "2 - Remove Staff member" << endl;
        cout << "3 - Change Staff member" << endl;
        cout << "4 - Show Staff members" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 4);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                delegation.addStaffMember();
                break;
            case 2:
                //removeStaffMember();
                break;
            case 3:
                //changeStaffMember(delegation);
                break;
            case 4:
                //showStaffMember(); // ou um menu com opção para mostrar ou só um ou todos os membros
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

        //show client's menu
        cout << "1 - Add Athlete" << endl;
        cout << "2 - Change Athlete" << endl;
        cout << "3 - Remove Athlete" << endl;
        cout << "4 - View Athlete Info (by PASSPORT)" << endl;
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
                //delegation.showAthlete();
                break;
            case 5:
                //agency.showAllAthletes();
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
        cout << "\t\t   Athletes Options " << endl;
        cout << "_____________________________________________________" << endl << endl;

        //show client's menu
        cout << "1 - Add Athlete" << endl;
        cout << "2 - Change Athlete" << endl;
        cout << "3 - Remove Athlete" << endl;
        cout << "4 - View Athlete Info (by PASSPORT)" << endl;
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
                //delegation.showAthlete();
                break;
            case 5:
                //agency.showAllAthletes();
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}