#include "../include/Settings.hpp"

using namespace sf;

Settings::Settings()
{
    chosenOption = level - 1;
}

void Settings::run( ) 
{
    Event event;
    Font font;
    Text settingsTextEasy;
    Text settingsTextMedium;
    Text settingsTextHard;

    RenderWindow window(VideoMode(settingsWindowWidth, settingsWindowHeight),"Settings");

    if (!font.loadFromFile("assets/arial.ttf"))
	{
		std::cerr << "Error loading arial.ttf" << std::endl;
	}

    settingsTextEasy.setFont(font);
    settingsTextEasy.setCharacterSize(20);
    settingsTextEasy.setString("Easy");
    settingsTextEasy.setPosition({static_cast<float>(settingsWindowWidth * 5 / 12), static_cast<float>(settingsWindowHeight * 3 / 12)});

    settingsTextMedium.setFont(font);
    settingsTextMedium.setCharacterSize(20);
    settingsTextMedium.setString("Medium");
    settingsTextMedium.setPosition({static_cast<float>(settingsWindowWidth * 5 / 12), static_cast<float>(settingsWindowHeight * 5 / 12)});

    settingsTextHard.setFont(font);
    settingsTextHard.setCharacterSize(20);
    settingsTextHard.setString("Hard");
    settingsTextHard.setPosition({static_cast<float>(settingsWindowWidth * 5 / 12), static_cast<float>(settingsWindowHeight * 7 / 12)});


    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
            //nkey pressed
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
                        chooseOption();
                        return;
                    default:
                        break;
                    
                }
            }
            else
            if( event.type ==Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left )
            {
                Vector2i position = Mouse::getPosition(window);
                
                if( position.x > settingsWindowWidth * 2 / 5 && position.x < settingsWindowWidth * 7 / 10)
                {
                    if( position.y > settingsWindowHeight * 4 / 15 && position.y < settingsWindowHeight / 3 )
                    {
                        chosenOption = 0;
                        chooseOption();
                        return;
                    }
                    else
                    if( position.y > settingsWindowHeight * 32 / 75 && position.y < settingsWindowHeight / 2 )
                    {
                        chosenOption = 1;
                        chooseOption();
                        return;
                    }
                    else
                    if( position.y > settingsWindowHeight * 3 / 5 && position.y < settingsWindowHeight * 2 / 3 )
                    {
                        chosenOption = 2;
                        chooseOption();
                        return;
                    }
                    
                }
            }
        }
        switch (chosenOption)
        {
        case 0:
            settingsTextEasy.setFillColor(checked);
            settingsTextMedium.setFillColor(unchecked);
            settingsTextHard.setFillColor(unchecked);
            break;
        case 1:
            settingsTextEasy.setFillColor(unchecked);
            settingsTextMedium.setFillColor(checked);
            settingsTextHard.setFillColor(unchecked);
            break;
        case 2:
            settingsTextEasy.setFillColor(unchecked);
            settingsTextMedium.setFillColor(unchecked);
            settingsTextHard.setFillColor(checked);
            break;
        default:
            break;
        }

        window.clear(sf::Color(10, 10, 10));
        window.draw(settingsTextEasy);
        window.draw(settingsTextMedium);
        window.draw(settingsTextHard);
        window.display();
        
    }
    
}

//set level when user confirm choice
void Settings::chooseOption()
{
    level = chosenOption + 1;
}