#ifndef MANUAL_PLAYER_H
#define MANUAL_PLAYER_H

#include <cmath>

#include "Player.hpp"

class ManualPlayer : public Player
{
    private:

    public:
        ManualPlayer(double x, double y);
        void setMousePosition(sf::Vector2i position);
};

#endif 