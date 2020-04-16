#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.hpp>

using namespace sf;

int main()
{
    std::cout<<"Hello\n";
    RenderWindow window(VideoMode(453,453),"Tytul.");
    
    Menu menu = Menu(window);
    

    return 0;
}