#include "../include/ManualPlayer.hpp"

#include <iostream>

using namespace sf;

ManualPlayer::ManualPlayer(double x, double y) : Player(x, y)
{
    setColor(Color::Red);
}

void ManualPlayer::setMousePosition(Vector2i position)
{
    for(auto cell: playerCells)
    {
        Vector2f cellPos = cell->getPosition();
        double x = static_cast<double>(position.x) - cellPos.x;
        double y = static_cast<double>(position.y) - cellPos.y;

        double length = sqrt(x*x + y*y);
        x /= length;
        y /= length;

        cell->setDirecction(x, y);
        cell->update();
    }
}
