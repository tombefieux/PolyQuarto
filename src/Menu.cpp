#include "../include/Menu.h"

Menu::Menu(GameEngine* engine)
{
    this->engine = engine;
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->currentMenuType = MenuType::PlayerNumber;
    this->selectedShape = ShapeName::Invaders;

    this->returnToNumber = new Button(20, 20, "Retour");

    this->onePlayerButton = new Button(BUTTON_X, BUTTON_Y, "Un joueur");
    this->twoPlayersButton = new Button(BUTTON_X, BUTTON_Y + 80, "Deux joueurs");

    this->easyButton = new Button(BUTTON_X, BUTTON_Y, "Facile");
    this->hardButton = new Button(BUTTON_X, BUTTON_Y + 80, "Difficile");

    this->shapeButtons = new ImageButton*[7];
    for(int i = 0; i < 7; i++)
    {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile(SHAPES_PATH + "shape" + std::to_string(i + 1) + ".png");
        this->shapeButtons[i] = new ImageButton(120 + (i * IMAGE_BUTTON_WIDTH) + (i * 20) - ((i / 4) * ((4 * IMAGE_BUTTON_WIDTH) + 40)), BUTTON_Y - 20 + ((i / 4) * (IMAGE_BUTTON_HEIGHT + 20)), texture);
    }

    this->background.loadFromFile(IMAGES_PATH + "menuBackground.png");
}

Menu::~Menu()
{
    delete player1;
    delete player2;

    delete onePlayerButton;
    delete twoPlayersButton;

    delete returnToNumber;

    delete easyButton;
    delete hardButton;

    delete[] shapeButtons;
}

void Menu::handleLeftClick(int const& x, int const& y)
{
    // depends of the current type of menu
    switch (this->currentMenuType) {
        case PlayerNumber:
            if(this->twoPlayersButton->isClickedOnIt(x, y))
            {
                onePlayer = false;
                this->currentMenuType = MenuType::Shape;

                if(player1 != nullptr)
                    delete player1;
                player1 = new Player("Joueur 1");

                if(player2 != nullptr)
                    delete player2;
                player2 = new Player("Joueur 2");
            }

            else if(this->onePlayerButton->isClickedOnIt(x, y))
            {
                onePlayer = true;
                this->currentMenuType = MenuType::Difficulty;

                if(player1 != nullptr)
                    delete player1;
                player1 = new Player("Joueur 1");
            }
            break;

        case Difficulty:
            if(this->easyButton->isClickedOnIt(x, y))
            {
                this->currentMenuType = MenuType::Shape;

                // TODO: change for IA
                if(player2 != nullptr)
                    delete player2;

                this->engine->setOnePlayer(true);
                /*
                AI ai = AI("IA", 2);
                player2 = &ai;
                */
            }

            else if(this->hardButton->isClickedOnIt(x, y))
            {
                this->currentMenuType = MenuType::Shape;

                // TODO: change for IA
                if(player2 != nullptr)
                    delete player2;

                this->engine->setOnePlayer(true);
                /*
                AI ai = AI("IA", 4);
                player2 = &ai;
                */
            }

            else if(this->returnToNumber->isClickedOnIt(x, y))
                this->currentMenuType = MenuType::PlayerNumber;

            break;

        case Shape:
            if(this->returnToNumber->isClickedOnIt(x, y))
                this->currentMenuType = MenuType::PlayerNumber;
            else
            {
                bool selected = false;
                for(int i = 0; i < 7 && !selected; i++)
                    if(this->shapeButtons[i]->isClickedOnIt(x, y))
                    {
                        this->selectedShape = (ShapeName) i;
                        selected = true;
                    }

                if(selected) launchEngine();
            }
            break;
    }
}

void Menu::render(sf::RenderWindow &window) const
{
    sf::Sprite sprite;
    sprite.setTexture(this->background);
    window.draw(sprite);

    // depends of the current type of menu
    switch (this->currentMenuType) {
        case PlayerNumber:
            drawPLayerNumber(window);
            break;

        case Difficulty:
            drawDifficulty(window);
            break;

        case Shape:
            drawShape(window);
            break;
    }
}

void Menu::drawPLayerNumber(sf::RenderWindow &window) const
{
    this->onePlayerButton->render(window);
    this->twoPlayersButton->render(window);
}

void Menu::drawDifficulty(sf::RenderWindow &window) const
{
    this->easyButton->render(window);
    this->hardButton->render(window);
    this->returnToNumber->render(window);
}


void Menu::drawShape(sf::RenderWindow &window) const
{
    for(int i = 0; i < 7; i++)
        this->shapeButtons[i]->render(window);

    this->returnToNumber->render(window);
}

void Menu::launchEngine()
{
    this->engine->start(this->player1, this->player2, this->selectedShape);
    this->currentMenuType = MenuType::PlayerNumber;
}
