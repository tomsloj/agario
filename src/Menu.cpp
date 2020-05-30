#include "../include/Menu.hpp"

#include "../include/Game.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

Menu::Menu()
{
    chosenOption = 0;
    std::cout<<"MENU\n";
}

/*
Menu::Menu(int &window)
{
    int w = window;
    
}
*/
void Menu::run( RenderWindow &window ) 
{
    std::cout<<"RUN\n";
    Event event;
    Font font;

    if (!font.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Error loading arial.ttf" << std::endl;
	}

    menuTextPlay.setFont(font);
    menuTextPlay.setCharacterSize(20);
    menuTextPlay.setString("Play");
    menuTextPlay.setPosition({static_cast<float>(gameWindowWidth * 5 / 11), static_cast<float>(gameWindowHeight * 4 / 12)});

    menuTextLoad.setFont(font);
    menuTextLoad.setCharacterSize(20);
    menuTextLoad.setString("Load game");
    menuTextLoad.setPosition({static_cast<float>(gameWindowWidth * 5 / 11), static_cast<float>(gameWindowHeight * 5 / 12)});

    menuTextSettings.setFont(font);
    menuTextSettings.setCharacterSize(20);
    menuTextSettings.setString("Settings");
    menuTextSettings.setPosition({static_cast<float>(gameWindowWidth * 5 / 11), static_cast<float>(gameWindowHeight * 6 / 12)});

    menuTextScores.setFont(font);
    menuTextScores.setCharacterSize(20);
    menuTextScores.setString("High scores");
    menuTextScores.setPosition({static_cast<float>(gameWindowWidth * 5 / 11), static_cast<float>(gameWindowHeight * 7 / 12)});
    

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            //nacisnieto przycisk
            else
            if(event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case Keyboard::Down:
                        chosenOption = (chosenOption + 1) % 4;
                        break;
                    case Keyboard::Up:
                        chosenOption = (((chosenOption - 1) % 4) + 4) % 4;
                        break;
                    case Keyboard::Return:
                        
                        chooseOption( window );
                    default:
                        break;
                    
                }
            }
            else
            if( event.type ==Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left )
            {
                Vector2i position = Mouse::getPosition(window);

                if( position.x > gameWindowWidth * 9 / 20 && position.x < gameWindowWidth * 2 / 3)
                {
                    if( position.y > gameWindowHeight / 3 && position.y < gameWindowHeight * 23 / 60 )
                    {
                        chosenOption = 0;
                        chooseOption( window );
                    }
                    else
                    if( position.y > gameWindowHeight * 5 / 12 && position.y < gameWindowHeight * 7 / 15 )
                    {
                        chosenOption = 1;
                        chooseOption( window );
                    }
                    else
                    if( position.y > gameWindowHeight / 2 && position.y < gameWindowHeight * 11 / 20 )
                    {
                        chosenOption = 2;
                        chooseOption( window );
                    }
                    else
                    if( position.y > gameWindowHeight * 7 / 12 && position.y < gameWindowHeight * 19 / 30 )
                    {
                        chosenOption = 3;
                        chooseOption( window );
                    }
                    
                }
            }
            

        }
        switch (chosenOption)
        {
        case 0:
            menuTextPlay.setFillColor(checked);
            menuTextLoad.setFillColor(unchecked);
            menuTextSettings.setFillColor(unchecked);
            menuTextScores.setFillColor(unchecked);
            break;
        case 1:
            menuTextPlay.setFillColor(unchecked);
            menuTextLoad.setFillColor(checked);
            menuTextSettings.setFillColor(unchecked);
            menuTextScores.setFillColor(unchecked);
            break;
        case 2:
            menuTextPlay.setFillColor(unchecked);
            menuTextLoad.setFillColor(unchecked);
            menuTextSettings.setFillColor(checked);
            menuTextScores.setFillColor(unchecked);
            break;
        case 3:
            menuTextPlay.setFillColor(unchecked);
            menuTextLoad.setFillColor(unchecked);
            menuTextSettings.setFillColor(unchecked);
            menuTextScores.setFillColor(checked);
            break;
        default:
            break;
        }

        window.draw(menuTextPlay);
        window.draw(menuTextLoad);
        window.draw(menuTextSettings);
        window.draw(menuTextScores);
        window.display();
        
    }
    
}

void Menu::chooseOption( RenderWindow &window )
{
    switch (chosenOption)
    {
        //graj
        case 0:
        {
            std::cout << "graj" << "\n";
            remove("bin/save");
            Game game(window);
            
            break;
        }
        case 1:
        {
            Game game(window);
        }
            break;
        default:
            break;
    }
}
