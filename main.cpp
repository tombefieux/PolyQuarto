#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/GameEngine.h"
#include "include/Shape.h"
#include "include/Config.h"

#include <vector>

int main()
{
    Shape shape(ShapeName::Line);
    std::vector<std::vector<std::vector<int>>> result = shape.getPossibleCoordinatesToCheck(0, 0);
    std::cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j][0] << " " << result[i][j][1] << endl;
        }

        std::cout << "----" << endl;
    }




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

        window.clear();
        engine.render(window);
        window.display();

        // sleep (for the FPS)
        this_thread::sleep_for(chrono::milliseconds(1000 / (long) FPS));
    }

    return 0;
}
