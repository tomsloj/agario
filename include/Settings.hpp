#ifndef SETTINGS_H
#define SETTINGS_H

#include "GlobalValues.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class Settings
{
    private:
        const int settingsWindowWidth = 300;
        const int settingsWindowHeight = 300;

        int chosenOption;

        const sf::Color checked = sf::Color::Red;
        const sf::Color unchecked = sf::Color::White;

        

    public:
        Settings();

        void run( );
        void chooseOption( );
};

#endif 