#include "../include/Button.h"

Button::Button(int const& x, int const& y, string const& label): Clickable(x, y, BUTTON_WIDTH, BUTTON_HEIGHT)
{
    this->background.loadFromFile(IMAGES_PATH + "button.png");

    // build the text
    font.loadFromFile(FONT_PATH + "SF_Atarian_System.ttf");
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);

    float width = text.getGlobalBounds().width;
    float height = text.getGlobalBounds().height;
    text.setPosition(this->x + (BUTTON_WIDTH - width)/2, this->y + 4);
}

void Button::render(sf::RenderWindow &window) const
{
    sf::Sprite sprite;
    sprite.setTexture(this->background);
    sprite.setPosition(this->x, this->y);
    window.draw(sprite);

    window.draw(text);
}