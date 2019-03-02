#ifndef PAWN_H
#define PAWN_H
#include <iostream>
#include <string>

using namespace std;


class Pawn
{
private:
    bool bright, small, square, hollow;

public:
    Pawn(){};
    Pawn(bool bright, bool small, bool square, bool hollow);
    ~Pawn(){};

};

#endif // PAWN_H
