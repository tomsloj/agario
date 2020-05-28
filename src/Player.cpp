#include "../include/Player.hpp"

#include <iostream>

using namespace sf;

Player::Player()
{
    //playerCells.push_back(Cell());
}

//create new player - one cell
Player::Player(double x, double y)
{
    playerCells.push_back(new Cell(x, y, 500));
}

Player::Player( Cell* cell)
{
    playerCells.push_back( cell );
}

Player::~Player()
{
    playerCells.clear();
}

void Player::setColor( Color color )
{
    for(auto cell: playerCells)
        cell->Unit::setColor(color);
}

void Player::draw( RenderWindow& window) 
{
    for(auto cell: playerCells)
        cell->Unit::draw(window);
}

