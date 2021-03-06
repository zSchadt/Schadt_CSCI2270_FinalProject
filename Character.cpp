/*
 This Class is for the controlling of your character
 */
#include "Character.h"

using namespace std;

Character::Character() {
    
    makeMe();
    
}

void Character::store() {
    
    string decision;
    
    while (decision != "3"){
        
        cout << "Welcome to the store!" << endl;
        cout << "## \nYou have " << UserCharacter->gold << " gold!" << endl;
        cout << "1. Damage Enchantment: 100 coins" << endl;
        cout << "2. Health Enchantment: 100 coins" << endl;
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
                    UserCharacter->maxHealth = UserCharacter->maxHealth + 30;
                    
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
    location->visited = true;
    visited.push_back(location);
    
}

TownNode *Character::getCurrentLocation() {
    return location;
}

void Character::addLoot(Nemesis *item) {
    
    cout << "The " << item->type << " was carrying a " << item->item.itemName << endl;
    cout << "It gives bonus: " << endl;
    if (item->item.strength != 0) { 
        cout << "Strength: " << item->item.strength << endl;
    }
    if (item->item.health != 0) {
        cout << "Health: " << item->item.health << endl;
    }
    if (item->item.crit != 0) {
        cout << "This item also has " << item->item.crit << " Critical Strike";
        cout << "... Critical Strike is very rare!" << endl;
    }
    
    string decision;
    cout << "===============" << endl;
    cout << "Do you want to take this item?" << endl;
    cout << "1. Yes!" << endl;
    cout << "2. No, leave it" << endl;
    getline(cin, decision);
    
    if (decision == "1") {
        
        if (UserCharacter->inventorySize < 6) {
            
            UserCharacter->maxHealth = UserCharacter->maxHealth + item->item.health;
            UserCharacter->health = UserCharacter->health + item->item.health;
            UserCharacter->strength = UserCharacter->strength + item->item.strength;
            UserCharacter->criticalStrike = UserCharacter->criticalStrike + item->item.crit;
            
            UserCharacter->inventory[UserCharacter->inventorySize] = item->item;
            
            UserCharacter->inventorySize = UserCharacter->inventorySize + 1;
            
        } else {
            
            cout << "Your inventory is full, please choose which item you would like to replace" << endl;
            
            for (int i = 0; i < UserCharacter->inventorySize; i++) {
               cout << UserCharacter->inventory[i].itemName << ":" << endl;
               cout << "Strength: " << UserCharacter->inventory[i].strength << endl;
               cout << "Health: " << UserCharacter->inventory[i].health << endl;
               if (UserCharacter->inventory[i].crit != 0) {
                   cout << "Critical Strike: " << UserCharacter->inventory[i].crit << endl;
               }
               cout << endl;
            }   
            
            string choice;
            if (choice != "cancel") {
                
                cout << "Type the name of the item you would like to replace (type 'cancel' if you do not want to replace any items): "<<endl;
                getline(cin,choice);
                
                if (choice == "cancel") {
                    cout << "You decided to leave the item." << endl;
                    return;
                }
                
                for (int i = 0; i < 6; i++) {//looping through inventory
                    
                    if (choice == UserCharacter->inventory[i].itemName) {
                        cout << UserCharacter->inventory[i].itemName << " has been removed ";
                        cout << "and " << item->item.itemName << " has been added!" << endl;
                        
                        UserCharacter->inventory[i] = item->item;
                                    
                        UserCharacter->maxHealth = UserCharacter->maxHealth + item->item.health;
                        UserCharacter->health = UserCharacter->health + item->item.health;
                        UserCharacter->strength = UserCharacter->strength + item->item.strength;
                        UserCharacter->criticalStrike = UserCharacter->criticalStrike + item->item.crit;
                        
                        return;
                        
                    }
                    
                }
            
            }
            
        }
        
    }
    
}

void Character::fight(TownNode *Instance) {
    
    Nemesis *fighter = generateEnemy();
    Char *You = UserCharacter;
    int criticalStrike;
    
    if (Instance->beaten) {
        cout << "You have defeated all of the enemies in " << Instance->name << endl;
        return;
    }
    
    cout << "=====Battle Log=====" << endl;
    
    while(You->alive && fighter->alive && Instance->define->monsterCount > 0) {
        
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
            cout << "You killed the " << fighter->type << "!" << endl;
            Instance->define->monsterCount = Instance->define->monsterCount - 1;
            fighter->alive = false;
        } else {
            cout << "Nice hit!" << endl;
            cout << "The " << fighter->type << " still has " << fighter->health << " health left!" << endl;
        }
        
        if (fighter->alive) {
            
            int monsterDamage = fighter->strength;
            
            cout << "The " << fighter->type << " attacks back and deals " << fighter->strength << " damage!\n" << endl;
            You->health = You->health - fighter->strength;
            
            if (You->health < 1) {
                cout << "Ohh no! You have died" << endl;
                You->alive = false;
            } else {
                cout << "You have " << You->health << " health remaining!" << endl;

            }
             
        }
        
    }
    
    cout << "=================" << endl;
    
    if (Instance->define->monsterCount < 1) {
        
        cout << "Congratulations, you have defeated all of the enemies in ";
        cout << Instance->name << "!" << endl;
        cout << "You have won " << (Instance->define->reward) << " gold!" << endl;
        
        UserCharacter->gold = Instance->define->reward + UserCharacter->gold;
        
        Instance->beaten = true;
        
    }
    
    if (!fighter->alive) {
        
        if (fighter->item.have) {
            addLoot(fighter);
        }
        
        cout << "The " << fighter->type << " had " << fighter->coinage << "!" << endl;
        You->gold = You->gold + fighter->coinage;
        cout << "You now have " << You->gold << " gold!" << endl;
        cout << "==============\n" << endl;
        
        UserCharacter = You;

    } else { //If you died
        //the next functions called will deal with respawning the character
        UserCharacter = You;
        respawn();
    }
    
}

