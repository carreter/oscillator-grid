#pragma once
#include <SFML/Graphics.hpp>
#include "grid/Grid.h"

class OscillatorGrid : Grid {
    private:
        float coupling;
        float damping;

        float **posGrid;
        float **velGrid;

        float **initilizeGrid();
        void deleteGrid(float **grid);

    public:
        OscillatorGrid(const int width, const int height, float coupling, float damping);
        ~OscillatorGrid();

        float getValue(const int &x, const int &y);
        void setValue(const int &x, const int &y, const float &val);

        void update(sf::Time &dt);
};