#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include "Map.h"
#define MONSTNAMES "monsterNames.txt"

struct Loot {
    
    std::string itemName;
    int strength;
    
};

struct Nemesis {
    
    int health;
    std::string type;
    int strength;
    int coinage;
    bool alive;
    
    Nemesis(std::string name) {
        type = name;
    }
    
};

struct Char {
    
    std::string userName;
    std::string charType;
    int health = 500;
    int strength;
    int criticalStrike = 0;
    int gold = 250;
    bool alive = true;
    
    Loot *next;
    Loot *previous;
    int inventory = 6;
    
    Char(std::string name, int type) {
        
        userName = name;
        
        switch(type) {
            case 1:
                //user chose knight
                strength = 60;
                health = health + 100;
                break;
            case 2:
                //user chose Wizard
                strength = 80;
                health = health + 50;
                break;
            case 3:
                //user is ogre
                strength = 50;
                health = health + 200;
                break;
            default:
                break;
        }        
    }
    
};

class Character {
public:
    Character();
    
    void makeMe();
    void fight(TownNode *Instance);
    void store();
    void setCurrentLocation(TownNode *temp);
    
    void monstFileRead();
    virtual ~Character();
    
private:
    Nemesis *generateEnemy();
    TownNode *location;
    std::vector<std::string> Monsters;
    Char *UserCharacter;
    Loot *head;

};

#endif /* CHARACTER_H */
