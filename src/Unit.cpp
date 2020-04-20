#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Unit::Unit(  )
{
    std::cout<<"UNIT\n";
}

Unit::Unit( double X, double Y, int size /*= 1*/ )
{
    std::cout<<"UNIT\n";
    position = sf::Vector2f(X, Y);
    this->size = size;
    sprite = new CircleShape();
}

Unit::Unit( Vector2f position, int size /*= 1*/ )
{
    std::cout<<"UNIT\n";
    this->position = position;
    this->size = size;
    sprite = new CircleShape();
}

void Unit::grow(const int sizeOfGrowth)
{
    size += sizeOfGrowth;
}

void Unit::increaseSize( int sizeReduction /*= 1*/ )
{
    size -= sizeReduction;
}

int Unit::getSize()
{
    return size;
}

void Unit::draw(sf::RenderWindow& window)
{
    sprite->setPosition(position);
    sprite->setRadius(size);
    sprite->setFillColor(color);
    window.draw(*sprite);
}