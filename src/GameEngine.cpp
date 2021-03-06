#include "../include/GameEngine.h"
#include <iostream>
#include <string>

using namespace std;

GameEngine::GameEngine()
{
    this->grid.resize(4);
    this->selectedPawn = nullptr;
    for(int i = 0; i<4; i++) this->grid[i].resize(4);

    // build the text
    font.loadFromFile(FONT_PATH + "SF_Atarian_System.ttf");
    text.setFont(font);
    text.setCharacterSize(26);
    text.setColor(sf::Color(87, 49, 46));
    text.setPosition(20, 510);

    this->quitButton = new Button(500, 510, "Quitter");

    loadImages();
}

GameEngine::~GameEngine()
{
    delete this->shape;
    delete this->selectedPawn;

    clearGrid();
}

void GameEngine::start(Player* player2, Player* player1, ShapeName const& shapeName, int const& AIdif)
{
    this->player1 = player1;
    this->player2 = player2;
    this->shape = new Shape(shapeName);
    this->engineIsRunning = true;
    this->gameIsRunning = true;

    if(AIdif != 0)
    {
        this->onePlayer = true;
        this->AIdif = AIdif;
    }
    else
    {
        this->onePlayer = false;
        this->AIdif = 0;
    }

    loadAvailablePawns();

    if(shapeTexture != nullptr)
        delete shapeTexture;
    shapeTexture = new sf::Texture();
    shapeTexture->loadFromFile(SHAPES_PATH + "shape" + std::to_string((int) shapeName + 1) + ".png");

    text.setString("Selectionnez le pion de l'adverssaire");
}

