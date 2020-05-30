#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
    private:
        int chosenOption;

        const sf::Color checked = sf::Color::Red;
        const sf::Color unchecked = sf::Color::White;

        Text menuTextPlay;
        Text menuTextLoad;
        Text menuTextSettings;
        Text menuTextScores;
    public:
        Menu();
        //Menu( int &window);
        void run( sf::RenderWindow &window );
        void chooseOption( sf::RenderWindow &window );
};

#endif 