#include "../include/AI.h"

AI::AI()
{
    depth = 4;
    name="IA";
}

AI::~AI()
{
    //dtor
}

AI::AI(string n, int d)
{
    this->name = n;
    depth = d;
}

int AI::getDepth() const
{
    return depth;
}

string AI::getType() const
{
    return "AI";
}
