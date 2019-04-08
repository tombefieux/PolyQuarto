#include "../include/Menu.h"

Menu::Menu(GameEngine* engine)
{
    this->engine = engine;
    this->player1 = nullptr;
    this->player2 = nullptr;
    this->currentMenuType = MenuType::PlayerNumber;
    this->selectedShape = ShapeName::Invaders;

    this->returnToNumber = new Button(20, 20, "Retour");

    this->onePlayerButton = new Button(BUTTON_X, 200, "Un joueur");
    this->twoPlayersButton = new Button(BUTTON_X, 280, "Deux joueurs");

    this->easyButton = new Button(BUTTON_X, 200, "Facile");
    this->hardButton = new Button(BUTTON_X, 280, "Difficile");

    this->background.loadFromFile(IMAGES_PATH + "menuBackground.png");
}

Menu::~Menu()
{
    delete player1;
    delete player2;

    delete onePlayerButton;
    delete twoPlayersButton;
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

                // TEMP
                launchEngine();
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
                player2 = new Player("IA");
            }

            else if(this->hardButton->isClickedOnIt(x, y))
            {
                this->currentMenuType = MenuType::Shape;

                // TODO: change for IA
                if(player2 != nullptr)
                    delete player2;
                player2 = new Player("IA");
            }

            else if(this->returnToNumber->isClickedOnIt(x, y))
                this->currentMenuType = MenuType::PlayerNumber;

            break;

        case Shape:



            // launchEngine();
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

}

void Menu::launchEngine()
{
    this->engine->start(this->player1, this->player2, this->selectedShape);
    this->currentMenuType = MenuType::PlayerNumber;
}