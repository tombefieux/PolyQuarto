#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Pawn.h"
#include "Player.h"
#include "Config.h"

class GameEngine
{
    private:
        std::vector< vector<Pawn> > grid;
        Player *player1;
        Player *player2;
        bool isPlayer1turn = true;
        Pawn selectedPawn;
        std::vector<Pawn> availablePawn;
        int form;

        // graphics
        sf::Texture background;              /** The background image sprite. */

    public:
        GameEngine();
        ~GameEngine();

        void start(std::string p1Name, std::string p2Name);
        bool isWon(int i, int j);
        void addPawn(int i, int j);
        void SelectPawn(int i, int j);
        bool isPlayable(int i, int j);

        // graphics
        /**
        * This function render the game engine in a render window.
        * @param window: the window
        */
        void render(sf::RenderWindow &window);


    private:
        /**
        * This function loads the available pawns.
        */
        void loadAvailablePawns();

        // graphics
        /**
        * This function load the useful images.
        */
        void loadImages();

};

#endif // GAMEENGINE_H
