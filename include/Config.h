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
const string FONT_PATH = "assets/font/";

const int GRID_SIZE = 4;

const int START_AVAILABLE_PAWN_LIST_X = 40;
const int START_AVAILABLE_PAWN_LIST_Y = 15;
const int SPACE_BETWEEN_AVAILABLE_PAWN = 20;
const int PAWN_SIZE = 40;

const int START_GRID_PAWN_X = 342;
const int START_GRID_PAWN_Y = 113;
const int SPACE_BETWEEN_PAWN = 32;

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 40;

const int BUTTON_X = 260;

enum ShapeName {Line = 0, LeftL = 1, RightL = 2, Square = 3, LeftZ = 4, RightZ = 5, Invaders = 6};

const bool SHAPES[7][4][4] = {

    // Line
    {
        {true, true, true, true},
        {false, false, false, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // LeftL
    {
        {true, false, false, false},
        {true, true, true, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // RightL
    {
        {false, false, true, false},
        {true, true, true, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // Square
    {
        {true, true, false, false},
        {true, true, false, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // LeftZ
    {
        {false, true, true, false},
        {true, true, false, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // RightZ
    {
        {true, true, false, false},
        {false, true, true, false},
        {false, false, false, false},
        {false, false, false, false}
    },

    // Invaders
    {
        {false, true, false, false},
        {true, true, true, false},
        {false, false, false, false},
        {false, false, false, false}
    }
};

#endif // CONFIG_H_INCLUDED
