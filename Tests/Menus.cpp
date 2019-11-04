//
// Created by Diana Freitas on 20/10/2019.
//

#include "Menus.h"
#include <regex>

using namespace std;

int checkinputchoice(string& test, int lowerlimit, int upperlimit) {
    // e.g. ll = 0, ul = 3 , se num < 0 || num > 3    return 1
    do {
        getline(cin, test);
        if (cin.eof()) {
            cin.clear();
            return 2;
        }

    } while (test.length() == 0);
    test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
    for (unsigned int i = 0; i < test.length(); i++)
    {
        if (!isdigit(test[i]))
            return 1;
    }
    if (stoi(test) < lowerlimit || stoi(test) > upperlimit)
        return 1;
    return 0;
}

void mainMenu(Delegation &delegation){
    int testinput = 0;
    string input = "";
    do
    {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t" << delegation.getCountry() << "'s Olympic Delegation - Tokyo 2020" << endl;
        cout << "_____________________________________________________" << endl << endl;

        cout << "Choose a option by typing a number and pressing Enter." << endl << endl;
        //show the main menu
        cout << "1 - Athletes" << endl;
        cout << "2 - Staff" << endl;
        cout << "3 - Sports Competitions" << endl;
        cout << "4 - Results" << endl;
        cout << "0 - EXIT" << endl;
        //checking if option is valid
        do {
            testinput = checkinputchoice(input, 0, 4);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }
        if (testinput == 2)
            input = "0";
        switch (stoi(input)) {
            case 1:
                //clientsMenu(agency);
                break;
            case 2:
                //packetsMenu(agency);
                break;
            case 3:
                //statisticsMenu(agency);
                break;
            case 0:
                //AgencyToFile(agencychoice);
                //agency.saveClients();
                //agency.savePackets();
                break;
        }
    } while (stoi(input) != 0);
}