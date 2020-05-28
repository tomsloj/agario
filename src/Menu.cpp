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
    Text menuText1;
    Text menuText2;
    Text menuText3;
    Text menuText4;

    if (!font.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Error loading arial.ttf" << std::endl;
	}

    menuText1.setFont(font);
    menuText1.setCharacterSize(20);
    menuText1.setString("Play");
    menuText1.setPosition({280.f, 160.f});

    menuText2.setFont(font);
    menuText2.setCharacterSize(20);
    menuText2.setString("Load game");
    menuText2.setPosition({280.f, 210.f});

    menuText3.setFont(font);
    menuText3.setCharacterSize(20);
    menuText3.setString("Settings");
    menuText3.setPosition({280.f, 260.f});

    menuText4.setFont(font);
    menuText4.setCharacterSize(20);
    menuText4.setString("High scores");
    menuText4.setPosition({280.f, 310.f});
    

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            //nacisnieto przycisk
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
        }
        switch (chosenOption)
        {
        case 0:
            menuText1.setFillColor(checked);
            menuText2.setFillColor(unchecked);
            menuText3.setFillColor(unchecked);
            menuText4.setFillColor(unchecked);
            break;
        case 1:
            menuText1.setFillColor(unchecked);
            menuText2.setFillColor(checked);
            menuText3.setFillColor(unchecked);
            menuText4.setFillColor(unchecked);
            break;
        case 2:
            menuText1.setFillColor(unchecked);
            menuText2.setFillColor(unchecked);
            menuText3.setFillColor(checked);
            menuText4.setFillColor(unchecked);
            break;
        case 3:
            menuText1.setFillColor(unchecked);
            menuText2.setFillColor(unchecked);
            menuText3.setFillColor(unchecked);
            menuText4.setFillColor(checked);
            break;
        default:
            break;
        }

        window.draw(menuText1);
        window.draw(menuText2);
        window.draw(menuText3);
        window.draw(menuText4);
        window.display();
        
    }
    
}

void Menu::chooseOption( RenderWindow &window )
{
    std::cout << chosenOption << "\n";
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
