#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.hpp>
#include "GlobalValues.hpp"

using namespace sf;

int main()
{
    std::cout<<FPSNumber<< "\n";
    std::cout<<"Hello\n";
    RenderWindow window(VideoMode(453,453),"Tytul.");
    
    Menu menu = Menu(window);
    

    return 0;
}