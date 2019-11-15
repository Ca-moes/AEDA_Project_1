//
// Created by Diana Freitas on 20/10/2019.
//

#include "Menus.h"
#include <regex>
#include <unistd.h>

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
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(14) << " " << delegation.getCountry() << "'s Olympic Delegation - Tokyo 2020" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "Choose an option by typing a number and pressing Enter." << endl << endl;
        //show the main menu
        cout << "1 - Members" << endl;
        cout << "2 - Sports Competitions" << endl;
        cout << "3 - Trials Calendar"<<endl;
        cout << "4 - Medals Statistics" << endl;
        /*cout << "5 - History" << endl;*/
        cout << "0 - EXIT" << endl;
        //checking if option is valid
        do {
            testinput = checkinputchoice(input, 0, 4);
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
                trialsMenu(delegation);
                break;
            case 4:
                medalsStatisticsMenu(delegation);
                break;
            default:
                break;
        }

    } while (stoi(input) != 0);
}

//submenus - participants, sports, medals statistics, history
void participantsMenu(Delegation & delegation) {
    int testinput = 0;
    string input;
    do
    {
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(27) << " "<<"Members Options" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

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
                    delegation.sortAllPeople();
                    delegation.showMembers();
                }catch(NoMembers & e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 0:
                break;
            default:
                break;
        }
    } while (stoi(input) != 0);
}
void sportsMenu(Delegation & delegation) {
    int testinput = 0;
    string input,option;
    do
    {
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(28) << " "<<"Sports Options" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

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

        if(stoi(input) != 0) {
            option = "1";
        } else {
            option = "0";
        }
      
        switch (stoi(option)) {
            case 1:
                try{
                    competitionsMenu(delegation,delegation.getSports()[stoi(input)-1]->getName());
                }
                catch(NonExistentSport & s){
                    cout << s;
                    exceptionHandler();
                }
                break;
            case 0:
                break;
            default:
                break;
        }
    } while (stoi(option) != 0);
}
void trialsMenu(Delegation & delegation){
    int testinput = 0;
    string input;
    do
    {
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(27) << " "<<"Trials Calendar" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "1 - All Trials" << endl;
        cout << "2 - Trials by day" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 3);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                try{
                    delegation.showAllTrials();
                }catch(NoTrials & e){
                    cout<< e;
                    exceptionHandler();
                }
                catch(NoSports & e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 2:
                try{
                    delegation.showTrialsInDay();
                }catch(NoTrials & e){
                    cout<< e;
                    exceptionHandler();
                }
                catch(NoSports & e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}
void medalsStatisticsMenu(Delegation & delegation){
    int testinput = 0;
    string input;
    do
    {
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(26) << " "<<"Medals Statistics" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "1 - All Medals" << endl;
        cout << "2 - Medals by country" << endl;
        cout << "3 - Medals Rankings" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 3);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                try{
                    delegation.showAllMedals();
                }catch(NoMedals & e){
                    cout<< e;
                    exceptionHandler();
                }
                break;
            case 2:
                try{
                    delegation.showCountryMedals();
                }catch(NoMedals & e){
                    cout<< e;
                    exceptionHandler();
                }
                break;
            case 3:
                medalRankingsMenu(delegation);
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
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(27) << " "<<"Staff's Options" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

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
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 2:
                try{
                    delegation.removeStaffMember();
                }
                catch(NonExistentStaff & e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 3:
                try{
                    delegation.changeStaffMember();
                }
                catch(NonExistentStaff & e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 4:
                try{
                    delegation.showStaffMember();
                }
                catch(NonExistentStaff & e){
                    cout << e;
                    exceptionHandler();
                }
                catch(NoMembers & n){
                    cout << n;
                    exceptionHandler();
                }
                break;
            case 5:
                try{
                    delegation.showStaffMembers();
                }
                catch(NonExistentPerson & e){
                    cout << e;
                    exceptionHandler();
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
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(27) << " "<<"Athletes Options" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "1 - Add Athlete" << endl;
        cout << "2 - Remove Athlete" << endl;
        cout << "3 - Change Athlete" << endl;
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
                try {
                    delegation.addAthlete();
                }
                catch(PersonAlreadyExists &e) {
                    cout << e;
                    exceptionHandler();
                }
                catch(NonExistentSport &e) {
                    cout << e;
                    exceptionHandler();
                }
                catch(NonExistentTeam &e) {
                    cout << e;
                    exceptionHandler();
                }
                catch(FullTeam &e){
                    cout << e;
                    exceptionHandler();
                }
                delegation.calculateTotalCost();
                delegation.sortAllPeople();
                break;
            case 2:
                try {
                    delegation.sortAllPeople();
                    delegation.removeAthlete();
                }
                catch (NonExistentAthlete &e){
                    cout << e;
                    exceptionHandler();
                }
                break;
            case 3:
                try {
                    delegation.sortAllPeople();
                    delegation.changeAthlete();
                } catch (NonExistentAthlete &e){
                    cout << e;
                    exceptionHandler();
                } catch (NonExistentSport &e){
                    cout << e;
                    exceptionHandler();
                } catch (NonExistentTeam &e){
                    cout << e;
                    exceptionHandler();
                } catch (FullTeam &e){
                    cout << e;
                    exceptionHandler();
                }
                delegation.sortAllPeople();
                delegation.calculateTotalCost();
                break;
            case 4:
                try{
                    delegation.showAthlete();
                }
                catch(NonExistentAthlete & e){
                    cout << e;
                    exceptionHandler();
                }
                catch(NoMembers & n){
                    cout << n;
                    exceptionHandler();
                }
                break;
            case 5:
                try{
                    delegation.sortAllPeople();
                    delegation.showAllAthletes();
                }
                catch(NoMembers & n){
                    cout << n;
                    exceptionHandler();
                }
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
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------"<< endl;
        cout << setw(28) << " "<<"Teams Options" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "1 - View Team Info" << endl;
        cout << "2 - View All Teams Info" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 2);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                try{
                    delegation.showTeam();
                }
                catch(NonExistentTeam & t){
                    cout<< t;
                    exceptionHandler();
                }
                catch(NoMembers & e){
                    cout<< e;
                    exceptionHandler();
                }
                break;
            case 2:
                try{
                    delegation.showAllTeams();
                }
                catch(NoMembers & e){
                    cout<< e;
                    exceptionHandler();
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}

//Sports submenus
void competitionsMenu(Delegation & delegation, const string & sport){
    int testinput = 0;
    string input;
    do
    {
        system("cls");
        cout << "----------------------------------------------------------------------" << endl;
        int space = (70-(sport.size()+24))/2;
        cout << setw(space)<<" "<< sport << " - Competitions & Trials" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "Choose an option by typing a number and pressing Enter." << endl << endl;
        //show the main menu
        cout << "1 - Competition information" << endl;
        cout << "2 - All Competitions" << endl;
        cout << "3 - All Trials" << endl;
        cout << "0 - EXIT" << endl;

        do {
            testinput = checkinputchoice(input, 0, 3);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }


        switch (stoi(input)) {
            case 1:
                try{
                    delegation.showCompetition(sport);
                }
                catch(NonExistentCompetition & c){
                    cout << c;
                    exceptionHandler();
                }
                catch(NoCompetitions & c){
                    cout << c ;
                    exceptionHandler();
                }
                break;
            case 2:
                try{
                    delegation.showAllCompetitions(sport);
                }
                catch(NoCompetitions & c){
                    cout << c;
                    exceptionHandler();
                }
                break;
            case 3:
                try{
                    delegation.showAllTrials(sport);
                }
                catch(NoTrials & c){
                    cout << c;
                    exceptionHandler();
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}

//Medals Statistics Submenus
void medalRankingsMenu(Delegation & delegation){
    int testinput = 0;
    string input;
    do
    {
        if (system("CLS")) system("clear");
        cout << "----------------------------------------------------------------------" << endl;
        cout << setw(27) << " " <<"Medals Rankings" << endl;
        cout << "----------------------------------------------------------------------" << endl << endl;

        cout << "1 - Most awarded countries (total of medals)" << endl;
        cout << "2 - Most awarded countries (gold medals)" << endl;
        cout << "3 - Most awarded athletes" << endl;
        cout << "0 - BACK" << endl;

        do {
            testinput = checkinputchoice(input, 0, 3);
            if (testinput != 0 && testinput != 2)
                cerr << "Invalid option! Please try again." << endl;
        } while (testinput != 0 && testinput != 2);
        if (testinput == 2)
        { input = "0"; }

        switch (stoi(input)) {
            case 1:
                try{
                    delegation.mostAwardedCountries();
                }
                catch(NoMedals & e){
                    cout << e;
                }
                break;
            case 2:
               try{
                   delegation.mostAwardedGold();
               }
               catch(NoMedals & e){
                   cout << e;
               }
               break;
            case 3:
                try{
                    delegation.mostAwardedAthletes();
                }
                catch(NoMedals & e){
                    cout << e;
                }
                break;
            case 0:
                break;
        }
    } while (stoi(input) != 0);
}