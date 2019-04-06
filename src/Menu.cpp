#include "../include/Menu.h"

Menu::Menu(GameEngine* engine)
{
    this->engine = engine;
    player1 = new Player("Joueur 1");
    player2 = new Player("Joueur 2");

    this->engine->start(player1, player2, ShapeName::Invaders);
}

Menu::~Menu()
{
    delete player1;
    delete player2;
}

void Menu::handleLeftClick(int const& x, int const& y)
{

}

void Menu::render(sf::RenderWindow &window) const
{

}