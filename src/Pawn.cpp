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
