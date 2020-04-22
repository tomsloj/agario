#include "../include/Game.hpp"
#include "../include/Unit.hpp"

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
    window.clear();
    window.display();
    double x = 0.0;
    double y = 0.0;
    Unit u(x, y, 20);
    u.setColor(Color::Red);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
        sleep(sf::milliseconds(2));
        step(window);
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

void Game::step( RenderWindow &window )
{

}