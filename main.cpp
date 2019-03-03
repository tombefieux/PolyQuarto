#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "GameEngine.h"
#include "Config.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Quarto");
    GameEngine engine;

    // actually start a game with this names
    engine.start("Bob", "Cedric");

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        engine.render(window);
        window.display();

        // sleep (for the FPS)
        this_thread::sleep_for(chrono::milliseconds(1000 / (long) FPS));
    }

    return 0;
}
