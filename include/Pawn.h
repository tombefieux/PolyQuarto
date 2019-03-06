#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Config.h"

using namespace std;


class Pawn
{
    private:
        bool bright, small, square, hollow;

        // graphics
        sf::Texture texture;           /** The texture of the pawn. */

    public:
        Pawn(){};
        Pawn(bool bright, bool small, bool square, bool hollow);
        ~Pawn();

        /**
        * Getter of the texture of the pawn.
        * @return the texture of the pawn
        */
        sf::Texture* getTexture();


    private:
        // graphics
        /**
        * This function loads the good texture with the attributes value.
        */
        void loadTextureFromAttributes();
        vector<bool> inCommon(Pawn*);
        vector<bool> inCommon(vector<Pawn>);

};

#endif // PAWN_H
