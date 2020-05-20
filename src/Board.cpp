#include "../include/Board.hpp"
#include "../include/Cell.hpp"
#include "../include/Unit.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Board::Board()
{
    std::cout<<"CELL\n";
}

Board::Board(Vector2u size)
{
    this->size = size;
}

void Board::update( Time time )
{
    //sprawdzamy czy ktoras z komorek moze znejsc jakas kulke jedzenia
    for( auto cell : cells )
    {
        for( vector<Unit*>::iterator unit = feedUnits.begin(); unit != feedUnits.end(); ++unit )
        {
            if( cell->distance(*(*unit)) <= cell->getRadius() )
            {
                Unit* u = *unit;
                cout << cell->getMass() << "\n"; 
                cell->grow(u->getMass());
                delete u;
                feedUnits.erase(unit);
                --unit;
            }
        }
    }
    //tu bedzie sporo do zakodowania
}

void Board::addCell(Cell *cell)
{
    cells.push_back(cell);
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

vector<Cell*>& Board::getCells()
{
    return cells;
}

vector<Unit*>& Board::getFeedUnits()
{
    return feedUnits;
}

Vector2u Board::getSize()
{
    return size;
}

void Board::draw( RenderWindow& window )
{
    //rysujemy komorki
    for( size_t i = 0; i < cells.size(); ++i )
    {
        cells[i]->draw(window);
    }

    //rysujemy kulki jedzenia
    for( size_t i = 0; i < feedUnits.size(); ++i )
    {
        feedUnits[i]->draw(window);
    }
}