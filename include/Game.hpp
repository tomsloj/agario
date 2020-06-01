#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

#include "ManualPlayer.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Board.hpp"


class Game
{
    private:
        ManualPlayer *player;
        std::vector<Player>players;
        Bot *bot;
        std::vector<Bot>bots;
        std::vector<Cell>feedCells;
        std::vector<Cell*> tmp;
        Board* board;
        sf::Clock clock;
    public:
        Game();
        Game( sf::RenderWindow &window );
        ~Game();
        void createPlayer();
        sf::Vector2f findPlace();
        double fRand( double fMin, double fMax );
        void step( sf::RenderWindow &window );
        void save();
        bool load();

        void gameOver(sf::RenderWindow &window);
};

#endif 