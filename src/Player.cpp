#include "../include/Player.h"
#include <iostream>
#include <string>

using namespace std;


Player::Player(string name)
{
    this->name = name;
}


string Player::getName() const
{
    return this->name;
}

string Player::getType() const
{
    return "HUMAN";
}
