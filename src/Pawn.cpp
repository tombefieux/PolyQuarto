#include "Pawn.h"
#include <iostream>
#include <string>

using namespace std;

Pawn::Pawn(bool bright, bool small, bool square, bool hollow)
{
    this->bright = bright;
    this->small = small;
    this->square = square;
    this->hollow = hollow;

    loadTextureFromAttributes();
}

Pawn::~Pawn()
{

}

vector<bool> Pawn::inCommon(Pawn * p)
{
    vector<bool> temp;
    if (this->bright==p->bright)
        temp.push_back(true);
    else temp.push_back(false);
    if (this->small==p->small)
        temp.push_back(true);
    else temp.push_back(false);
    if (this->square==p->square)
        temp.push_back(true);
    else temp.push_back(false);
    if (this->hollow==p->hollow)
        temp.push_back(true);
    else temp.push_back(false);
    return temp;
}


void Pawn::inCommon(vector<bool> &commonPoints)
{

    if (this->bright==commonPoints[0])
        commonPoints[0]=true;
    else commonPoints[0]=false;
    if (this->small==p->commonPoints[1])
        commonPoints[1]=true;
    else commonPoints[1]=false;
    if (this->square==p->commonPoints[2]))
        commonPoints[2]=true;
    else commonPoints[2]=false;
    if (this->hollow==p->commonPoints[3]))
        commonPoints[3]=true;
    else commonPoints[3]=false;

}


sf::Texture* Pawn::getTexture()
{
    return &this->texture;
}

void Pawn::loadTextureFromAttributes()
{
    string path = IMAGES_PATH;

    if(this->bright)
        path += "player1Pawns/";
    else
        path += "player2Pawns/";

    if(this->square)
        path += "squares/";
    else
        path += "circles/";

    if(this->small)
        path += "little";
    else
        path += "big";

    if(this->hollow) path += "Hole";

    path += ".png";

    this->texture.loadFromFile(path);
}
