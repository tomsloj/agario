#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.hpp"
#include <vector>

class Player
{
    private:
        
    public:
        Player();
        Player(double x, double y);
        Player( Cell* cell );
        ~Player();
        
        void setColor( sf::Color color);
        void draw( sf::RenderWindow& window);

        std::vector<Cell*>playerCells;
};

#endif 