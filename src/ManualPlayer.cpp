#include "../include/ManualPlayer.hpp"

#include <iostream>

using namespace sf;

ManualPlayer::ManualPlayer(double x, double y) : Player(x, y, 0, basicPlayerMass)
{
    setColor(Color::Red);
}

ManualPlayer::ManualPlayer( Cell* cell ) : Player( cell )
{
    setColor(Color::Red);
}

//przesyla informacje o pozycji myszki i aktualizuje pozycje gracza
void ManualPlayer::setMousePosition(Vector2i position)
{
    for(auto cell: cells)
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

std::vector<Cell*> ManualPlayer::Divide(Vector2i mousePosition)
{
    std::vector<Cell *> newcells;

	for (std::vector<Cell *>::iterator it = cells.begin(); it != cells.end(); ++it)
	{
		if ((*it)->getMass() > 50)
		{
			newcells.push_back((*it)->Division(mousePosition));
		}
	}

	for(auto cell : newcells)
    {
        cell->setAsPlayer();
		cells.push_back(cell);
    }

	return newcells;
}
