#include "../include/Bot.hpp"

#include <iostream>

using namespace sf;

Bot::Bot()
{
    setColor(Color::Green);
}

//create new bot - one cell
Bot::Bot(double x, double y)
{
    botCells.push_back(new Cell(x, y, 0, false, rand()%( 60 * level) + 2));
    setColor(Color::Green);
}

Bot::Bot( Cell* cell)
{
    botCells.push_back( cell );
    setColor(Color::Green);
}

Bot::~Bot()
{
    botCells.clear();
}

void Bot::setNextPosition(std::vector<Unit*> feedUnits, std::vector<Cell*> cells)
{
    double length = 10000;
    double x;
    double y;

    double prioryty; // priority = 1 / dostance to smaller - 1 / distance to bigger
    double tmpBiggestSamller;
    double tmpNearestBiggerSize;
    double nearestBigger;
    double nearestSmaller;
    double xSecondCellBigger;
    double ySecondCellBigger;
    double xSecondCellSmaller;
    double ySecondCellSmaller;

    for(auto cell: botCells)
    {
        length = 1000;
        tmpBiggestSamller = 0;
        tmpNearestBiggerSize = 0;
        nearestBigger = 1000;
        nearestSmaller = 1000;


        for(auto feedUnit : feedUnits)
        {
            double tmpX = static_cast<double>(feedUnit->getPosition().x  - cell->getPosition().x);
            double tmpY = static_cast<double>(feedUnit->getPosition().y  - cell->getPosition().y);

            double newLength = sqrt(tmpX*tmpX + tmpY*tmpY);

            if(newLength < length)
            {
                length = newLength;
                x = tmpX;
                y = tmpY;
            } 
        }

        for(auto secondCell : cells)
        {

            double tmpX = static_cast<double>(secondCell->getPosition().x  - cell->getPosition().x);
            double tmpY = static_cast<double>(secondCell->getPosition().y  - cell->getPosition().y);

            double newLength = sqrt(tmpX*tmpX + tmpY*tmpY);

            if(secondCell->getMass() > cell->getMass() && nearestBigger > newLength && newLength - secondCell->getRadius() < cell->getRadius() * 2)
            {
                tmpNearestBiggerSize = secondCell->getMass();
                nearestBigger = newLength - secondCell->getRadius();
                xSecondCellBigger = tmpX;
                ySecondCellBigger = tmpY;
            }
            else if(secondCell->getMass() < cell->getMass() && tmpBiggestSamller < secondCell->getMass() && newLength - secondCell->getRadius() < cell->getRadius() * 4)
            {
                nearestSmaller = newLength - secondCell->getRadius();
                tmpBiggestSamller = secondCell->getMass();
                xSecondCellSmaller = tmpX;
                ySecondCellSmaller = tmpY;
            }
            
        }
        prioryty = 1 / nearestSmaller - 1 / nearestBigger; // choose to run or to chase

        if(prioryty > 0)
        {
            if(1/length < 1/nearestSmaller * tmpBiggestSamller)
            {
                x = xSecondCellSmaller;
                y = ySecondCellSmaller;
            }
        }
        else
        {
            if(1/length < 1/nearestBigger * tmpNearestBiggerSize)
            {
                x = -xSecondCellBigger;
                y = -ySecondCellBigger;
            }
        }

        x = (x + cell->getDirection().x) / 2;
        y = (y + cell->getDirection().y) / 2;
        
        double length = sqrt(x*x + y*y);

        cell->setDirecction( x/length, y/length );
        cell->update();
    }
}

void Bot::setColor( Color color )
{
    for(auto cell: botCells)
        cell->Unit::setColor(color);
}