void Character::respawn() {
    
    cout << "You are dead. In order to revive you must pay 100 coins" << endl;
    cout << "You should really heal if you are low on health, it is much less ";
    cout << "taxing." << endl << endl;
    
    if (UserCharacter->gold < 100) {
        
        cout << "You Have insufficient funds!" << endl;
        cout << "===GAME OVER===" << endl;
        
    } else {
        
        UserCharacter->gold = UserCharacter->gold - 100;
        
        cout << "You now have " << UserCharacter->gold << " gold." << endl;
        cout << "Be careful next time!" << endl;
        cout << "==================" << endl;
        
        UserCharacter->health = UserCharacter->maxHealth;
        UserCharacter->alive = true;
        
    }
    
}

void Character::heal() {
    
    int cost = ((UserCharacter->maxHealth - UserCharacter->health) / 20);
    string decision;
    
    cout << "Welcome to the healing center!" << endl;
    cout << "You are currently at " << UserCharacter->health << " out of "; 
    cout << UserCharacter->maxHealth << " max health points." << endl;
    cout << "It will cost " << cost << " gold to heal you to full health!" << endl;
    cout << "Would you like to heal?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    getline(cin, decision);
    
    if (decision == "1") {
        
        if (UserCharacter->gold < cost) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        
        UserCharacter->health = UserCharacter->maxHealth;
        UserCharacter->gold = UserCharacter->gold - cost;
        
        cout << "You now have " << UserCharacter->health << "(full) health!" << endl;
        cout << UserCharacter->gold << " gold remaining." << endl;
        cout << "See you next time!" << endl;
        
    } else {
        cout << "Good luck out there!" << endl;
    }
    
}

bool Character::getALife() {
    return UserCharacter->alive;
}

void Character::travel() {
    
    cout << "You are currently in " << location->name << endl;
    cout << "===Where to go===" << endl;
    for (int i = 0; i < (location->adj.size()); i++) {
        cout << location->adj[i].next->name << " :: ";
        cout << ((location->adj[i].weight)/10) << " miles away" << endl;
    }
    cout << "Insert the name of where you want to go (insert 'cancel' if you wish to stay put): " << endl;
    cout << "** For fast travel options insert '1' **" << endl;
    string decision;
    getline(cin, decision);
    
    if (decision == "cancel") {
        return;
    }
    if (decision == "1") {
        
        cout << endl << "Where would you like to travel too?" << endl;
        for (int i = 0; i < visited.size(); i++) {
            cout << visited[i]->name << endl;
        }
        cout << "Enter the name of where you want to go (costs 10 gold)." << endl;
        cout << "Enter 'cancel' if you wish to leave." << endl;
        getline(cin, decision);
        
        if (decision == "cancel") {
            cout << "Safe travels." << endl;
            return;
        }
        else {
            for (int i = 0; i < visited.size(); i++) {
                if (visited[i]->name == decision) {
                    
                    UserCharacter->gold = UserCharacter->gold - 10;
                    
                    cout << "You are now leaving " << location->name << " and traveling to ";
                    cout << visited[i]->name << endl;
                    cout << "You have " << UserCharacter->gold << " gold left!" << endl << endl;
                    location = visited[i];
                    return;
                    
                }
            }
        }
               
        return;
    }
    for (int i = 0; i < (location->adj.size()); i++) {
        if (decision == (location->adj[i].next->name)) {
            cout << "You are now leaving " << location->name << " and traveling to ";
            cout << location->adj[i].next->name << endl << endl;
            location = location->adj[i].next;
            location->visited = true;
            visited.push_back(location);
        }
    }
    
}

