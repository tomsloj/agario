#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Unit::Unit(  )
{
    sprite = new CircleShape();
}

Unit::Unit( double X, double Y, int mass /*= 1*/ )
{
    position = sf::Vector2f(X, Y);
    this->mass = mass;
    //radius = mass;
    sprite = new CircleShape();
    color = Color(30, 144, 255); //domyslny kolor
    setRadius( mass );
}

Unit::Unit( Vector2f position, int mass /*= 1*/ )
{
    this->position = position;
    this->mass = mass;
    //radius = mass;
    sprite = new CircleShape();
    color = Color(30, 144, 255); //domyslny kolor
    setRadius( mass );
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

void Unit::decreaseMass( int massReduction /*= 1*/ )
{
    mass -= massReduction;
}

void Unit::setMass (int newMass)
{
    mass = newMass;
}

int Unit::getMass() const
{
    return mass;
}

sf::Vector2f Unit::getPosition() const
{
    return position;
}

double Unit::getRadius() const
{
    return radius;
}

sf::Color Unit::getColor() const
{
    return color;
}

void Unit::draw( RenderWindow& window) 
{
    setRadius( mass );
    try
    {
        sprite->setOrigin(radius, radius);
        sprite->setPosition(position);
        sprite->setRadius(radius);
        sprite->setFillColor(color);
        window.draw(*sprite);
    }
    catch (std::exception& e)
    {
        std::cerr << "cannot draw shape: " << e.what() << "\n";
    }
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
    radius = sqrt(mass);
}

std::ostream& operator<<(std::ostream& stream,  const Unit& unit)
{
    stream << unit.mass << "\n";
    stream << unit.color.r<< "\n";
    stream << unit.color.g << "\n";
    stream << unit.color.b << "\n";
    stream << unit.color.a << "\n";
    stream << unit.position.x << "\n";
    stream << unit.position.y << "\n";
    stream << unit.radius << "\n";
    return stream;
}

std::istream& operator>>(std::istream& stream,  Unit& unit)
{
    stream >> unit.mass;
    stream >> unit.color.r;
    stream >> unit.color.g;
    stream >> unit.color.b;
    stream >> unit.color.a;
    stream >> unit.position.x;
    stream >> unit.position.y;
    stream >> unit.radius;
    return stream;
}
