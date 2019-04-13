#include "../include/Shape.h"

using namespace std;

Shape::Shape(ShapeName const& name)
{
    this->grid = new bool* [4];
    for (int i = 0; i < 4; i++)
        this->grid[i] = new bool[4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->grid[i][j] = SHAPES[name][i][j];
}

Shape::Shape(Shape const& shape)
{
    this->grid = new bool* [4];
    for (int i = 0; i < 4; i++)
        this->grid[i] = new bool[4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->grid[i][j] = shape.grid[i][j];
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
            if(this->grid[j][i] && i < x) x = i;
            if(this->grid[j][i] && j < y) y = j;
            if(this->grid[j][i] && i > maxX) maxX = i;
            if(this->grid[j][i] && j > maxY) maxY = j;
        }

    vector<int> result;
    result.push_back(x);
    result.push_back(y);
    result.push_back(maxX - x + 1);
    result.push_back(maxY - y + 1);

    return result;
}

vector<vector<vector<int>>> Shape::getPossibleCoordinatesToCheck(int const& i, int const& j) const
{
    vector<vector<vector<int>>> allPossibilities = getAllPossibleCoordinatesInGrid();
    vector<vector<vector<int>>> result;

    // for each shape
    for (unsigned int a = 0; a < allPossibilities.size(); a++)
    {
        // see if the i j coordinates are in the shape
        bool contained = false;
        // for each coordinate of the shape
        for (unsigned int b = 0; b < allPossibilities[a].size() && !contained; b++)
            if(allPossibilities[a][b][0] == i && allPossibilities[a][b][1] == j)
                contained = true;

        // if contained add it
        if(contained)
            result.push_back(allPossibilities[a]);
    }

    return result;
}

vector<vector<vector<int>>> Shape::getAllPossibleCoordinatesInGrid() const
{
    vector<vector<vector<int>>> result;
    Shape currentShape(*this);

    // for every possible rotations (4)
    for (int i = 0; i < 4; i++)
    {
        // get possibles coordinates
        vector<vector<vector<int>>> possibleCoordinates = currentShape.getPossibleCoordinates();

        // add to the result
        // for each possible coordinates
        for (unsigned int j = 0; j < possibleCoordinates.size(); j++)
        {
            // if already doesn't exist
            bool exist = false;

            // for each coordinates already in result
            for (unsigned int a = 0; a < result.size() && !exist; a++)
            {
                bool same = true;

                // for each coordinates
                for (unsigned int b = 0; b < result[a].size() && same; b++)
                    if(result[a][b][0] != possibleCoordinates[j][b][0] || result[a][b][1] != possibleCoordinates[j][b][1])
                        same = false;

                exist = same;
            }

            // if not in add it
            if(!exist)
                result.push_back(possibleCoordinates[j]);
        }

        // rotate
        if(i != 3)
            currentShape.rotate();
    }

    return result;
}

vector<vector<vector<int>>> Shape::getPossibleCoordinates() const
{
    // if doesn't work -> try with vector named trueCoordinatesOfShape
    vector<vector<vector<int>>> result;
    vector<int> englobingRectangle = this->getRectangle();

    for (int i = 0; i < 4 && i + englobingRectangle[2] - 1 < 4; i++)
    {
        for (int j = 0; j < 4 && j + englobingRectangle[3] - 1 < 4; j++)
        {
            vector<vector<int>> temp;
            for (int a = 0; a < 4; a++)
                for (int b = 0; b < 4; b++)
                    if(this->grid[a][b])
                    {
                        vector<int> coordinate;
                        coordinate.push_back(a + j - englobingRectangle[1]);    // to be honest I just know that it works :)
                        coordinate.push_back(b + i - englobingRectangle[0]);    // the same :)
                        temp.push_back(coordinate);
                    }

            result.push_back(temp);
        }
    }

    return result;
}

void Shape::rotate() {

    /**
     * Code from:
     * https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
     */
    int N = 4;

    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group of 4 in
        // current square
        for (int y = x; y < N - x - 1; y++) {
            // store current cell in temp variable
            bool temp = this->grid[x][y];

            // move values from right to top
            this->grid[x][y] = this->grid[y][N - 1 - x];

            // move values from bottom to right
            this->grid[y][N - 1 - x] = this->grid[N - 1 - x][N - 1 - y];

            // move values from left to bottom
            this->grid[N - 1 - x][N - 1 - y] = this->grid[N - 1 - y][x];

            // assign temp to left
            this->grid[N - 1 - y][x] = temp;
        }
    }
}
