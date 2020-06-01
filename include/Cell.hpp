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
        double xDirection;
        double yDirection;
        bool isPlayer;
        sf::Clock clock;
        int stepsToDecreaseMass;
        
    public:
        Cell();
        Cell( double X, double Y, double acceleration, bool isItPlayer,  int mass = 1 );
        Cell( sf::Vector2f position, double acceleration, bool isItPlayer, int mass = 1 );
        ~Cell();
        void updateSpeed();
        void setDirecction(double x, double y);
        void setAsPlayer();
        void setAcceleration(double acc);
        void update();
        int calculateSteps();
        double distance(Unit &unit);
        double distance(Cell &cell);
        void grow(const int massOfGrowth);

        bool isItPlayer();

        Cell *Division(sf::Vector2i mousePosition);

        sf::Vector2i getDirection();

        //void draw( sf::RenderWindow& window );
};

#endif 