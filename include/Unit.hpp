#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>

class Unit
{
    private:
        int size;
        sf::Vector2f position;
        sf::CircleShape *sprite;
        sf::Color color;
    public:
        Unit();
        Unit( double X, double Y, int size = 1 );
        Unit( sf::Vector2f position, int size = 1 );
        void grow(const int sizeOfGrowth);
        void increaseSize( int sizeReduction = 1 );
        int getSize();
        void draw(sf::RenderWindow& window);
        void setColor(sf::Color);
};

#endif 