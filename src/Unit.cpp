#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Unit::Unit(  )
{
    std::cout<<"UNIT\n";
}

Unit::Unit( double X, double Y, int mass /*= 1*/ )
{
    std::cout<<"UNIT\n";
    position = sf::Vector2f(X, Y);
    this->mass = mass;
    radius = mass;
    sprite = new CircleShape();
}

Unit::Unit( Vector2f position, int mass /*= 1*/ )
{
    std::cout<<"UNIT\n";
    this->position = position;
    this->mass = mass;
    radius = mass;
    sprite = new CircleShape();
}

void Unit::grow(const int massOfGrowth)
{
    mass += massOfGrowth;
}

void Unit::increaseMass( int massReduction /*= 1*/ )
{
    mass -= massReduction;
}

int Unit::getMass()
{
    return mass;
}

sf::Vector2f Unit::getPosition()
{
    return position;
}

void Unit::draw( RenderWindow& window) 
{
    setRadius( mass );
    sprite->setPosition(position);
    sprite->setRadius(radius);
    sprite->setFillColor(color);
    window.draw(*sprite);
}

void Unit::setColor( Color color)
{
    this->color = color;
}

void Unit::setPosition( Vector2f position )
{
    this->position = position;
}

void Unit::setRadius( int mass )
{
    //trzeba to zoptymalizowa 
    radius = mass;
}
