#include "GameEngine.h"
#include <iostream>
#include <string>

using namespace std;


GameEngine::GameEngine(string P1, string P2)
{
    this->P1 = new Player(P1);
    this->P2 = new Player(P2);
    this->grid.resize(4);
    for(int i = 0; i<4; i++) this->grid[i].resize(4);
}
