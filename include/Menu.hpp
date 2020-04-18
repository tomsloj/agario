#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
    private:
        int chosenOption;
    public:
        Menu();
        //Menu( int &window);
        void run( sf::RenderWindow &window );
};

#endif 