#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.hpp"
#include <vector>

class Player
{
    private:
        
    public:
        std::vector<Cell*> cells;

        Player();
        Player(double x, double y, double acc, int mass);
        Player(Cell* cell);
        ~Player();
        
        void setColor( sf::Color color);
        void draw( sf::RenderWindow& window);

        void addCell(Cell* cell);
        void removeCell(Cell* cell);
};

#endif 