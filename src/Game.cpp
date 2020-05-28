#include "../include/Game.hpp"
#include "../include/Unit.hpp"
#include "../include/GlobalValues.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int MAX_NUMBER_OF_PLAYERS = 70;
const int MAX_NUMBER_OF_FEED_UNITS = 1000;

Game::Game()
{
    std::cout<<"Game\n";
}

Game::Game(RenderWindow &window)
{
    srand( time( NULL ) );
    //window.setSize(Vector2u(gameWindowWidth, gameWindowHeight));
    window.setFramerateLimit(FPSNumber);
    Vector2u size = window.getSize();
    board = new Board(size);
    if ( !load() )
    {
        player = new ManualPlayer(size.x/2, size.y/2);
        board->addCell(player->playerCells[0]);
    }
    else
    {
        player = new ManualPlayer( board->getCells()[0] );
    }
    
        
    std::cout << window.getSize().x << " " << window.getSize().y << "\n";
    
    std::cout<<"Game Window\n";
    window.clear();
    window.display();

    clock.restart();
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if(e.type == Event::Closed)
            {
                save();
                window.close();
            }else
            if( e.type == Event::KeyPressed )
            {
                switch( e.key.code )
                {
                    case Keyboard::M:
                        save();
                        window.clear();
                        return;
                        break;
                    default:
                        break;
                }
            }
        }
        window.clear();
        sleep(sf::milliseconds(2));

        step(window);
        window.display();
    }
    
}

Game::~Game()
{
    players.clear();
    feedCells.clear();
    if( board != nullptr )
        delete board;
}

void Game::createPlayer()
{
    //players.push_back(Player());
}

Vector2f Game::findEmptyPlace(double radius)
{
    //TODO sprawdzenie czy nie trafilismy w zajete miejsce
    Vector2f place = findPlace();

    return place;
}

Vector2f Game::findPlace()
{
    return Vector2f( fRand(0.0, board->getSize().x), fRand(0.0, board->getSize().y));
}

void Game::step( RenderWindow &window )
{
    while( board->getFeedUnits().size() < MAX_NUMBER_OF_FEED_UNITS )
        board->addFeedUnit(new Unit(findPlace(), 1));

    //TODO sprawdzenie i uzupelnienie liczby graczy

    while( board->getCells().size() < MAX_NUMBER_OF_PLAYERS )
    {
        bot = new BotBehaviour(findPlace().x, findPlace().y);
        board->addCell(bot->botCells[0]);
        board->addBot(bot);
    }


    sf::Vector2i position = sf::Mouse::getPosition(window);
    player->setMousePosition(position);
    Time time = clock.getElapsedTime();
    clock.restart();
    board->update(time);
    board->draw(window);
}

double Game::fRand( double fMin, double fMax )
{
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Game::save()
{
    ofstream myfile;
    myfile.open ("bin/save");
    myfile << *board;
    myfile.close();
}

bool Game::load()
{
    ifstream myfile;
    myfile.open("bin/save");
    if( !myfile )
        return false;
    myfile >> *board;
    myfile.close();
    return true;
}