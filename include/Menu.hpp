#ifndef MENU_H
#define MENU_H

#include "Game.hpp"
#include "Settings.hpp"

#include <SFML/Graphics.hpp>

class Menu
{
    private:
        int chosenOption;

        const sf::Color checked = sf::Color::Red;
        const sf::Color unchecked = sf::Color::White;

        Settings settings;
        Game game; 
    public:
        Menu();
        //Menu( int &window);
        void run( sf::RenderWindow &window );
        void chooseOption( sf::RenderWindow &window );
};

#endif 