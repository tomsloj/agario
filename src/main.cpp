#include "GlobalValues.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(gameWindowWidth, gameWindowHeight),"Agario");
    
    Menu menu;
    menu.run(window);

    return 0;
}