#include "../include/Cell.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Cell::Cell()
{
}

Cell::Cell( double X, double Y, int mass /*= 1*/ ) : Unit(X, Y, mass)
{
    speed = 2.0;
}

Cell::Cell( Vector2f position, int mass /*= 1*/ ) : Unit(position, mass)
{
    speed = 2.0;
}

void Cell::updateSpeed()
{
    
}

void Cell::setDirecction(double x, double y)
{
    xDirection = x;
    yDirection = y;
}

void Cell::update()
{
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
/*
void Cell::draw( RenderWindow& window ) : Unit(window)
{

}
*/