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
        std::vector<vector<Pawn*>> grid;
        Player *player1;
        Player *player2;
        bool isPlayer1Turn = true;
        Pawn* selectedPawn;
        std::vector<Pawn*> availablePawn;
        bool pawnPlayed;

        // graphics
        sf::Texture background;              /** The background image sprite. */

    public:
        GameEngine();
        ~GameEngine();

        void start(std::string p1Name, std::string p2Name);
        bool isWon(int const& i, int const& j) const;
        void addPawn(int const& i, int const& j);
        void selectPawn(int const& i, int const& j);
        bool isPlayable(int const& i, int const& j) const;

        vector<Pawn>* getAvailablePawn() const;
        Pawn* getSelectedPawn() const;

        // graphics
        /**
        * This function render the game engine in a render window.
        * @param window: the window
        */
        void render(sf::RenderWindow &window) const;

        /**
        * This function handles the left click event of the window.
        * @param x: the x coordinate of the click
        * @param y: the y coordinate of the click
        */
        void handleLeftClick(int const& x, int const& y);


    private:

        Player* getCurrentPlayer();

        /**
        * This function selects a pawn in the available pawns list at its index.
        * @param i: the index of the pawn in the available pawns list
        */
        void selectPawn(int const& i);

        /**
        * This function clears the grid vector.
        */
        void clearGrid();

        /**
        * This function loads the available pawns.
        */
        void loadAvailablePawns();

        // graphics
        /**
        * This function load the useful images.
        */
        void loadImages();

        /**
        * This function returns the index of the pawn in the available pawns list at the x and y coordinates of the window.
        * @param x: the x coordinate in the window
        * @param y: the y coordinate int he window
        * @return the index of the pawn at (x, y) or -1 if there's no pawn at this place
        */
        int getPawnIndexWithCoordiante(int const& x, int const& y) const;

        /**
        * This function returns the indexes in the grid for a coordinate in the window.
        * @param x: the x coordinate in the window
        * @param y: the y coordinate int he window
        * @param iIndex: the i index in the grid (-1 if not found)
        * @param jIndex: the j index in the grid (-1 if not found)
        */
        void getGridIndexWithCoordiante(int const& x, int const& y, int& iIndex, int& jIndex) const;

};

#endif // GAMEENGINE_H
