#ifndef UNIT_H
#define UNIT_H

#include <cmath>
#include <SFML/Graphics.hpp>

class Unit
{
    private:
        int mass;
        
        sf::CircleShape *sprite;
        sf::Color color;
    protected:
        sf::Vector2f position;
        double radius;
    public:
        Unit();
        Unit( double X, double Y, int mass = 1 );
        Unit( sf::Vector2f position, int mass = 1 );
        ~Unit();
        virtual void grow(const int massOfGrowth);
        void increaseMass( int massReduction = 1 );
        int getMass();
        sf::Vector2f getPosition();
        double getRadius();
        void draw(sf::RenderWindow& window);
        void setColor(sf::Color color);
        void setPosition( sf::Vector2f position );
        void setRadius( int mass );
};

#endif 