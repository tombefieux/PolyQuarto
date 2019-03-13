#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>

using namespace std;

/**
* A configuration file with useful constants in it.
*/

const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 480;

const int FPS = 30;

const string IMAGES_PATH = "assets/images/";

const int GRID_SIZE = 4;

const int START_AVAILABLE_PAWN_LIST_X = 40;
const int START_AVAILABLE_PAWN_LIST_Y = 15;
const int SPACE_BETWEEN_AVAILABLE_PAWN = 20;
const int PAWN_SIZE = 40;

const int START_GRID_PAWN_X = 342;
const int START_GRID_PAWN_Y = 113;
const int SPACE_BETWEEN_PAWN = 32;

enum ShapeName {Line = 0, Columm = 1};

const bool SHAPES[][][] = {

    // Line
    {
        {true, true, true, true},
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // Column
    {
        {true, false, false, false},
        {true, false, false, false},
        {true, false, false, false},
        {true, false, false, false}
    }
};

#endif // CONFIG_H_INCLUDED
