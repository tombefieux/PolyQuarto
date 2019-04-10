#ifndef POLYQUARTO_IMAGEBUTTON_H
#define POLYQUARTO_IMAGEBUTTON_H


#include <SFML/Graphics.hpp>

#include "Config.h"
#include "Clickable.h"

/**
 * This class represents a button with an image.
 */
class ImageButton: public Clickable {

private:
    sf::Texture* background;              /** The background image sprite. */

public:
    ImageButton(int const& x, int const& y, sf::Texture* background);
    ~ImageButton();

    /**
    * This function render the button in a render window.
    * @param window: the window
    */
    void render(sf::RenderWindow &window) const;
};


#endif //POLYQUARTO_IMAGEBUTTON_H
