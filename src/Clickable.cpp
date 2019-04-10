#include "../include/Clickable.h"

Clickable::Clickable(int const& x, int const& y, int const& width, int const& height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool Clickable::isClickedOnIt(int const& x, int const& y) const
{
    return (
            x >= this->x && x <= this->x + width &&
            y >= this->y && y <= this->y + height
    );
}