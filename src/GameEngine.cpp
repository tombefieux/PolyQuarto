#include "GameEngine.h"
#include <iostream>
#include <string>

using namespace std;

GameEngine::GameEngine()
{
    this->grid.resize(4);
    for(int i = 0; i<4; i++) this->grid[i].resize(4);

    loadImages();
}

GameEngine::~GameEngine()
{
    delete this->player1;
    delete this->player2;

    clearGrid();
}

bool GameEngine::isPlayable(int i, int j)
{
    if(grid[i][j] == nullptr) return true;
    else return false;
}

void GameEngine::clearGrid()
{
    for (int i = 0; i < this->grid.size(); i++)
        for (int j = 0; j < this->grid[i].size(); j++)
            delete grid[i][j];

    this->grid.clear();
}

void GameEngine::addPawn(int i, int j)
{
    if(!pawnPlayed)
    {
        if(this->isPlayable(i, j))
        {
            grid[i][j] = selectedPawn;
            selectedPawn = nullptr;
            cout<<"Sélectionnez une pièce pour votre adversaire";
            pawnPlayed = true;

        }
        else cout<<"MDR t'es con !";
    }
    else cout<<"MDR t'es con !";

}

void GameEngine::selectPawn(int i)
{
    if(selectedPawn ==  nullptr)
    {
        selectedPawn = availablePawn[i];
        availablePawn[i] = nullptr;
        isPlayer1Turn = !isPlayer1Turn;
        pawnPlayed = false;
    }

}


bool GameEngine::isWonLine4(int i, int j)
{
    int x, y,incr, cpt = 0;
    x = i;
    y = j;
    incr = 3-j;
    for (y; y<=incr; y++)
    {
        if (inCommon(grid[x][y],grid[i][j]))
        {
            cpt++;
        }
        else break;
    };
    y = j;
    for (y; y=>0; y--)
    {
        if (inCommon(grid[x][y],grid[i][j]))
        {
            cpt++;
        }
        else break;
    }
    if(cpt>=4) return true;
    commonPoints.clear();
    return false;
}

bool GameEngine::isWonColumn4(int i, int j)
{
    int x, y,incr, cpt = 0;
    x = i;
    y = j;
    incr = 3-i;
    for (x; x<=incr; x++)
    {
        if (inCommon(grid[x][y],grid[i][j]))
        {
            cpt++;
        }
        else break;
    };
    x=i;
    for (x; x=>0; x--)
    {
        if (inCommon(grid[x][y],grid[i][j]))
        {
            cpt++;
        }
        else break;
    }
    if(cpt>=4) return true;
    commonPoints.clear();
    return false;
}

bool GameEngine::isWon4(int i; int j;)
{
    if(isWonLine4(i, j)) return true;
    if(isWonColumn4(i, j)) return true;
    return false;
}


bool GameEngine::inCommon(Pawn* uno,Pawn* dos)
{
    if(commonpoints.empty())
    {
        commonPoints=uno.inCommon(dos);
        bool temp=false;
        for(int i =0; i<4; i++)
        {
            if(commonPoints[i]==true) temp=commonPoints[i];
        }
        return temp;
    }
    else {
        dos.inCommon(commonPoints);
        bool temp=false;
        for(int i =0; i<4; i++)
        {
            if(commonPoints[i]==true) temp=commonPoints[i];
        }
        return temp;
    }
}

void GameEngine::loadImages()
{
    this->background.loadFromFile(IMAGES_PATH + "background.png");
}

void GameEngine::start(string p1Name, string p2Name)
{
    this->player1 = new Player(p1Name);
    this->player2 = new Player(p2Name);

    loadAvailablePawns();
}

void GameEngine::loadAvailablePawns()
{
    this->availablePawn.clear();

    for (int a = 0; a < 2; a++)
        for (int b = 0; b < 2; b++)
            for (int c = 0; c < 2; c++)
                for (int d = 0; d < 2; d++)
                    this->availablePawn.push_back(new Pawn((bool) a, (bool) b, (bool) c, (bool) d));
}

void GameEngine::render(sf::RenderWindow &window)
{
    // background
    sf::Sprite sprite;
    sprite.setTexture(this->background);
    window.draw(sprite);

    // display the available pawns
    for (int i = 0; i < (int) this->availablePawn.size(); i++)
    {
        sf::Sprite temp;
        temp.setTexture(*this->availablePawn.at(i)->getTexture());

        if(i < 8)
            temp.setPosition(START_AVAILABLE_PAWN_LIST_X, START_AVAILABLE_PAWN_LIST_Y + (PAWN_SIZE + SPACE_BETWEEN_AVAILABLE_PAWN) * i);
        else
            temp.setPosition(START_AVAILABLE_PAWN_LIST_X + PAWN_SIZE + START_AVAILABLE_PAWN_LIST_X, START_AVAILABLE_PAWN_LIST_Y + (PAWN_SIZE + SPACE_BETWEEN_AVAILABLE_PAWN) * (i - 8));

        window.draw(temp);
    }
}
