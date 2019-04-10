#ifndef POLYQUARTO_BUTTON_H
#define POLYQUARTO_BUTTON_H

#include <SFML/Graphics.hpp>

#include <string>

#include "Config.h"
#include "Clickable.h"

/**
 * This class represents a button.
 */
class Button: public Clickable {

private:
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

};


#endif //POLYQUARTO_BUTTON_H