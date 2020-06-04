#include "../include/Board.hpp"

using namespace std;
using namespace sf;

Board::Board()
{
}

Board::Board(Vector2u size)
{
    this->size = size;
}
Board::~Board()
{
}

Vector2u Board::getSize() const
{
    return size;
}

void Board::setSize( Vector2u size )
{
    this->size = size;
}

//draw all cells and units on window
void Board::draw( sf::RenderWindow& window, std::vector<Cell*> cells, std::vector<Unit*> feedUnits )
{
    if( window.getSize() != size )
        window.setSize(size);
    //draw cells
    for( size_t i = 0; i < cells.size(); ++i )
    {
        cells[i]->draw(window);
    }

    //draw feed units
    for( size_t i = 0; i < feedUnits.size(); ++i )
    {
        feedUnits[i]->draw(window);
    }

}