#ifndef MANUAL_PLAYER_H
#define MANUAL_PLAYER_H

#include <cmath>

#include "Player.hpp"
#include "GlobalValues.hpp"

class ManualPlayer : public Player
{
    private:

    public:
        ManualPlayer(double x, double y);
        ManualPlayer(Cell* cell);
        void setMousePosition(sf::Vector2i position);

        std::vector<Cell*> Divide(sf::Vector2i mousePosition);
};

#endif 