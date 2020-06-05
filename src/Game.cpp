#include "../include/Game.hpp"

using namespace sf;
using namespace std;

const int MAX_NUMBER_OF_PLAYERS = 60;
const int MAX_NUMBER_OF_FEED_UNITS = 1000;

Game::Game()
{
}

Game::Game(RenderWindow &window)
{
    srand( time( NULL ) );
    window.setFramerateLimit(FPSNumber);
    Vector2u size = window.getSize();
    board = new Board(size);

    //try to load game
    if ( !load() )
    {
        player = new ManualPlayer(size.x/2, size.y/2);
        cells.push_back(player->cells[0]);
    }
    else
    {
        //connect players cells with manual player
        player = NULL;
        for( auto cell : cells )
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
                    //go to menu
                    case Keyboard::M:
                        save();
                        window.clear();
                        return;
                        break;
                    case Keyboard::Space:
                        for(auto cell : player->divide(sf::Mouse::getPosition(window)))
                            cells.push_back(cell);
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

        //check if game is over
        double maxRadius = 0;
        for( auto cell: cells )
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
    for (auto p : tmp)
    {
        if( p != NULL )
        {
            delete p;
            p = NULL;
        }
    } 
    tmp.clear();
    for(auto fu : feedUnits)
    {
        if( fu != NULL)
        {
            delete fu;
            fu = NULL;
        }
    }
    feedUnits.clear();

    for(auto b : bots)
    {
        if( b != NULL)
        {
            delete b;
            b = NULL;
        }
    }
    feedUnits.clear();

    for(auto c : cells)
    {
        if( c != NULL)
        {
            delete c;
            c = NULL;
        }
    }
    feedUnits.clear();

    if( board != NULL )
    {
        delete board;
        board = NULL;
    }
    if( player != NULL )
    {
        delete player;
        player = NULL;
    }
}

//find place to insert any unit
Vector2f Game::findPlace()
{
    return Vector2f( fRand(0.0, board->getSize().x), fRand(0.0, board->getSize().y));
}

//next step of game
void Game::step( RenderWindow &window )
{
    while( feedUnits.size() < MAX_NUMBER_OF_FEED_UNITS )
    {
        Unit* u = new Unit(findPlace(), 1);
        feedUnits.push_back(u);
    }

    while( bots.size() + 1 < MAX_NUMBER_OF_PLAYERS )
    {
        bot = new Bot(findPlace().x, findPlace().y);
        bots.push_back(bot);
        cells.push_back(bot->getBotCells()[0]);
    }


    sf::Vector2i position = sf::Mouse::getPosition(window);
    player->setMousePosition(position);
    Time time = clock.getElapsedTime();
    clock.restart();
    update(time);
    board->draw(window, cells, feedUnits);
}

void Game::update( Time time )
{
    std::vector<Cell*> cellsToDelete;

    //check if cell can eat sth
    for( vector<Cell*>::iterator cell = cells.begin(); cell != cells.end(); ++cell )
    {

        for( vector<Unit*>::iterator unit = feedUnits.begin(); unit != feedUnits.end(); ++unit )
        {
            if( (*cell)->distance(*(*unit)) <= (*cell)->getRadius() )
            {
                (*cell)->grow((*unit)->getMass());
                delete (*unit);
                *unit = NULL;
                feedUnits.erase(unit); 
                --unit;
            }
        }
        
        for( vector<Cell*>::iterator cell2 = cell + 1; cell2 != cells.end(); ++cell2 )
        {
            if( (*cell)->distance(*(*cell2)) <= (*cell)->getRadius() )
            {
                if((*cell)->getMass() > (*cell2)->getMass())
                {
                    if((*cell2)->isItPlayer())
                    {
                        player->removeCell((*cell2));
                    }
                    else
                    {
                        for(auto bot : bots)
                        {
                            if(bot->getBotCells()[0] == (*cell2))
                            {
                                //board->deleteBot(bot);
                                deleteBot(bot);
                                delete bot;
                                bot = NULL;
                            } 
                        }
                    }
                    
                    (*cell)->grow((*cell2)->getMass() / 2); 
                    cellsToDelete.push_back(*cell2);
                    cells.erase(cell2);
                    --cell2;
                }
            }
            else if( (*cell2)->distance(*(*cell)) <= (*cell2)->getRadius() )
            {
                if((*cell)->getMass() < (*cell2)->getMass())
                {
                    if((*cell)->isItPlayer())
                    {
                        player->removeCell((*cell));
                    }
                    else
                    {
                        for(auto bot : bots)
                        {
                            if(bot->getBotCells()[0] == (*cell))
                            {
                                deleteBot(bot);
                                delete bot;
                                bot = NULL;
                            } 
                        }
                    }

                    (*cell2)->grow((*cell)->getMass() / 2); 
                    cellsToDelete.push_back(*cell);
                }
            }
        }
    }

    for( auto cell : cellsToDelete )
    {
        deleteCell(cell);
    }    
            
    for( auto bot : bots)
    {
        bot->setNextPosition(feedUnits, cells);
    }
}

//rand a number form the range fMin, fMax
double Game::fRand( double fMin, double fMax )
{
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

//save game to bin/save
void Game::save()
{
    ofstream myfile;
    myfile.open ("bin/save");
    myfile << *this;
    myfile.close();
}

//load game to bin/save
bool Game::load()
{
    ifstream myfile;
    myfile.open("bin/save");
    if( !myfile )
        return false;
    myfile >> *this;
    myfile.close();
    return true;
}

void Game::gameOver(RenderWindow &window)
{
    window.clear(sf::Color::Black);
}

void Game::addCell( Cell *cell )
{
    cells.push_back( cell );
}
void Game::addBot( Bot *bot )
{
    bots.push_back( bot );
}        

void Game::deleteCell(Cell *cell)
{
    for( vector<Cell*>::iterator it = cells.begin(); it != cells.end(); ++it )
    {
        if( *it == cell )
        {
            cells.erase(it);
            if( cell != NULL )
                delete cell;
            cell = NULL;
            break;
        }
    }
}

void Game::deleteFeedUnit(Unit *unit)
{
    for( vector<Unit*>::iterator it = feedUnits.begin(); it != feedUnits.end(); ++it )
    {
        if(*it == unit)
        {
            feedUnits.erase(it);
            break;
        }
    }
}
void Game::deleteBot(Bot* bot)
{
    for( vector<Bot*>::iterator it = bots.begin(); it != bots.end(); ++it )
    {
        if(*it == bot)
        {
            bots.erase(it);
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const Game& game)
{
    stream << game.cells.size() << "\n";
    for( unsigned int i = 0; i < game.cells.size(); ++i )
    {
        stream << game.cells[i]->isItPlayer() << "\n";
        stream << *game.cells[i] << "\n";
    }
    stream << game.feedUnits.size() << "\n";
    for( unsigned int i = 0; i < game.feedUnits.size(); ++i )
    {
        stream << *game.feedUnits[i] << "\n";
    }
    return stream;
    
}

std::istream& operator>>(std::istream& stream, Game& game)
{
    unsigned int cellsSize;
    stream >> cellsSize;
    for( unsigned int i = 0; i < cellsSize; ++i )
    {
        bool isPlayer;
        stream >> isPlayer;
        Cell* cell = new Cell();
        stream >> *cell;
        if( isPlayer )
        {
            cell->setAsPlayer();
            game.addCell(cell);
        }
        else
        {
            Bot* bot = new Bot(cell->getPosition().x, cell->getPosition().y);
            bot->getBotCells()[0]->setMass(cell->getMass());
            game.addCell(bot->getBotCells()[0]);
            game.addBot(bot);
        }
    }

    unsigned int feedUnitsSize;
    stream >> feedUnitsSize;
    for( unsigned int i = 0; i < feedUnitsSize; ++i )
    {
        game.feedUnits.push_back(new Unit());
        stream >> *game.feedUnits[i];
    }

    return stream;
    
}