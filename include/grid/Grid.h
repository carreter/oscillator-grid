#pragma once
#include <SFML/Graphics.hpp>

class Grid {
    protected:
        int width;
        int height;

        bool inBounds(const int &x, const int &y);

    public:
        virtual ~Grid() {};

        virtual float getValue(const int &x, const int &y) = 0;
        virtual void setValue(const int &x, const int &y, const float &val) = 0;

        virtual void update(sf::Time &dt) = 0;
};