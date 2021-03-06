#ifndef POLYQUARTO_MENU_H
#define POLYQUARTO_MENU_H

#include "GameEngine.h"
#include "Button.h"
#include "ImageButton.h"

/**
 * Enum for the menu
 */
enum MenuType {PlayerNumber, Difficulty, Shape};

/**
 * This class represents the menu of the game.
 */
class Menu {

private:
    GameEngine* engine;                 /** The engine of the game. */
    Player* player1;                    /** The first player. */
    Player* player2;                    /** The second player. */
    ShapeName selectedShape;            /** The selected shape. */
    MenuType currentMenuType;           /** Te current type of menu. */
    bool onePlayer;                     /** If the player want to play alone. */
    int difficulty;                     /** Te difficulty of the AI. */

    Button* returnToNumber;              /** Button to return to the main menu. */

    // for player menu
    Button* onePlayerButton;             /** Button to select one player. */
    Button* twoPlayersButton;            /** Button to select two players. */

    // for difficulty menu
    Button* easyButton;                  /** Button to select easy difficulty. */
    Button* hardButton;                  /** Button to select hard difficulty. */

    // for shape menu
    ImageButton** shapeButtons;       /** The shape buttons. */


    // graphics
    sf::Texture background;              /** The background image sprite. */

public:

    Menu(GameEngine* engine);
    ~Menu();

    /**
     * This function handles the click in the menu.
     * @param x: x coordinate of the click
     * @param y: y coordinate of the click
     */
    void handleLeftClick(int const& x, int const& y);

    /**
    * This function render the menu in a render window.
    * @param window: the window
    */
    void render(sf::RenderWindow &window) const;

private:

    /**
     * This function draws the player number menu.
     * @param window: the window
     */
     void drawPLayerNumber(sf::RenderWindow &window) const;

    /**
    * This function draws the difficulty menu.
    * @param window: the window
    */
     void drawDifficulty(sf::RenderWindow &window) const;

    /**
    * This function draws the shape menu.
    * @param window: the window
    */
     void drawShape(sf::RenderWindow &window) const;

     /**
      * This function launch the engine for a game.
      */
     void launchEngine();
};


#endif //POLYQUARTO_MENU_H
