#ifndef POLYQUARTO_BUTTON_H
#define POLYQUARTO_BUTTON_H

#include <SFML/Graphics.hpp>

#include <string>

#include "Config.h"

/**
 * This class represents a button.
 */
class Button {

private:
    int x;                               /** The x position of the button. */
    int y;                               /** The y position of the button. */

    // graphics
    sf::Texture background;              /** The background image sprite. */
    sf::Text text;                       /** The text of the button. */
    sf::Font font;                       /** The font of the text. */

public:
    Button(int const& x, int const& y, string const& label);

    /**
    * This function render the button in a render window.
    * @param window: the window
    */
    void render(sf::RenderWindow &window) const;

    /**
     * This fucntion returns if the coordinate of the mouse's click is on the button.
     * @param x: x coordinate of the click
     * @param y: y coordinate of the click
     * @return if the coordinate of the mouse's click is on the button.
     */
    bool isClickedOnIt(int const& x, int const& y) const;

};


#endif //POLYQUARTO_BUTTON_H
