#include "../include/BotBehaviour.hpp"

#include <iostream>

using namespace sf;


BotBehaviour::BotBehaviour(double x, double y) : Bot(x, y)
{
    setColor(Color::Green);
}

BotBehaviour::BotBehaviour( Cell* cell ) : Bot( cell )
{
    setColor(Color::Green);
}

// position - pozycja najblizszego czegos co moze zjesc / od czego trzeba uciekac
void BotBehaviour::setNextPosition(std::vector<Unit*> feedUnits, std::vector<Cell*> cells)
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

        
        x /= length;
        y /= length;

        if(abs(x) < 1)
        {
            if(x < 0) x -= 1;
            else if (x > 0) x += 1;          
        }

        if(abs(y) < 1)
        {
            if(y < 0) y -= 1;
            else if (y > 0) y += 1;          
        }

        cell->setDirecction(((x + cell->getDirection().x) / 2), ((y + cell->getDirection().y) / 2) );
        cell->update();
    }
}