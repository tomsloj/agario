#ifndef BOARD_H
#define BOARD_H

#include "Cell.hpp"
#include "Unit.hpp"
#include "Bot.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
    private:
        sf::Vector2u size;
    protected:
        
    public:
        
        Board();
        Board( sf::Vector2u size);
        ~Board();
        sf::Vector2u getSize() const;
        void setSize( sf::Vector2u size );

        void draw( sf::RenderWindow& window, std::vector<Cell*> cells, std::vector<Unit*> feedUnits );
};

#endif 