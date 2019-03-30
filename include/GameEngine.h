#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Pawn.h"
#include "Player.h"
#include "Shape.h"
#include "Config.h"

class GameEngine
{
private:
    std::vector<vector<Pawn*>> grid;    /** The grid of the game. */
    Player *player1;                    /** The player one. */
    Player *player2;                    /** The player one. */
    bool isPlayer1Turn = true;          /** If it's to the first player to play. */
    Pawn* selectedPawn;                 /** The current selected pawn. */
    std::vector<Pawn*> availablePawn;   /** The pawns that are available. */
    Shape* shape;                       /** The shape to play with. */
    bool engineIsRunning = false;       /** If the engine is running or not. */
    bool gameIsRunning = false;       /** If the game is running or not. */

    // graphics
    sf::Texture background;              /** The background image sprite. */

public:
    /**
     * THe constructor.
     */
    GameEngine();

    /**
     * Te destructor.
     */
    ~GameEngine();

    /**
     * This function start a game with two player and a shape.
     * @param player1: the first player
     * @param player2: the second player
     * @param shapeName: the name of the shape to play with
     */
    void start(Player* player2, Player* player1, ShapeName const& shapeName);

    /**
     * This function checks if the game is won with a pawn at one position.
     * @param i: line of the pawn
     * @param j: column of the pawn
     * @return if the game is won with this pawn
     */
    bool isWon(int const& i, int const& j) const;

    /**
     * This function adds a pawn in the grid (the selected one).
     * @param i: the line
     * @param j: the column
     */
    void addPawn(int const& i, int const& j);

    /**
     * This function returns if we can play at a position.
     * @param i: the line
     * @param j: the column
     * @return if we can play
     */
    bool isPlayable(int const& i, int const& j) const;

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

    /**
     * Getter to know if the engine is running or not.
     * @return if the engine is running or not.
     */
    bool getEngineIsRunning() const;

    /**
    * Getter to know if the game is running or not.
    * @return if the game is running or not.
    */
    bool getGameIsRunning() const;


private:

    /**
     * This function returns the current player.
     * @return the current player
     */
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
    int getPawnIndexWithCoordinate(int const& x, int const& y) const;

    /**
    * This function returns the indexes in the grid for a coordinate in the window.
    * @param x: the x coordinate in the window
    * @param y: the y coordinate int he window
    * @param iIndex: the i index in the grid (-1 if not found)
    * @param jIndex: the j index in the grid (-1 if not found)
    */
    void getGridIndexWithCoordinate(int const& x, int const& y, int& iIndex, int& jIndex) const;

    /**
    * This function ends the engine.
    */
    void endEngine();

};

#endif // GAMEENGINE_H
