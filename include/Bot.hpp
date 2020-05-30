#ifndef BOT_H
#define BOT_H

#include "Player.hpp"

class Bot : public Player
{
    private:

    public:

        std::vector<Cell*>botCells;

        Bot();
        Bot(double x, double y);
        Bot( Cell* cell );
        ~Bot();

        void setColor( sf::Color color);

        void setNextPosition(std::vector<Unit*> feedUnits, std::vector<Cell*> cells);
};

#endif 