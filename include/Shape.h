#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

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
        * Destructor.
        */
        ~Shape();

        /**
        * Gets the rectangle englobing the shape.
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
        * This function returns every every coordinates possible for the shape.
        * @param shape : the chosen shape on which the coordinates depend
        * @return The list of coordinates, that are possible in the grid, representing the shape
        */
        static std::vector<std::vector<std::vector<int>>> getPossibleCoordinates(Shape const& shape);
};

#endif // SHAPE_H
