#include "../include/Menu.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Menu::Menu()
{
    std::cout<<"MENU\n";
}

Menu::Menu(RenderWindow &window)
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
