#include "../include/Board.hpp"
#include "../include/Cell.hpp"
#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Board::Board()
{
}

Board::Board(Vector2u size)
{
    this->size = size;
}
Board::~Board()
{
    
    for( auto p : cells )
    {
        if( p != nullptr )
        {
            delete p;
            p = NULL;
        }
    }
    cells.clear();
    
    for( auto p : feedUnits )
    {
        if( p != nullptr )
        {
            delete p;
            p = NULL;
        }
    }
    feedUnits.clear();
    
}

void Board::update( Time time, Player *player )
{
    std::vector<Cell*> cellsToDelete;

    //sprawdzamy czy ktoras z komorek moze zjesc jakas kulke jedzenia
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
                            if(bot->botCells[0] == (*cell2))
                            {
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
                            if(bot->botCells[0] == (*cell))
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
        bot->setNextPosition(getFeedUnits(), getCells());
    }
}

void Board::addCell(Cell *cell)
{
    cells.push_back(cell);
}

void Board::addBot( Bot *bot)
{
    bots.push_back(bot);
}

void Board::addFeedUnit(Unit *unit)
{
    feedUnits.push_back(unit);
}

void Board::deleteCell(Cell *cell)
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

void Board::deleteFeedUnit(Unit *unit)
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
void Board::deleteBot(Bot* bot)
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

vector<Cell*>& Board::getCells()
{
    return cells;
}

vector<Unit*>& Board::getFeedUnits()
{
    return feedUnits;
}

Vector2u Board::getSize() const
{
    return size;
}

void Board::setSize( Vector2u size )
{
    this->size = size;
}

void Board::draw( RenderWindow& window )
{
    //rysujemy komorki
    for( size_t i = 0; i < cells.size(); ++i )
    {
        cells[i]->draw(window);
        //std::cout << cells[i]->getPosition().x << " " << cells[i]->getPosition().y << "\n";
    }

    //rysujemy kulki jedzenia
    for( size_t i = 0; i < feedUnits.size(); ++i )
    {
        feedUnits[i]->draw(window);
    }
}

std::ostream& operator<<(std::ostream& stream, const Board& board)
{
    stream << board.size.x << "\n";
    stream << board.size.y << "\n";
    stream << board.cells.size() << "\n";
    for( unsigned int i = 0; i < board.cells.size(); ++i )
    {
        stream << board.cells[i]->isItPlayer() << "\n";
        stream << *board.cells[i] << "\n";
    }
    stream << board.feedUnits.size() << "\n";
    for( unsigned int i = 0; i < board.feedUnits.size(); ++i )
    {
        stream << *board.feedUnits[i] << "\n";
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, Board& board)
{
    stream >> board.size.x;

    stream >> board.size.y;

    unsigned int cellsSize;
    stream >> cellsSize;
    for( unsigned int i = 0; i < cellsSize; ++i )
    {
        bool isPlayer;
        stream >> isPlayer;
        Cell* cell = new Cell();
        //board.cells.push_back(new Cell());
        stream >> *cell;
        if( isPlayer )
        {
            board.addCell(cell);
            cell->setAsPlayer();
        }
        else
        {
            Bot* bot = new Bot(cell->getPosition().x, cell->getPosition().y);
            board.addCell(bot->botCells[0]);
            board.addBot(bot);
        }
    }

    unsigned int feedUnitsSize;
    stream >> feedUnitsSize;
    for( unsigned int i = 0; i < feedUnitsSize; ++i )
    {
        board.feedUnits.push_back(new Unit());
        stream >> *board.feedUnits[i];
    }

    return stream;
}