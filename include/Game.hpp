#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"

class Game
{
    private:
        std::vector<Player>players;
        std::vector<Cell>feedCells;
    public:
        Game();
        Game( sf::RenderWindow &window);
        void createPlayer();
        sf::Vector2f findEmptyPlace(double radius);
        sf::Vector2f findPlace();
};

#endif 