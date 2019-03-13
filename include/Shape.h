#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Config.h"

/**
* This class represents a shape in a grid.
*/
class Shape
{

private:
    bool** grid;  /** The grid containing the shape. */


public:

    /**
    * Constructor.
    * @param name: the name of the shape
    */
    Shape(ShapeName const& name);

    /**
    * Copy constructor.
    * @param shape: shape to copy
    */
    Shape(Shape const& shape);

    /**
    * Destructor.
    */
    ~Shape();

    /**
    * Gets the rectangle englobing the shape (x, y, width, height).
    * @return the rectangle
    */
    std::vector<int> getRectangle() const;

    /**
    * This function returns every coordinates GameEngine has to check for victory,
    * for every way the last played pawn can integrate itself in the selected Shape.
    * @param i : the y coordinate of the pawn
    * @param j : the x coordinate of the pawn
    * @return Returns the list of coordinates.
    */
    std::vector<std::vector<std::vector<int>>> getPossibleCoordinatesToCheck(int const& i, int const& j) const;

    /**
    * This function returns every coordinates possible for the shape.
    * @return The list of list of coordinates (representing the shape) that are possible in the grid
    */
    std::vector<std::vector<std::vector<int>>> getPossibleCoordinates() const;

    /**
     * This function rotates a shape of 90 degrees (clock wise).
     */
     void rotate();

};

#endif // SHAPE_H
