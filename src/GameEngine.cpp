#include "GameEngine.h"
#include <iostream>
#include <string>

using namespace std;

GameEngine::GameEngine()
{
    this->grid.resize(4);
    this->selectedPawn = nullptr;
    for(int i = 0; i<4; i++) this->grid[i].resize(4);

    loadImages();
}

GameEngine::~GameEngine()
{
    delete this->player1;
    delete this->player2;

    clearGrid();
}

void GameEngine::start(string p1Name, string p2Name)
{
    this->player1 = new Player(p1Name);
    this->player2 = new Player(p2Name);

    loadAvailablePawns();

    cout << "Sélectionnez une pièce pour votre adversaire";
}

bool GameEngine::isPlayable(int const& i, int const& j) const
{
    if(grid[i][j] == nullptr) return true;
    else return false;
}

void GameEngine::clearGrid()
{
    for (int i = 0; i < (int) this->grid.size(); i++)
        for (int j = 0; j < (int) this->grid[i].size(); j++)
            delete grid[i][j];

    this->grid.clear();
}

void GameEngine::addPawn(int const& i, int const& j)
{
    if(!pawnPlayed)
    {
        if(this->isPlayable(i, j))
        {
            grid[i][j] = selectedPawn;
            selectedPawn = nullptr;
            cout << "Sélectionnez une pièce pour votre adversaire";
            pawnPlayed = true;

        }
        else cout<<"MDR t'es con !";
    }
    else cout<<"MDR t'es con !";

}

void GameEngine::selectPawn(int const& i)
{
    if(selectedPawn ==  nullptr)
    {
        selectedPawn = availablePawn[i];
        availablePawn[i] = nullptr;
        isPlayer1Turn = !isPlayer1Turn;
        pawnPlayed = false;
    }
}

void GameEngine::loadImages()
{
    this->background.loadFromFile(IMAGES_PATH + "background.png");
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

int GameEngine::getPawnIndexWithCoordiante(int const& x, int const& y) const
{
    int result = -1;

    for (int i = 0; i < (int) this->availablePawn.size(); i++)
    {
        int currentX, currentY;
        if(i < 8)
        {
            currentX = START_AVAILABLE_PAWN_LIST_X;
            currentY = START_AVAILABLE_PAWN_LIST_Y + (PAWN_SIZE + SPACE_BETWEEN_AVAILABLE_PAWN) * i;
        }
        else
        {
            currentX = START_AVAILABLE_PAWN_LIST_X + PAWN_SIZE + START_AVAILABLE_PAWN_LIST_X;
            currentY = START_AVAILABLE_PAWN_LIST_Y + (PAWN_SIZE + SPACE_BETWEEN_AVAILABLE_PAWN) * (i - 8);
        }

        // if the click is in the current
        if(
               currentX <= x && currentX + PAWN_SIZE >= x &&
               currentY <= y && currentY + PAWN_SIZE >= y
               )
                result = i;
    }

    return result;
}

void GameEngine::getGridIndexWithCoordiante(int const& x, int const& y, int& iIndex, int& jIndex) const
{
    iIndex = -1;
    jIndex = -1;

    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if(
               START_GRID_PAWN_X + (i*SPACE_BETWEEN_PAWN) + (i*PAWN_SIZE) <= x && START_GRID_PAWN_X + (i*SPACE_BETWEEN_PAWN) + ((i+1)*PAWN_SIZE) >= x &&
               START_GRID_PAWN_Y + (j*SPACE_BETWEEN_PAWN) + (j*PAWN_SIZE) <= y && START_GRID_PAWN_Y + (j*SPACE_BETWEEN_PAWN) + ((j+1)*PAWN_SIZE) >= y
               )
            {
                // because we are in line, column
                iIndex = j;
                jIndex = i;
            }
        }
}

void GameEngine::render(sf::RenderWindow &window) const
{
    // background
    sf::Sprite sprite;
    sprite.setTexture(this->background);
    window.draw(sprite);

    // display the available pawns
    for (int i = 0; i < (int) this->availablePawn.size(); i++)
    {
        if(this->availablePawn[i] != nullptr)
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

    // display the selected pawn if there's one
    if(this->selectedPawn != nullptr)
    {
        sf::Sprite temp;
        temp.setTexture(*this->selectedPawn->getTexture());
        temp.setPosition(sf::Mouse::getPosition(window).x - PAWN_SIZE / 2, sf::Mouse::getPosition(window).y - PAWN_SIZE / 2);

        window.draw(temp);
    }

    // display pawn on the grid
    for (int i = 0; i < (int) this->grid.size(); i++)
        for (int j = 0; j < (int) this->grid.at(i).size(); j++)
            if(this->grid[i][j])
            {
                sf::Sprite temp;
                temp.setTexture(*this->grid[i][j]->getTexture());
                temp.setPosition
                (
                    START_GRID_PAWN_X + (j*SPACE_BETWEEN_PAWN) + (j*PAWN_SIZE),
                    START_GRID_PAWN_Y + (i*SPACE_BETWEEN_PAWN) + (i*PAWN_SIZE)
                 );

                window.draw(temp);
            }
}

void GameEngine::handleLeftClick(int const& x, int const& y)
{
    // if we have a selected pawn -> we want to play
    if(this->selectedPawn != nullptr)
    {
        int iGridIndex, jGridIndex;
        getGridIndexWithCoordiante(x, y, iGridIndex, jGridIndex);
        if(iGridIndex != -1)
            addPawn(iGridIndex, jGridIndex);
    }

    // else
    else
    {
        // if it's on a pawn we select it
        int pawnIndexWithClick = getPawnIndexWithCoordiante(x, y);
        if(pawnIndexWithClick != -1)
            selectPawn(pawnIndexWithClick);
    }

}
