#ifndef GAME_H
#define GAME_H

#include "ManualPlayer.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Unit.hpp"
#include "GlobalValues.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>


class Game
{
    private:
        ManualPlayer *player;
        std::vector<Player>players;
        Bot *bot;
        std::vector<Bot*>bots;
        std::vector<Unit*>feedUnits;
        std::vector<Cell*> tmp;
        std::vector<Cell*> cells;
        Board* board;
        sf::Clock clock;
    public:
        Game();
        Game( sf::RenderWindow &window );
        ~Game();
        sf::Vector2f findPlace();
        double fRand( double fMin, double fMax );
        void step( sf::RenderWindow &window );
        void update( sf::Time time );
        void save();
        bool load();

        void gameOver(sf::RenderWindow &window);

        void addCell( Cell *cell );
        void addBot( Bot *bot );

        void deleteCell( Cell *cell );
        void deleteBot( Bot* bot );
        void deleteFeedUnit( Unit *unit );

        friend std::ostream& operator<<(std::ostream& stream, const Game& game);
        friend std::istream& operator>>(std::istream& stream, Game& game);
};

#endif 