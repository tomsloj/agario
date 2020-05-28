#ifndef BOT_BEHAVIOUR_H
#define BOT_BEHAVIOUR_H

#include "Bot.hpp"
#include <vector>

class BotBehaviour : public Bot
{
    private:
        
    public:
        BotBehaviour(double x, double y);
        BotBehaviour(Cell* cell);
        void setNextPosition(std::vector<Unit*> feedUnits, std::vector<Cell*> cells);
};

#endif 