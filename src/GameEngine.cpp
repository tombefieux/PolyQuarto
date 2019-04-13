#include "../include/GameEngine.h"
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
    delete this->shape;
    delete this->selectedPawn;

    clearGrid();
}

void GameEngine::start(Player* player2, Player* player1, ShapeName const& shapeName)
{
    this->player1 = player1;
    this->player2 = player2;
    this->shape = new Shape(shapeName);
    this->engineIsRunning = true;
    this->gameIsRunning = true;

    loadAvailablePawns();

    cout << "Sélectionnez une pièce pour votre adversaire" << endl;
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

bool GameEngine::isWon(int const& i, int const& j) const
{
    // get ALL the possibilities of shapes at this point for the shape of the game
    vector<vector<vector<int>>> possibilitiesForLine = this->shape->getPossibleCoordinatesToCheck(i, j);

    // for each shape possibility
    for (unsigned int a = 0; a < possibilitiesForLine.size(); a++)
    {
        bool stillOkForBright = true, stillOkForSmall = true, stillOkForSquare = true, stillOkForHollow = true;
        Pawn* firstPawn = this->grid[possibilitiesForLine[a][0][0]][possibilitiesForLine[a][0][1]];

        if(firstPawn != nullptr)
        {
            // for each coordinate
            bool stop = false;
            for (unsigned int b = 1; b < possibilitiesForLine[a].size() && !stop; b++)
            {
                Pawn* currentPawn = this->grid[possibilitiesForLine[a][b][0]][possibilitiesForLine[a][b][1]];

                if(currentPawn != nullptr) {
                    stillOkForBright = (stillOkForBright && firstPawn->getPoints()[0] == currentPawn->getPoints()[0]);
                    stillOkForSmall = (stillOkForSmall && firstPawn->getPoints()[1] == currentPawn->getPoints()[1]);
                    stillOkForSquare = (stillOkForSquare && firstPawn->getPoints()[2] == currentPawn->getPoints()[2]);
                    stillOkForHollow = (stillOkForHollow && firstPawn->getPoints()[3] == currentPawn->getPoints()[3]);
                }
                else
                    stop = true;
            }

            if(!stop && (stillOkForBright || stillOkForHollow || stillOkForSmall || stillOkForSquare))
                return true;
        }
    }

    return false;
}

void GameEngine::AI(int depth)
{
    int maxVal = -999999;
    int value = 0;
    int xBestPlay =-1;
    int yBestPlay = -1;
    vector<Pawn*> copyAvailablePawn;


    for(unsigned int k = 0; k<this->grid.size(); k++)
    {
        for(unsigned int l = 0; l<this->grid.size(); l++)
        {
            copyAvailablePawn.clear();
            for(unsigned int t = 0; t<this->availablePawn.size(); t++)
            {
                copyAvailablePawn.push_back(this->availablePawn[t]);
            }
            if(isPlayable(k, l))
            {
                this->grid[k][l] = selectedPawn;

                if(isWon(k,l))
                    value = 999999;
                else
                {
                    value = Min(this->grid, copyAvailablePawn, depth);
                }
            }

            if(value>maxVal)
            {
                maxVal = value;
                xBestPlay = k;
                yBestPlay = l;
            }

            this->grid[k][l] = nullptr;
        }

    }
/*    for(int e=0;e<this->grid.size();e++)
    {
        for(int r=0;r<this->grid.size();r++)
        {
            if(this->grid[e][r] == nullptr)
               cout<<"VIDE ";
            else cout<<"PAWN ";
        }
        cout<<endl;
    }
*/
    //addPawn(xBestPlay, yBestPlay);
}

int GameEngine::Min(vector<vector<Pawn*>> grid, vector<Pawn*> &copyPawns, int &depth)
{
    int value = 0;
    int minVal = 9999999;

    //stores a copy of the list of playable Pawns that can be worked on and modified in called function Max
    vector<Pawn*> copyAvailablePawns;

    if(depth == 0 || copyPawns.size()==0)
    {
        cout<<"Evaluation de la grille dans Min() "<<endl;
        return evaluateGrid(grid);
    }

    //test every playable Pawn
    for(unsigned int i =0; i<copyPawns.size(); i++)
    {
        //at every playable position
        for(unsigned int k = 0; k<grid.size(); k++)
        {
            for(unsigned int l = 0; l<grid.size(); l++)
            {
                if(isPlayable(k, l))
                {
                    this->grid[k][l] = copyPawns[i];
                    copyAvailablePawns.clear();
                    for(unsigned int t = 0; t<copyPawns.size(); t++)
                    {
                        if(copyPawns[t] != copyPawns[i])
                            copyAvailablePawns.push_back(copyPawns[t]);
                    }

                    if(isWon(k,l))
                        value = 999999;
                    else
                    {
                        int d = depth-1;
                        value = Max(this->grid, copyAvailablePawns, d);
                    }
                }

                if(value<minVal)
                {
                    minVal = value;
                }

                this->grid[k][l] = nullptr;
            }

        }
    }
    return minVal;
}

int GameEngine::Max(vector<vector<Pawn*>> grid, vector<Pawn*> &copyPawns, int &depth)
{
    int value = 0;
    int maxVal = -9999999;

    //stores a copy of the list of playable Pawns that can be worked on and modified in called function Min
    vector<Pawn*> copyAvailablePawns;

    if(depth == 0 || copyPawns.size()==0)
    {
        cout<<"Evaluation de la grille dans Max() "<<endl;
        return evaluateGrid(grid);
    }

    //test every playable Pawn
    for(unsigned int i =0; i<copyPawns.size(); i++)
    {
        //at every playable position
        for(unsigned int k = 0; k<grid.size(); k++)
        {
            for(unsigned int l = 0; l<grid.size(); l++)
            {
                if(isPlayable(k, l))
                {
                    this->grid[k][l] = copyPawns[i];
                    copyAvailablePawns.clear();
                    for(unsigned int t = 0; t<copyPawns.size(); t++)
                    {
                        if(copyPawns[t] != copyPawns[i])
                            copyAvailablePawns.push_back(copyPawns[t]);
                    }

                    if(isWon(k,l))
                        value = -999999;
                    else
                    {
                        int d =depth-1;
                        value = Min(this->grid, copyAvailablePawns, d);
                    }
                }

                if(value>maxVal)
                {
                    maxVal = value;
                }

                this->grid[k][l] = nullptr;
            }

        }
    }
    return maxVal;
}

int GameEngine::evaluateGrid(vector<vector<Pawn*>> &grid) const
{
    int maxCount = 1;
    for(unsigned int z=0; z<grid.size(); z++)
    {
        for (unsigned int e = 0; e<grid.size(); e++)
        {
            if(grid[z][e] != nullptr)
            {
                // get ALL the possibilities of shapes at this point for the shape of the game
                vector<vector<vector<int>>> possibilitiesForLine = this->shape->getPossibleCoordinatesToCheck(z, e);

                // to store the number of Pawns fitting the Shape, in all rotations and positions
                int count = 1;

                // for each shape possibility
                for (unsigned int a = 0; a < possibilitiesForLine.size(); a++)
                {
                    bool stillOkForBright = true, stillOkForSmall = true, stillOkForSquare = true, stillOkForHollow = true;
                    Pawn* firstPawn = grid[possibilitiesForLine[a][0][0]][possibilitiesForLine[a][0][1]];

                    if(firstPawn != nullptr)
                    {
                        // for each coordinate
                        bool stop = false;
                        for (unsigned int b = 1; b < possibilitiesForLine[a].size() && !stop; b++)
                        {
                            Pawn* currentPawn = grid[possibilitiesForLine[a][b][0]][possibilitiesForLine[a][b][1]];

                            if(currentPawn != nullptr) {
                                stillOkForBright = (stillOkForBright && firstPawn->getPoints()[0] == currentPawn->getPoints()[0]);
                                stillOkForSmall = (stillOkForSmall && firstPawn->getPoints()[1] == currentPawn->getPoints()[1]);
                                stillOkForSquare = (stillOkForSquare && firstPawn->getPoints()[2] == currentPawn->getPoints()[2]);
                                stillOkForHollow = (stillOkForHollow && firstPawn->getPoints()[3] == currentPawn->getPoints()[3]);
                                if(stillOkForBright || stillOkForHollow || stillOkForSmall || stillOkForSquare)
                                    count++;
                            }
                            else
                                stop = true;
                        }
                        if(count>maxCount)
                            maxCount = count;
                    }
                }
            }
        }
    }
    cout<<endl<<maxCount<<endl;
    return maxCount;

}

void GameEngine::addPawn(int const& i, int const& j)
{
    if(selectedPawn != nullptr)
    {
        if(this->isPlayable(i, j))
        {
            grid[i][j] = selectedPawn;
            selectedPawn = nullptr;
            cout << "Sélectionnez une pièce pour votre adversaire" << endl;

            for(unsigned int a =0; a<grid.size(); a++)
            {
                for(unsigned int b=0;b<grid.size();b++)
                {
                    if(grid[a][b] != nullptr)
                        cout<<"Pawn";
                    else cout<<"Vide";
                }
                cout<<endl;
            }

            // if won
            if(isWon(i, j))
            {
                cout << "Nice you have won!" << endl;
                this->gameIsRunning = false;
            }
        }
        else cout<<"Impossible" << endl;
    }
    else cout<<"MDR t'es con !" << endl;

}

Player* GameEngine::getCurrentPlayer()
{
    if(this->isPlayer1Turn)
        return this->player1;
    else
        return this->player2;
}

void GameEngine::selectPawn(int const& i)
{
    if(selectedPawn ==  nullptr && this->gameIsRunning)
    {
        selectedPawn = availablePawn[i];
        availablePawn[i] = nullptr;
        isPlayer1Turn = !isPlayer1Turn;
        if(!isPlayer1Turn && this->onePlayer)
            AI(2);
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

int GameEngine::getPawnIndexWithCoordinate(int const& x, int const& y) const
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

void GameEngine::getGridIndexWithCoordinate(int const& x, int const& y, int& iIndex, int& jIndex) const
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

    // display the selected pawn if there's one
    if(this->selectedPawn != nullptr)
    {
        sf::Sprite temp;
        temp.setTexture(*this->selectedPawn->getTexture());
        temp.setPosition(sf::Mouse::getPosition(window).x - PAWN_SIZE / 2, sf::Mouse::getPosition(window).y - PAWN_SIZE / 2);

        window.draw(temp);
    }
}

void GameEngine::handleLeftClick(int const& x, int const& y)
{
    // if we have a selected pawn -> we want to play
    if(this->selectedPawn != nullptr)
    {
        int iGridIndex, jGridIndex;
        getGridIndexWithCoordinate(x, y, iGridIndex, jGridIndex);
        if(iGridIndex != -1)
            addPawn(iGridIndex, jGridIndex);
    }

    // else
    else
    {
        // if it's on a pawn we select it
        int pawnIndexWithClick = getPawnIndexWithCoordinate(x, y);
        if(pawnIndexWithClick != -1)
            selectPawn(pawnIndexWithClick);
    }

}

bool GameEngine::getEngineIsRunning() const
{
    return this->engineIsRunning;
}

bool GameEngine::getGameIsRunning() const
{
    return this->gameIsRunning;
}

bool GameEngine::getOnePlayer() const
{
    return onePlayer;
}

void GameEngine::setOnePlayer(bool b)
{
    onePlayer = b;
}

void GameEngine::endEngine()
{
    this->gameIsRunning = false;
    this->engineIsRunning = false;
}
