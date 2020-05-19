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

    if (!font.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Error loading arial.ttf" << std::endl;
	}

    menuText1.setFont(font);
    menuText1.setCharacterSize(20);
    menuText1.setString("Graj");
    menuText1.setPosition({280.f, 160.f});

    menuText2.setFont(font);
    menuText2.setCharacterSize(20);
    menuText2.setString("Ustawienia");
    menuText2.setPosition({280.f, 210.f});

    menuText3.setFont(font);
    menuText3.setCharacterSize(20);
    menuText3.setString("Najlepsze wyniki");
    menuText3.setPosition({280.f, 260.f});
    

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
                        chosenOption = (chosenOption + 1) % 3;
                        break;
                    case Keyboard::Up:
                        chosenOption = (((chosenOption - 1) % 3) + 3) % 3;
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
            break;
        case 1:
            menuText1.setFillColor(unchecked);
            menuText2.setFillColor(checked);
            menuText3.setFillColor(unchecked);
            break;
        case 2:
            menuText1.setFillColor(unchecked);
            menuText2.setFillColor(unchecked);
            menuText3.setFillColor(checked);
            break;
        default:
            break;
        }

        window.draw(menuText1);
        window.draw(menuText2);
        window.draw(menuText3);
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
        Game game(window);
        
        break;
    }
    case 1:
        break;
    default:
        break;
    }
}
