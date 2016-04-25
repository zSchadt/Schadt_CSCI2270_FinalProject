#include <iostream>
#include "Character.h"
#include "Map.h"

using namespace std;

int mainMenu(Character *instance) {
    
    string townName = (instance->getCurrentLocation())->name;
    string decision;
    
    cout << "You are currently in " << townName << endl;
    cout << "1. Fight" << endl;
    cout << "2. Heal" << endl;
    cout << "3. Store" << endl;
    cout << "4. Travel" << endl;
    cout << "5. Game Statistics" << endl;
    cout << "6. Quit" << endl;
    getline(cin, decision);
    
    return stoi(decision);
    
}

int main(int argc, char** argv) {

    cout << "Welcome to The End!" << endl;
    
    //The following are all initializations
    Character *User = new Character;
    Map *Create = new Map;
    Create->townGenerator();
    User->setCurrentLocation((Create->getStartTown()));
    User->monstLootFileRead();
    
    int decision;
    while ((User->getALife()) && (decision = mainMenu(User)) != 6 ) {
        
        switch(decision) {
            case 1:
                User->fight(User->getCurrentLocation());
                break;
                
            case 2:
                User->heal();
                break;
                
            case 3:
                User->store();
                break;
                
            case 4:
                User->travel();
                break;
                
            case 5:
                User->getInfo();
                break;

            default:
                cout << "Incorrect Input" << endl;
                break;
        }
        
    }
    
    
    return 0;
}

