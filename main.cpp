#include <iostream>
#include "Character.h"
#include "Map.h"

using namespace std;

int main(int argc, char** argv) {

    //Character *User = new Character;
    
    Map *Create = new Map;
    Create->townGenerator();
    
    return 0;
    
}
