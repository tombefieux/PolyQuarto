#ifndef POLYQUARTO_MENU_H
#define POLYQUARTO_MENU_H

#include "GameEngine.h"

/**
 * This class represents the menu of the game.
 */
class Menu {

private:
    GameEngine* engine;                 /** The engine of the game. */
    Player* player1;                    /** The first player. */
    Player* player2;                    /** The second player. */
    ShapeName selectedShape;            /** The selected shape. */

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

};


#endif //POLYQUARTO_MENU_H
