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
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
        }
        
    }
    
}
