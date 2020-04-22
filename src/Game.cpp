#include "../include/Game.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Game::Game()
{
    std::cout<<"Game\n";
}

Game::Game(RenderWindow &window)
{
    std::cout<<"Game Window\n";
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    
}

void Game::createPlayer()
{
    //players.push_back(Player());
}

Vector2f Game::findEmptyPlace(double radius)
{

}

Vector2f Game::findPlace()
{
    
}