bool GameEngine::isPlayable(int const& i, int const& j) const
{
    return (grid[i][j] == nullptr);
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

void GameEngine::playAI(int const& depth)
{
    int maxVal = -999999;
    int xBestPlay = -1;
    int yBestPlay = -1;

    // for each position in the grid
    for(unsigned int k = 0; k < this->grid.size(); k++)
    {
        for(unsigned int l = 0; l < this->grid.size(); l++)
        {
            int value = maxVal;
            if(isPlayable(k, l))
            {
                this->grid[k][l] = selectedPawn;
                selectedPawn->setPlayable(false);
                if(isWon(k, l))
                    value = 999999;
                else
                    //value = min(depth, k, l);
                    value = MINIMAX_AB(depth, k, l, -2000, 2000);

                this->grid[k][l] = nullptr;
                selectedPawn->setPlayable(true);
            }

            if(value > maxVal)
            {
                maxVal = value;
                xBestPlay = k;
                yBestPlay = l;
            }
        }
    }

    if(xBestPlay != -1) addPawn(xBestPlay, yBestPlay);

    // selects the Pawn the human player will have to play
    // random process to save time
    if(this->gameIsRunning)
    {
        int r;
        do
        {
            r = rand()%(16);
        }
        while(this->availablePawn[r] == nullptr || !this->availablePawn[r]->getPlayable());

        selectPawn(r);
    }
}

int GameEngine::min(int depth, int const& line, int const& col)
{
    int minVal = 9999999;

    if(depth == 0 || this->availablePawn.size() == 0)
        return evaluateGrid(grid, line, col);

    // test every playable Pawn
    for(unsigned int i = 0; i < this->availablePawn.size(); i++)
    {
        if(this->availablePawn[i] != nullptr && this->availablePawn[i]->getPlayable())
        {
            // at every playable position
            for(unsigned int k = 0; k <grid.size(); k++)
            {
                for(unsigned int l = 0; l < grid.size(); l++)
                {

                        int value = minVal;

                        if(isPlayable(k, l))
                        {
                            // change grid
                            this->grid[k][l] = this->availablePawn[i];
                            this->availablePawn[i]->setPlayable(false);

                            // get the value
                            if(isWon(k, l))
                                value = 999999;
                            else
                                value = max(depth - 1, k, l);

                            // grid as origin
                            this->grid[k][l] = nullptr;
                            this->availablePawn[i]->setPlayable(true);
                        }

                        if(value < minVal)
                            minVal = value;
                    }
                }
            }
    }

    return minVal;
}

int GameEngine::max(int depth, int const& line, int const& col)
{
    int maxVal = -9999999;

    if(depth == 0 || this->availablePawn.size() == 0)
        return evaluateGrid(grid, line, col);

    // test every playable Pawn
    for(unsigned int i = 0; i<this->availablePawn.size(); i++)
    {
        if(this->availablePawn[i] != nullptr && this->availablePawn[i]->getPlayable())
        {
            //at every playable position
            for(unsigned int k = 0; k<grid.size(); k++)
            {
                for(unsigned int l = 0; l<grid.size(); l++)
                {
                    int value = maxVal;

                    if(isPlayable(k, l))
                    {
                        // change grid
                        this->grid[k][l] = this->availablePawn[i];
                        this->availablePawn[i]->setPlayable(false);

                        if(isWon(k, l))
                            value = -999999;
                        else
                            value = min(depth - 1, k, l);

                        // grid as origin
                        this->grid[k][l] = nullptr;
                        this->availablePawn[i]->setPlayable(true);
                    }

                    if(value > maxVal)
                        maxVal = value;
                }
            }
        }
    }

    return maxVal;
}





int GameEngine::MINIMAX_AB(int depth, int const& line, int const& col, int const &A, int const&B)
{
    if(depth == 0 || this->availablePawn.size() == 0)
        return evaluateGrid(grid, line, col);


    int alpha = A;
    int beta = B;
    if(depth%2 == 0)
    {
        // test every playable Pawn
        for(unsigned int i = 0; i<this->availablePawn.size(); i++)
        {
            if(this->availablePawn[i] != nullptr && this->availablePawn[i]->getPlayable())
            {
                //at every playable position
                for(unsigned int k = 0; k<grid.size(); k++)
                {
                    for(unsigned int l = 0; l<grid.size(); l++)
                    {
                        int value;
                        if(isPlayable(k, l))
                        {
                            // change grid
                            this->grid[k][l] = this->availablePawn[i];
                            this->availablePawn[i]->setPlayable(false);

                            if(isWon(k, l))
                                value = -999999;
                            else
                                value = MINIMAX_AB(depth - 1, k, l, A, B);

                            // grid as origin
                            this->grid[k][l] = nullptr;
                            this->availablePawn[i]->setPlayable(true);

                            if(value<beta)
                                beta = value;
                            if(alpha>=beta)
                                return alpha;
                        }
                    }
                }
            }
        }
        return beta;
    }
    else
    {
        // test every playable Pawn
        for(unsigned int i = 0; i<this->availablePawn.size(); i++)
        {
            if(this->availablePawn[i] != nullptr && this->availablePawn[i]->getPlayable())
            {
                //at every playable position
                for(unsigned int k = 0; k<grid.size(); k++)
                {
                    for(unsigned int l = 0; l<grid.size(); l++)
                    {
                        int value;
                        if(isPlayable(k, l))
                        {
                            // change grid
                            this->grid[k][l] = this->availablePawn[i];
                            this->availablePawn[i]->setPlayable(false);

                            if(isWon(k, l))
                                value = -999999;
                            else
                                value = MINIMAX_AB(depth - 1, k, l, A, B);

                            // grid as origin
                            this->grid[k][l] = nullptr;
                            this->availablePawn[i]->setPlayable(true);

                            if(value>alpha)
                                alpha = value;
                            if(alpha>=beta)
                                return beta;
                        }
                    }
                }
            }
        }
        return alpha;
    }
}

int GameEngine::evaluateGrid(vector<vector<Pawn*>> const& grid, int const& line, int const& col) const
{
    int result = 0;
    if(grid[line][col] != nullptr)
    {
        // get ALL the possibilities of shapes at this point for the shape of the game
        vector<vector<vector<int>>> possibilitiesForLine = this->shape->getPossibleCoordinatesToCheck(line, col);

        // for each shape possibility
        for (unsigned int a = 0; a < possibilitiesForLine.size(); a++)
        {
            int pawnNbInShape = 0;
            int commonCharacteristics = 0;
            bool stillOkForBright = true, stillOkForSmall = true, stillOkForSquare = true, stillOkForHollow = true;
            Pawn* referencePawn = nullptr;

            // for each pawn in the shape
            for (unsigned int b = 0; b < possibilitiesForLine[a].size(); b++)
            {
                Pawn* currentPawn = grid[possibilitiesForLine[a][b][0]][possibilitiesForLine[a][b][1]];

                // check for reference pawn
                if(referencePawn == nullptr)
                {
                    if(currentPawn != nullptr)
                        referencePawn = currentPawn;
                }

                // we have the reference pawn and there's a new pawn in the shape
                else if(currentPawn != nullptr)
                {
                    // new pawn in shape
                    pawnNbInShape++;

                    // change boolean values
                    stillOkForBright = (stillOkForBright && referencePawn->getPoints()[0] == currentPawn->getPoints()[0]);
                    stillOkForSmall = (stillOkForSmall && referencePawn->getPoints()[1] == currentPawn->getPoints()[1]);
                    stillOkForSquare = (stillOkForSquare && referencePawn->getPoints()[2] == currentPawn->getPoints()[2]);
                    stillOkForHollow = (stillOkForHollow && referencePawn->getPoints()[3] == currentPawn->getPoints()[3]);
                }
            }

            commonCharacteristics = (int) stillOkForBright + (int) stillOkForSmall + (int) stillOkForSquare + (int) stillOkForHollow;
            result += pawnNbInShape * commonCharacteristics;
        }
    }

    return result;
}

void GameEngine::addPawn(int const& i, int const& j)
{
    if(selectedPawn != nullptr)
    {
        if(this->isPlayable(i, j))
        {
            grid[i][j] = selectedPawn;
            selectedPawn = nullptr;

            // if won
            if(isWon(i, j))
            {
                if(this->isPlayer1Turn)
                    text.setString("Partie gagnee par Joueur 1");
                else if (!this->onePlayer)
                    text.setString("Partie gagnee par Joueur 2");
                else
                    text.setString("Partie gagnee par l'IA");

                this->gameIsRunning = false;
            }
            else
                text.setString("Selectionnez le pion de l'adverssaire");
        }
    }
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
            playAI(this->AIdif);

        text.setString("Placez le pion sur la grille");
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

    // render bottom
    window.draw(text);
    this->quitButton->render(window);

    sf::Sprite temp;
    temp.setPosition(360, 475);
    temp.setTexture(*this->shapeTexture);
    window.draw(temp);
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

    if(this->quitButton->isClickedOnIt(x, y))
        endEngine();
}

bool GameEngine::getEngineIsRunning() const
{
    return this->engineIsRunning;
}

bool GameEngine::getGameIsRunning() const
{
    return this->gameIsRunning;
}

void GameEngine::endEngine()
{
    this->gameIsRunning = false;
    this->engineIsRunning = false;

    this->grid.clear();
    this->grid.resize(4);
    this->selectedPawn = nullptr;
    for(int i = 0; i<4; i++) this->grid[i].resize(4);
}
