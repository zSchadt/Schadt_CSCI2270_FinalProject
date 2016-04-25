#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include "Map.h"
#define MONSTNAMES "monsterNames.txt"
#define WEAPONNAMES "weapons.txt"

struct Loot {
    
    std::string itemName;
    int strength;
    int crit;
    int health;
    bool have;
    
};

struct Nemesis {
    
    int health;
    std::string type;
    int strength;
    int coinage;
    bool alive = true;
    
    Loot item;
    
    Nemesis(std::string name) {
        type = name;
    }
    
};

struct Char {
    
    std::string userName;
    std::string charType;
    int health = 500;
    int maxHealth;
    int strength;
    int criticalStrike = 0;
    int gold = 250;
    bool visited = false;
    bool alive = true;
    
    Loot inventory[6];
    int inventorySize = 0;
    
    Char(std::string name, int type) {
        
        userName = name;
        
        switch(type) {
            case 1:
                //user chose knight
                strength = 60;
                health = health + 100;
                maxHealth = health;
                break;
            case 2:
                //user chose Wizard
                strength = 80;
                health = health + 50;
                maxHealth = health;
                break;
            case 3:
                //user is ogre
                strength = 50;
                health = health + 200;
                maxHealth = health;
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
    void respawn();
    void travel();
    void getInfo();
    void heal();
    void addLoot(Nemesis *item);
    void setCurrentLocation(TownNode *temp);
    TownNode* getCurrentLocation();
    bool getALife();
    
    void monstLootFileRead();
    virtual ~Character();
    
private:
    Nemesis *generateEnemy();
    TownNode *location;
    std::vector<TownNode *> visited;
    std::vector<std::string> Monsters;
    std::vector<std::string> Weapons; 
    Char *UserCharacter;

};

#endif /* CHARACTER_H */

