#include "../include/Cell.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Cell::Cell()
{

}

Cell::Cell( double X, double Y, int mass /*= 1*/ ) : Unit(X, Y, mass)
{
    speed = 1.0 / sqrt(radius/2);
}

Cell::Cell( Vector2f position, int mass /*= 1*/ ) : Unit(position, mass)
{
    speed = 1.0 / sqrt(radius/2);
}

Cell::~Cell() = default;


void Cell::updateSpeed()
{
    speed = 1.0 / sqrt(radius/2);
}

void Cell::setDirecction(double x, double y)
{
    xDirection = x;
    yDirection = y;
}

void Cell::update()
{
    updateSpeed();
    position.x += xDirection*speed;
    position.y += yDirection*speed;
    if( position.x < radius )
        position.x = radius ;
    if( position.y < radius )
        position.y = radius;
    if( position.x > gameWindowWidth - radius)
        position.x = gameWindowWidth - radius;
    if( position.y > gameWindowHeight - radius)
        position.y = gameWindowHeight - radius;
}

double Cell::distance(Unit &unit)
{
    double x = position.x - unit.getPosition().x;
    double y = position.y - unit.getPosition().y;
    return sqrt( x * x + y * y );
}

double Cell::distance(Cell &cell)
{
    double x = position.x - cell.getPosition().x;
    double y = position.y - cell.getPosition().y;
    return sqrt( x * x + y * y );
}


void Cell::grow(const int massOfGrowth)
{
    Unit::grow(massOfGrowth);
    updateSpeed();
}

sf::Vector2i Cell::getDirection()
{
    return sf::Vector2i(xDirection, yDirection);
}

/*
void Cell::draw( RenderWindow& window ) : Unit(window)
{

}
*/