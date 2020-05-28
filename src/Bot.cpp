#include "../include/Bot.hpp"

#include <iostream>

Bot::Bot()
{
    //botCells.push_back(Cell());
}

//create new bot - one cell
Bot::Bot(double x, double y)
{
    botCells.push_back(new Cell(x, y, rand()%100));
}

Bot::Bot( Cell* cell)
{
    botCells.push_back( cell );
}

Bot::~Bot()
{
    botCells.clear();
}
