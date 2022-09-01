#include "grid/Grid.h"

#include "render/GridRenderer.h"


bool Grid::inBounds(const int &x, const int &y) {
    return x > 0 && x < width && y > 0 && y < height;
}