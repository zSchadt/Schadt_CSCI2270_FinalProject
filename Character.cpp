#include "Character.h"

using namespace std;

Character::Character() {
    
    makeMe();
    
}

void Character::store() {
    
    string decision;
    
    while (decision != "3"){
        
        cout << "Welcome to the store!" << endl;
        cout << "## \nYou have " << UserCharacter->gold << "gold!" << endl;
        cout << "1. Damage Item: 100 coins" << endl;
        cout << "2. Health Item: 100 coins" << endl;
        cout << "3. Exit" << endl;
        getline(cin, decision);
        int choice = stoi(decision);
        
        switch (choice){
            case 1:
                if (UserCharacter->gold >= 100) {
                    UserCharacter->gold = UserCharacter->gold - 100;
                    UserCharacter->strength = UserCharacter->strength + 20;

                    cout << "The damage item costed you 100 coins ["<< UserCharacter->gold << " gold left]" << endl;
                    cout << "Your strength is now: " << UserCharacter->strength << endl;
                }
                else{
                    cout << "You don't have enough gold!" << endl;
                }
                break;
            case 2:
                if (UserCharacter->gold >= 100) {
                    UserCharacter->gold = UserCharacter->gold - 100;
                    UserCharacter->health = UserCharacter->health + 30;

                    cout << "The health item costed you 100 coins ["<< UserCharacter->gold << " gold left]" << endl;
                    cout << "Your health is now: " << UserCharacter->health << endl;
                }
                else {
                    cout << "You don't have enough gold!" << endl;
                }
                break;
            case 3:
                break;
            default: 
                cout << "Incorrect input!!!" << endl;
                break;
            
        }
        
    }
    
    cout << "See you next time!" << endl;
}

void Character::setCurrentLocation(TownNode *temp) {
    location = temp;
}

void Character::fight(TownNode *Instance) {
    
    Nemesis *fighter = generateEnemy();
    Char *You = UserCharacter;
    int criticalStrike;
    
    while(You->alive && fighter->alive) {
        
        int userDamage = You->strength;
        
        if (userDamage > 49) { //can only crit if this is true;
            
            criticalStrike = rand() % 100 + 1;
    
            if (criticalStrike < You->criticalStrike) {
                cout << "!!!CRITICAL STRIKE!!!" << endl;
                userDamage *= 3;
            }
       
        }
        
        cout << "You dealt " << userDamage << "!" << endl;
        fighter->health = fighter->health - userDamage;
        if (fighter->health < 1) {
            cout << "You killed the " << fighter->type << "!";
            fighter->alive = false;
        } else {
            cout << "Nice hit!" << endl;
            cout << "The " << fighter->type << " still has " << fighter->health << " left!" << endl;
        }
        
        if (fighter->alive) {
            
            int monsterDamage = fighter->strength;
            
            cout << "The " << fighter->type << " attacks back and deals " << fighter->strength << " damage!" << endl;
            You->health = You->health - fighter->strength;
            
            if (You->health < 1) {
                cout << "Ohh no! You have died" << endl;
                You->alive = false;
            }
             
        }
        
    }
    
    if (!fighter->alive) {
        
        cout << "The goblin had " << fighter->coinage << "!" << endl;
        You->gold = You->gold + fighter->coinage;
        cout << "You now have " << You->gold << " gold!" << endl;
        
        Instance->define->monsterCount = Instance->define->monsterCount - 1;
        UserCharacter = You;

    } else { //If you died
        //the next functions called will deal with respawning the character
    }
    
}

Nemesis *Character::generateEnemy() { //monster user will be fighting
    
    int type = rand() % Monsters.size(); 
    Nemesis *monster = new Nemesis(Monsters[type]);
    
    type = rand() % 600 + 250;//health
    monster->health = type;
    type = rand() % 60 + 30;//strength
    monster->strength = type;
    type = rand() % 20;//coins for kill
    monster->coinage = type;
    
    return monster;
     
}

void Character::monstFileRead() {
    
    ifstream infile;
    infile.open(MONSTNAMES);
    
    if (!infile.good()) {
        
        cout << "Monster Names Not Found!" << endl;
        return;
        
    } else {
        
        string temp;
        
        while (getline(infile,temp)) {
            
            Monsters.push_back(temp);
            
        }
        
    }
    
}

void Character::makeMe() {
    
    string name;
    string type;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "What type of warrior would you like to be?" << endl;
    cout << "1. Knight \n2. Wizard \n3. Ogre" << endl;
    getline(cin, type);
    int type_pass = stoi(type);
    
    UserCharacter = new Char(name, type_pass);
    
}

Character::~Character() {
    
    delete UserCharacter;
    
}
