#include "config.h"
#include "grid/OscillatorGrid.h"
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 800.f

#define GRID_WIDTH 100
#define GRID_HEIGHT 100


#define COUPLING .1f
#define DAMPING 0.01f

int main(int argc, char* argv[]) 
{
    // Create a video mode object
    sf::VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create and open a window
    sf::RenderWindow window(vm, "Pong", sf::Style::None);
    sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setView(view);

    // Create oscillator grid
    OscillatorGrid grid(GRID_WIDTH, GRID_HEIGHT, COUPLING, DAMPING);

    // Create display grid
    float dotSize = WINDOW_HEIGHT / GRID_HEIGHT;
    sf::CircleShape ***displayGrid = new sf::CircleShape**[GRID_WIDTH];
    for (int i = 0; i < GRID_WIDTH; i++) {
        displayGrid[i] = new sf::CircleShape*[GRID_HEIGHT];

        for (int j = 0; j < GRID_HEIGHT; j++) {
            displayGrid[i][j] = new sf::CircleShape(dotSize / 2);
            displayGrid[i][j]->setPosition(i * dotSize, j * dotSize);
            displayGrid[i][j]->setFillColor(sf::Color::Yellow);
            displayGrid[i][j]->setOrigin(dotSize / 2, dotSize / 2);
        }
    }


    std::string source_dir = RESOURCE_PATH; 
#ifndef NDEBUG
    // Output RESOURCE_PATH
    std::cout << "RESOURCE_PATH: " << source_dir << std::endl;
#endif


    // Clock for timing everything
    sf::Clock clock;

    // Flag for updating the score
    while (window.isOpen())
    {
        /* Handle the player input
         *****************************************/
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                grid.setValue(static_cast<int>(pos.x / dotSize), static_cast<int>(pos.y / dotSize), 50.f);
            }
        }
            

        /*
         * Update
         *****************************************/
        // Update delta time
        sf::Time dt = clock.restart();
        grid.update(dt);


        /*
         * Draw
         ****************************************/
        window.clear();
        for (int i = 0; i < GRID_WIDTH; i++)
            for (int j = 0; j < GRID_HEIGHT; j++) {
                float val = grid.getValue(i, j);
                displayGrid[i][j]->setScale(val, val);
                window.draw(*displayGrid[i][j]);
            }
        window.display();
    }

    return EXIT_SUCCESS;
}
