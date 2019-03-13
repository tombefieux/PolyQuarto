#include "Shape.h"

using namespace std;

Shape::Shape(ShapeName const& name)
{
    this->grid = new bool[4];
    for (int i = 0; i < 4; i++)
        this->grid[i] = new bool[4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->grid[i][j] = SHAPES[name][i][j];
}

Shape::~Shape()
{
    for (int i = 0; i < 4; i++)
        delete[] this->grid[i];
    delete[] this->grid;
}

vector<int> Shape::getRectangle() const
{
    int x = 5, y = 5, maxX = -1, maxY = -1;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if(this->grid[i][j] && i < x) x = i;
            if(this->grid[j][i] && j < y) y = j;
            if(this->grid[i][j] && i > maxX) maxX = i;
            if(this->grid[j][i] && j > maxY) maxY = j;
        }

    vector<int> result;
    result.push_back(x);
    result.push_back(y);
    result.push_back(maxX - x);
    result.push_back(maxY - y);

    return result;
}

vector<vector<vector<int>>> Shape::getPossibleCoordinatesToCheck(int const& i, int const& j) const
{

}

static vector<vector<vector<int>>> Shape::getPossibleCoordinates(Shape const& shape)
{
    // if doesn't work -> try with vector named trueCoordinatesOfShape
    vector<vector<vector<int>>> result;
    vector<int> englobingRectangle = shape.getRectangle();
    for (int i = 0; i < 4 && i + englobingRectangle[2] < 4; i++)
        for (int j = 0; j < 4 && j + englobingRectangle[3] < 4; j++)
        {
            vector<vector<int>> temp;
            for (int a = 0; a < 4; a++)
                for (int b = 0; b < 4; b++)
                    if(shape.grid[a][b])
                    {
                        vector<int> coordinate;
                        coordinate.push_back(a+i);
                        coordinate.push_back(b+j);
                        temp.push_back(coordinate);
                    }

            result.push_back(temp);
        }

    return result;
}
