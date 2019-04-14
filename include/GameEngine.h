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
    bool gameIsRunning = false;         /** If the game is running or not. */
    bool onePlayer;

    // graphics
    sf::Texture background;              /** The background image sprite. */

public:
    /**
     * The constructor.
     */
    GameEngine();

    /**
     * The destructor.
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
     * This function decides where to play for the AI to win.
     * Part of the MinMax algorithm.
     * @param depth: the higher it is, the better the AI will be. Number of consecutive plays the program tests.
     */
    void playAI(int const& depth);

    /**
     * This function tests every playable Pawns contained in the given vector at every possible location in the grid.
     * It returns the "value" of a play by examining and comparing each following play by calling the method max(...).
     * If the depth is 0, it evaluates the grid and returns the value
     * Part of the MinMax algorithm.
     * @param copyAvailablePawns: the list of playable Pawns
     * @param depth: enables the program to know if it has to evaluate the grid or call min(...)
     * @param line: the line of the last played pawn
     * @param col: the column of the last played pawn
     */
    int min(int depth, int const& line, int const& col);

    /**
     * This function tests every playable Pawns contained in the given vector at every possible location in the grid.
     * It returns the "value" of a play by examining and comparing each following play by calling the method min(...).
     * If the depth is 0, it evaluates the grid and returns the value
     * Part of the MinMax algorithm.
     * @param copyAvailablePawns: the list of playable Pawns
     * @param depth: enables the program to know if it has to evaluate the grid or call min(...)
     * @param line: the line of the last played pawn
     * @param col: the column of the last played pawn
     */
    int max(int depth, int const& line, int const& col);

    /**
     * This function evaluates the grid depending of a pawn at (line, col) coordinates.
     * It evaluates the grid with the sum of common characteristics between all the pawns in a shape possibility * the number of pawns fitting with the shape.
     * The result is the sum of this value for each shape possibility at this point.
     * We assume that the pawn is already put in the grid at (line, col) coordinates.
     * @param grid: the grid to evaluate
     * @param line: the line of the played pawn
     * @param col: the column of the player pawn
     * @return the evaluation number
     */
    int evaluateGrid(vector<vector<Pawn*>> const& grid, int const& line, int const& col) const;

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

    bool getOnePlayer() const;

    void setOnePlayer(bool);

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
