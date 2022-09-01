#include "grid/OscillatorGrid.h"
#include <vector>
#include <algorithm>
#include <cmath>

const std::vector<std::pair<int, int>> NEIGHBORS({{0,1}, {1,0}, {-1,0}, {0,-1}});
const std::vector<std::pair<int, int>> DIAG_NEIGHBORS({{1,1}, {1,-1}, {-1,-1}, {-1,1}});

OscillatorGrid::OscillatorGrid(const int width, const int height, float coupling, float damping) 
    : coupling(coupling)
    , damping(damping)
{
    this->width = width;
    this->height = height;
    posGrid = initilizeGrid();
    velGrid = initilizeGrid();
}

float **OscillatorGrid::initilizeGrid() {
    float **newGrid = new float*[width];
    for (int i = 0; i < width; i++) {
        newGrid[i] = new float[height];
        for(int j = 0; j < height; j++) {
            newGrid[i][j] = 0;
        }
    }
    return newGrid;
}

void OscillatorGrid::deleteGrid(float **grid) {
    for (int i = 0; i < width; i++)
        delete grid[i];
    delete grid;
}

OscillatorGrid::~OscillatorGrid() {
    deleteGrid(posGrid);
    deleteGrid(velGrid);
}

float OscillatorGrid::getValue(const int &x, const int &y) {
    return posGrid[x][y];
}

void OscillatorGrid::setValue(const int &x, const int &y, const float &val) {
    posGrid[x][y] = val;
}

void OscillatorGrid::update(sf::Time &dt) {
    // Update velocity
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float nextVel = velGrid[x][y] - (damping * posGrid[x][y]);

            for (auto neighbor : NEIGHBORS) {
                int dx, dy;
                std::tie(dx, dy) = neighbor;

                if (inBounds(x + dx, y + dy)) {
                    nextVel += coupling * (posGrid[x + dx][y + dy] - posGrid[x][y]);
                }
            }


            for (auto neighbor : DIAG_NEIGHBORS) {
                int dx, dy;
                std::tie(dx, dy) = neighbor;

                if (inBounds(x + dx, y + dy)) {
                    nextVel += (1 / sqrt(2)) * coupling * (posGrid[x + dx][y + dy] - posGrid[x][y]);
                } else {
                    nextVel *= damping;
                }
            }

            velGrid[x][y] = nextVel;
        }
    }

    // Update position
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            posGrid[x][y] += velGrid[x][y] * dt.asSeconds();
    
}