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
    //TODO zjadanie cell przez cell
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
        board.cells.push_back(new Cell());
        stream >> *board.cells[i];
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