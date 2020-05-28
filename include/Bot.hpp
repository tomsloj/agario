#ifndef BOT_H
#define BOT_H

#include "Player.hpp"

class Bot : public Player
{
    private:

    public:

        Bot();
        Bot(double x, double y);
        Bot( Cell* cell );
        ~Bot();

        std::vector<Cell*>botCells;
};

#endif 