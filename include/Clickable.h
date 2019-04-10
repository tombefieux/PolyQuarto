#ifndef POLYQUARTO_CLICKABLE_H
#define POLYQUARTO_CLICKABLE_H

/**
 * This class represents a clickable rectangle.
 */
class Clickable {

protected:
    int x;                               /** The x position. */
    int y;                               /** The y position. */
    int width;                           /** The width. */
    int height;                          /** The height. */

public:

    Clickable(int const& x, int const& y, int const& width, int const& height);

    /**
     * This fucntion returns if the coordinate of the mouse's click is on the button.
     * @param x: x coordinate of the click
     * @param y: y coordinate of the click
     * @return if the coordinate of the mouse's click is on the button.
     */
    bool isClickedOnIt(int const& x, int const& y) const;
};


#endif //POLYQUARTO_CLICKABLE_H
