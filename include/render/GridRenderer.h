#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "grid/Grid.h"

class ScalingGridRenderer : sf::Drawable {
    private:
        Grid *grid;
        sf::Window *window;

        std::vector<sf::Shape> shapes;

    public:
        ScalingGridRenderer(Grid *grid, sf::Window *window, sf::Shape baseShape);
        ~ScalingGridRenderer();
};