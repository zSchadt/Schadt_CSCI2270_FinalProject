#include "Map.h"

using namespace std;

Map::Map() {
}

/*
 * This function will read in a file 'towns.txt' and store the names of the 
 * towns read in in the towns vector
 * The function then procedes to randomly assign the cities their adjacencies to
 * create the map 
 */
void Map::townGenerator() {
    
    ifstream infile;
    infile.open(FILENAME);
    
    if (!infile.good()) {
        cout << "Failed to generate town!" << endl;
        return;   
    }
    
    string tempCity;
    
    while(getline(infile, tempCity)) {
        
        towns.push_back(tempCity);
        
    }infile.close();
    
    int randomAdjTown;
    int randomDistance;

    srand(time(NULL));
    
    for (int i = 0; i < towns.size(); i++) {
        
        TownNode *tempCity = new TownNode(towns[i]);

        addTownChar(tempCity);

        if (vertices.size() == 0) { //checking if their are any cities;
            vertices.push_back(tempCity);
        } else {
            
            randomAdjTown = rand() % vertices.size(); //generates index for town
            randomDistance = rand() % 900 + 100; //generates a distance at random
            
            adjTown instance;
            instance.weight = randomDistance;
            
            //adding edge to parent node
            instance.next = tempCity;
            vertices[randomAdjTown]->adj.push_back(instance);
            
            //adding edge in other direction
            instance.next = vertices[randomAdjTown];
            tempCity->adj.push_back(instance);
            
            vertices.push_back(tempCity);
            
        }
        
    }
    
}

/*
 * The addTownChar function will randomly generate a difficulty for each tpwn
 * -- The number of monsters and reward is directly related to the difficulty --
 */
void Map::addTownChar(TownNode *temp) {
    
    int randDifficulty = rand() % 3 + 1;
    int diffMultiplier;

    switch (randDifficulty) {
        case 1:
            temp->define->difficulty = "Easy";
            diffMultiplier = 1;
            break;
        case 2:
            temp->define->difficulty = "Normal";\
            diffMultiplier = 2;
            break;
        case 3:
            temp->define->difficulty = "Hard";
            diffMultiplier = 3;
            break;
    }
   
    int monsterCount = rand() % 6 + 5;
    int rewardVal = rand() % 400 + 101;

    temp->define->monsterCount = (monsterCount * diffMultiplier);
    temp->define->reward = (rewardVal * diffMultiplier);
    
}

Map::~Map() {
}
