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
        std::vector<Cell*> cells;
        std::vector<Bot*> bots;
        std::vector<Unit*> feedUnits;
    protected:
        
    public:
        
        Board();
        Board( sf::Vector2u size);
        void update( sf::Time time , Player *player);
        void addCell( Cell *cell);
        void addBot( Bot *bot);
        void addFeedUnit( Unit *unit );
        void deleteCell( Cell *cell );
        void deleteBot(Bot* bot);
        void deleteFeedUnit( Unit *unit );
        std::vector<Cell*>& getCells();
        std::vector<Unit*>& getFeedUnits();
        sf::Vector2u getSize() const;
        void setSize( sf::Vector2u size );

        void draw( sf::RenderWindow& window );

        friend std::ostream& operator<<(std::ostream& stream, const Board& board);
        friend std::istream& operator>>(std::istream& stream, Board& board);
};

#endif 