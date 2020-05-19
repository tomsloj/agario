#ifndef BOARD_H
#define BOARD_H

#include "Cell.hpp"
#include "Unit.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
    private:
        sf::Vector2u size;
        std::vector<Cell*> cells;
        std::vector<Unit*> feedUnits;
    public:
        Board();
        Board( sf::Vector2u size);
        void update( sf::Time time );
        void addCell( Cell *cell);
        void addFeedUnit( Unit *unit );
        void deleteCell( Cell *cell );
        void deleteFeedUnit( Unit *unit );
        std::vector<Cell*>& getCells();
        std::vector<Unit*>& getFeedUnits();
        sf::Vector2u getSize();

        void draw( sf::RenderWindow& window );
};

#endif 