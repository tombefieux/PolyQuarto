#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/GameEngine.h"
#include "include/Menu.h"
#include "include/Config.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PolyQuarto");
    GameEngine engine;
    Menu menu(&engine);

    // game loop
    while (window.isOpen())
    {
        // check events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // mouse click event
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if(!engine.getEngineIsRunning())
                        menu.handleLeftClick(event.mouseButton.x, event.mouseButton.y);
                    else
                        engine.handleLeftClick(event.mouseButton.x, event.mouseButton.y);
                }
            }

            // window closed
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        // render
        window.clear();
        if(!engine.getEngineIsRunning())
            menu.render(window);
        else
            engine.render(window);
        window.display();

        // sleep (for the FPS)
        this_thread::sleep_for(chrono::milliseconds(1000 / (long) FPS));
    }

    return 0;
}
