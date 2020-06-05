#ifndef BOT_H
#define BOT_H

#include "Player.hpp"

class Bot : public Player
{
    private:
        std::vector<Cell*>botCells;

    public:

        

        Bot();
        Bot(double x, double y);
        Bot( Cell* cell );
        ~Bot();

        void setColor( sf::Color color);
        std::vector<Cell*> getBotCells();

        void setNextPosition(std::vector<Unit*> feedUnits, std::vector<Cell*> cells);
};

#endif 