#ifndef CELL_H
#define CELL_H

#include "Unit.hpp"
#include "GlobalValues.hpp"

#include <cmath>
#include <SFML/Graphics.hpp>

class Cell : public Unit
{
    private:
        double speed;
        double acceleration;
        //wektor jednostkkowy  wskazujacy kierunek
        double xDirection;
        double yDirection;
    public:
        Cell();
        Cell( double X, double Y, int mass = 1 );
        Cell( sf::Vector2f position, int mass = 1 );
        ~Cell();
        void updateSpeed();
        void setDirecction(double x, double y);
        void update();
        double distance(Unit &unit);
        double distance(Cell &cell);
        void grow(const int massOfGrowth);

        sf::Vector2i getDirection();

        //void draw( sf::RenderWindow& window );
};

#endif 