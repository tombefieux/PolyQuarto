#include "../include/Pawn.h"
#include <iostream>
#include <string>

using namespace std;

Pawn::Pawn(bool bright, bool small, bool square, bool hollow)
{
    this->bright = bright;
    this->small = small;
    this->square = square;
    this->hollow = hollow;
    this->playable = true;

    loadTextureFromAttributes();
}

Pawn::~Pawn()
{

}

bool Pawn::getPlayable() const
{
    return this->playable;
}


void Pawn::setPlayable(bool p)
{
    this->playable = p;
}


vector<bool> Pawn::inCommon(Pawn * p)
{
    vector<bool> temp;

    temp.push_back(this->bright==p->bright);
    temp.push_back(this->small==p->small);
    temp.push_back(this->square==p->square);
    temp.push_back(this->hollow==p->hollow);

    return temp;
}


void Pawn::inCommon(vector<bool> &commonPoints, const vector<bool> &pointsValue)
{
    vector<bool> tempP = this->getPoints();
    for (int i =0; i<4; i++)
    {
        if (commonPoints[i])
        {
            if(tempP[i] != pointsValue[i])
                commonPoints[i] = false;
        }
    }

 /*   if (this->bright==pointsValue[0])
        commonPoints[0]=true;
    else commonPoints[0]=false;
    if (this->small==commonPoints[1])
        commonPoints[1]=true;
    else commonPoints[1]=false;
    if (this->square==commonPoints[2])
        commonPoints[2]=true;
    else commonPoints[2]=false;
    if (this->hollow==commonPoints[3])
        commonPoints[3]=true;
    else commonPoints[3]=false;
*/
}


vector<bool> Pawn::getPoints()
{
    vector<bool> temp;
    temp.push_back(this->bright);
    temp.push_back(this->small);
    temp.push_back(this->square);
    temp.push_back(this->hollow);
    return temp;
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