void Character::getInfo() {
    
    cout << "\n===Current Game Information===" << endl;
    cout << "Username: " << UserCharacter->userName << endl;
    cout << "Type: " << UserCharacter->charType << endl;
    cout << "====Statistics====" << endl;
    cout << "Strength: " << UserCharacter->strength << endl;
    cout << "Current Health: " << UserCharacter->health << endl;
    cout << "Maximum Health: " << UserCharacter->maxHealth << endl;
    cout << "Critical Strike Chance: " << UserCharacter->criticalStrike << " %\n";
    cout << "===Location===" << endl;
    cout << location->name << endl;
    cout << "Monsters left: " << location->define->monsterCount << endl;
    
    if (UserCharacter->inventorySize != 0) {
        cout << "====Inventory====" << endl;
        
        for (int i = 0; i < UserCharacter->inventorySize; i++) {
            cout << UserCharacter->inventory[i].itemName << endl;
            if (UserCharacter->inventory[i].health == 0) {
                cout << "Strength: " << UserCharacter->inventory[i].strength << endl;
            } else {
                cout << "Health: " << UserCharacter->inventory[i].health << endl;
            }
            if (UserCharacter->inventory[i].crit != 0) {
                cout << "Critical Strike Chance: " << UserCharacter->inventory[i].crit << endl;
            }
            
            if ((i + 1) < UserCharacter->inventorySize) {
                cout << endl;
            }
           
        }
    }
    
    cout << "=========================\n" << endl;

}

Nemesis *Character::generateEnemy() { //monster user will be fighting
    
    int type = rand() % Monsters.size();
    
    Nemesis *monster = new Nemesis(Monsters[type]);
    
    type = rand() % 600 + 250;//health
    monster->health = type;
    type = rand() % 60 + 30;//strength
    monster->strength = type;
    type = rand() % 20 + 5;//coins for kill
    monster->coinage = type;
    
    type = rand() % 100 + 1 ;
    if (type < 49) {//chance the monster has an item
        
        monster->item.have = true;
        
        type = rand() % Weapons.size();
        monster->item.itemName = Weapons[type];
        type = rand() % 100 + 1;
        if (type < 15) {
            type = rand() % 16 + 5;
            monster->item.crit = type;
        } else {
            monster->item.crit = 0;
        }
        
        if (rand() % 2) {
            type = rand() % 20 + 5;
            monster->item.strength = type;
            monster->item.health = 0;
        } else {
            type = rand() % 50 + 5;
            monster->item.health = type;
            monster->item.strength = 0;
        }
        
    } else {
        //monster will not have an item
        monster->item.have = false;
        
    }
    
    return monster;
     
}

void Character::monstLootFileRead() {
    
    ifstream infile;
    string temp;
    infile.open(MONSTNAMES);
    
    if (!infile.good()) {
        
        cout << "Monster Names Not Found!" << endl;
        return;
        
    } else {
        
        while (getline(infile,temp)) {
            
            Monsters.push_back(temp);
            
        }
        infile.close();
    }
    
    ifstream otherInfile;
    otherInfile.open(WEAPONNAMES);
    
    if (!otherInfile.good()) {
        cout << "Weapon Names not found!" << endl;
        return;
    } else {
        
        while (getline(otherInfile, temp)) {
            Weapons.push_back(temp);
        }
        otherInfile.close();
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
    while (type != "1" && type != "2" & type != "3") {
        cout << "Incorrect input!" << endl;
        getline(cin, type);
    }
    int type_pass = stoi(type);
    
    UserCharacter = new Char(name, type_pass);
    
}

Character::~Character() {
    
    delete UserCharacter;
    
}

