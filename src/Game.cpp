#include "../include/Game.hpp"
#include "../include/Unit.hpp"
#include "../include/GlobalValues.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int MAX_NUMBER_OF_PLAYERS = 70;
const int MAX_NUMBER_OF_FEED_UNITS = 1500;

Game::Game()
{
    std::cout<<"Game\n";
}

Game::Game(RenderWindow &window)
{
    srand( time( NULL ) );
    Vector2u size = window.getSize();
    window.setFramerateLimit(FPSNumber);
    //std::cout << window.getSize().x << " " << window.getSize().y << "\n";
    board = new Board(size);
    std::cout<<"Game Window\n";
    window.clear();
    window.display();
    

    clock.restart();
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
        window.clear();
        sleep(sf::milliseconds(2));
        step(window);
        window.display();
    }
    
}

void Game::createPlayer()
{
    //players.push_back(Player());
}

Vector2f Game::findEmptyPlace(double radius)
{
    //TODO sprawdzenie czy nie trafilismy w zajete miejsce
    Vector2f place = findPlace();

    return place;
}

Vector2f Game::findPlace()
{
    return Vector2f( fRand(0.0, board->getSize().x), fRand(0.0, board->getSize().y));
}

void Game::step( RenderWindow &window )
{
    while( board->getFeedUnits().size() < MAX_NUMBER_OF_FEED_UNITS )
        board->addFeedUnit(new Unit(findPlace(), 1));

    //TODO sprawdzenie i uzupelnienei liczby graczy
    
    Time time = clock.getElapsedTime();
    clock.restart();
    board->update(time);
    board->draw(window);
    
}

double Game::fRand( double fMin, double fMax )
{
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}