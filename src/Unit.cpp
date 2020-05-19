#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Unit::Unit(  )
{
}

Unit::Unit( double X, double Y, int mass /*= 1*/ )
{
    position = sf::Vector2f(X, Y);
    this->mass = mass;
    radius = mass;
    sprite = new CircleShape();
    color = Color(30, 144, 255); //domyslny kolor
}

Unit::Unit( Vector2f position, int mass /*= 1*/ )
{
    this->position = position;
    this->mass = mass;
    radius = mass;
    sprite = new CircleShape();
    color = Color(30, 144, 255); //domyslny kolor
}

Unit::~Unit()
{
    if( sprite != nullptr )
    {
        delete sprite;
    }
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
    sprite->setOrigin(radius, radius);
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
