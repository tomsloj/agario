#include "../include/Player.hpp"

#include <iostream>

using namespace sf;

Player::Player()
{
    //playerCells.push_back(Cell());
}

//create new player - one cell
Player::Player(double x, double y, double acc, int mass)
{
    cells.push_back(new Cell(x, y, acc , true, mass) );
}

Player::Player( Cell* cell)
{
    cells.push_back( cell );
}

Player::~Player()
{
    cells.clear();
}

void Player::setColor( Color color )
{
    for(auto cell: cells)
        cell->Unit::setColor(color);
}

void Player::draw( RenderWindow& window) 
{
    for(auto cell: cells)
        cell->Unit::draw(window);
}

void Player::removeCell(Cell* cell)
{
    for( std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); ++it )
    {
        if( *it == cell )
        {
            cells.erase(it);
            break;
        }
    }
}

