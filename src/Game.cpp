#include "../include/Game.hpp"
#include "../include/Unit.hpp"
#include "../include/GlobalValues.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int MAX_NUMBER_OF_PLAYERS = 60;
const int MAX_NUMBER_OF_FEED_UNITS = 900;

Game::Game()
{
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
        board->addCell(player->cells[0]);
    }
    else
    {
        player = NULL;
        for( auto cell : board->getCells() )
        {
            cell->setAcceleration(0);
            if( cell->isItPlayer() )
            {
                if( !player )
                {
                    player = new ManualPlayer( cell );
                }
                else
                {
                    player->addCell(cell);
                }  
            }
        }
        remove("bin/save");
    }
    
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
                    case Keyboard::Space:
                        for(auto cell : player->Divide(sf::Mouse::getPosition(window)))
                            board->addCell(cell);
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

        double maxRadius = 0;
        for( auto cell: player->cells )
        {
            maxRadius = max( maxRadius, cell->getRadius());
        }

        if( player->cells.size() == 0 || maxRadius >= min(gameWindowHeight, gameWindowWidth) / 3 || maxRadius == 0 )
        {
            gameOver(window);
            break;
        }
        
    }
    
    
}

Game::~Game()
{
    players.clear();
    feedCells.clear();
    bots.clear();
    for (auto p : tmp)
    {
        if( p != NULL )
        delete p;
    } 
    tmp.clear();
    if( board != NULL )
        delete board;
    if( player != NULL )
        delete player;
}

void Game::createPlayer()
{
    //players.push_back(Player());
}

Vector2f Game::findPlace()
{
    return Vector2f( fRand(0.0, board->getSize().x), fRand(0.0, board->getSize().y));
}

void Game::step( RenderWindow &window )
{
    while( board->getFeedUnits().size() < MAX_NUMBER_OF_FEED_UNITS )
        board->addFeedUnit(new Unit(findPlace(), 1));

    while( board->getCells().size() < MAX_NUMBER_OF_PLAYERS )
    {
        bot = new Bot(findPlace().x, findPlace().y);
        board->addCell(bot->botCells[0]);
        board->addBot(bot);
    }


    sf::Vector2i position = sf::Mouse::getPosition(window);
    player->setMousePosition(position);
    Time time = clock.getElapsedTime();
    clock.restart();
    board->update(time, player);
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

void Game::gameOver(RenderWindow &window)
{
    window.clear(sf::Color::Black);
}