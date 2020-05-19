#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"
#include "Board.hpp"

class Game
{
    private:
        std::vector<Player>players;
        std::vector<Cell>feedCells;
        Board* board;
        sf::Clock clock;
    public:
        Game();
        Game( sf::RenderWindow &window );
        ~Game();
        void createPlayer();
        sf::Vector2f findEmptyPlace(double radius);
        sf::Vector2f findPlace();
        double fRand( double fMin, double fMax );
        void step( sf::RenderWindow &window );
};

#endif 