#include "../include/Player.hpp"

#include <iostream>

Player::Player()
{
    playerCells.push_back(Cell());
}

Player::~Player()
{
    playerCells.clear();
}