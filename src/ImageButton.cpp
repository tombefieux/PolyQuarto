#include "../include/ImageButton.h"

ImageButton::ImageButton(int const& x, int const& y, sf::Texture* background): Clickable(x, y, IMAGE_BUTTON_WIDTH, IMAGE_BUTTON_HEIGHT)
{
    this->background = background;
}

ImageButton::~ImageButton()
{
    delete this->background;
}

void ImageButton::render(sf::RenderWindow &window) const
{
    sf::Sprite sprite;
    sprite.setTexture(*this->background);
    sprite.setPosition(this->x, this->y);
    window.draw(sprite);
}