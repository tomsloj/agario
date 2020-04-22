#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>

class Unit
{
    private:
        int mass;
        double radius;
        sf::Vector2f position;
        sf::CircleShape *sprite;
        sf::Color color;
    public:
        Unit();
        Unit( double X, double Y, int mass = 1 );
        Unit( sf::Vector2f position, int mass = 1 );
        void grow(const int massOfGrowth);
        void increaseMass( int massReduction = 1 );
        int getMass();
        sf::Vector2f getPosition();
        void draw(sf::RenderWindow& window);
        void setColor(sf::Color color);
        void setPosition( sf::Vector2f position );
        void setRadius( int mass );sf::Color color);
        void setPosition( sf::Vector2f position );
        void setRadius( int mass );
};

#endif 