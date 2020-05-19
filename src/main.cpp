#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.hpp>
#include "GlobalValues.hpp"

using namespace sf;

int main()
{
    std::cout<<FPSNumber<< "\n";
    std::cout<<"Hello\n";
    RenderWindow window(VideoMode(gameWindowWidth, gameWindowHeight),"Tytul.");
    
    //int a = 300;
    Menu menu;
    //menu.addWindow(window);
    menu.run(window);
    

    return 0;
}