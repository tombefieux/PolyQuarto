#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/GameEngine.h"
#include "include/Config.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quarto");
    GameEngine engine;

    // actually start a game with this names
    Player* player1 = new Player("Bob");
    Player* player2 = new Player("Patrick");
    engine.start(player1, player2, ShapeName::Invaders);

    // game loop
    while (window.isOpen())
    {


        // TODO: menu stuff



        // while the engine needs to render
        while(engine.getEngineIsRunning() && window.isOpen())
        {
            // check events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // mouse click event
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                        engine.handleLeftClick(event.mouseButton.x, event.mouseButton.y);
                }

                    // window closed
                else if (event.type == sf::Event::Closed)
                    window.close();
            }

            // render
            window.clear();
            engine.render(window);
            window.display();

            // sleep (for the FPS)
            this_thread::sleep_for(chrono::milliseconds(1000 / (long) FPS));
        }
    }

    delete player1;
    delete player2;

    return 0;
}
