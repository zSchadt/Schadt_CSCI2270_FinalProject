#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#define FILENAME "towns.txt"

struct TownNode;

struct adjTown {
    
    TownNode *next;
    int weight;
    
};

struct TownChar {
    
    int monsterCount;
    int reward;
    std::string difficulty;
    
};

struct TownNode {
    
    TownNode *parent = NULL;
    int distance;

    TownChar *define = new TownChar;
    std::string name;
    bool visited;
    bool beaten = false;
    std::vector<adjTown> adj;
    
    TownNode(std::string cityName) {
        name = cityName;
    }
    
};

class Map {
public:
    Map();
    
    void addVertex(std::string cityName);
    void addAdjVertex(TownNode *adjacent, int weight);
    
    TownNode *getStartTown();
    void addTownChar(TownNode *temp);
    void townGenerator();
    
    virtual ~Map();
private:
    TownNode *findTownLocation(std::string townName);
    
    std::vector<TownNode *> vertices;
    std::vector<std::string> towns;
    
};

#endif /* MAP_H */

