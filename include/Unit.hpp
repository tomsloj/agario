#ifndef UNIT_H
#define UNIT_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

class Unit
{
    private:
        sf::CircleShape *sprite;
        sf::Color color;
    protected:
        sf::Vector2f position;
        double radius;
        int mass;
    public:
        Unit();
        Unit( double X, double Y, int mass = 1 );
        Unit( sf::Vector2f position, int mass = 1 );
        virtual ~Unit();
        virtual void grow(const int massOfGrowth);
        void decreaseMass( int massReduction = 1 );
        void setMass (int newMass);
        int getMass() const;
        sf::Color getColor() const;
        sf::Vector2f getPosition() const;
        double getRadius() const;
        void draw(sf::RenderWindow& window);
        void setColor(sf::Color color);
        void setPosition( sf::Vector2f position );
        void setRadius( int mass );

        friend std::ostream& operator<<(std::ostream& stream,  const Unit& unit);
        friend std::istream& operator>>(std::istream& stream,  Unit& unit);
};

#endif 