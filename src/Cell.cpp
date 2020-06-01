#include "../include/Cell.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>



using namespace sf;

Cell::Cell()
{

}

Cell::Cell( double X, double Y, double acc, bool isItPlayer, int mass /*= 1*/) : Unit(X, Y, mass)
{
    acceleration = acc;
    isPlayer = isItPlayer;
    speed = basicSpeed / sqrt(radius/2) + acc;
    clock.restart();
    stepsToDecreaseMass = calculateSteps();
}

Cell::Cell( Vector2f position, double acc, bool isItPlayer, int mass /*= 1*/) : Unit(position, mass)
{
    Cell(position.x, position.y, acc, isItPlayer, mass);
}

Cell::~Cell()
{
}


void Cell::updateSpeed()
{
    speed = basicSpeed / sqrt(radius/2) + acceleration;
    //redukcja przyspieszenia
    if(acceleration > 0 && clock.getElapsedTime().asMilliseconds() > 0.1)
    {
        acceleration -= 0.1;
        speed = basicSpeed / sqrt(radius/2) + acceleration;
        clock.restart();
        updateSpeed();
    }

}

void Cell::setDirecction(double x, double y)
{
    xDirection = x;
    yDirection = y;
}

void Cell::setAsPlayer()
{
    isPlayer = true;
}

void Cell::setAcceleration(double acc)
{
    acceleration = acc;
}

double Cell::getSpeed()
{
    return speed;
}

void Cell::update()
{
    //mechanizm glodu
    --stepsToDecreaseMass;
    if( stepsToDecreaseMass <= 0 )
    {
        if( mass > 1    )
            decreaseMass(1);
        stepsToDecreaseMass = calculateSteps();
    }

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

int Cell::calculateSteps()
{
    return static_cast<int>(20000.0/static_cast<double>(mass));
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

bool Cell::isItPlayer()
{
    return isPlayer;
}

Cell *Cell::Division(sf::Vector2i mousePosition)
{
    static const double SPEED = 5.0;

	Cell *newcell;
	double tmpX;
    double tmpY;
	int newMass;

    sf::Vector2f position = Unit::getPosition();
	double cosalpha, sinalpha;
	cosalpha = (mousePosition.x - position.x) / sqrt((mousePosition.x - position.x) * (mousePosition.x - position.x) + (mousePosition.y - position.y) * (mousePosition.y - position.y));
	sinalpha = (mousePosition.y - position.y) / sqrt((mousePosition.x - position.x) * (mousePosition.x - position.x) + (mousePosition.y - position.y) * (mousePosition.y - position.y));
	tmpX = (position.x + cosalpha*(1.5*Unit::getRadius()));
	tmpY = (position.y + sinalpha*(1.5*Unit::getRadius()));


    newMass = Unit::getMass() / 2;
    Unit::setMass(newMass);

	newcell = new Cell(tmpX, tmpY, SPEED, true,  newMass);
    newcell->setColor(sf::Color::Red);
	return newcell;
}