#ifndef CELL_H
#define CELL_H

#include "Unit.hpp"

#include <SFML/Graphics.hpp>

class Cell : public Unit
{
    private:
        double speed;
        double acceleration;
    public:
        Cell();
        void updateSpeed();
};

#endif 