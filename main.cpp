#include <iostream>
#include "Tests/Menus.h"

using namespace std;

int main() {
    cout << "AEDA 2019/2020 - Project 1" << endl;
    try{
        Delegation portugueseDelegation;
    }
    catch(FileError & e){
        exit(1);
    }
    catch(FileStructureError & s){
        exit(1);
    }

    return 0;
}