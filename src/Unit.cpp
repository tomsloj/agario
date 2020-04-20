#include "../include/Unit.hpp"

#include <iostream>

Unit::Unit(  )
{
    std::cout<<"UNIT\n";
}

Unit::Unit( double X, double Y, int size /*= 1*/ )
{
    std::cout<<"UNIT\n";
    this->X = X;
    this->Y = Y;
    this->size = size;
}

void Unit::grow(const int sizeOfGrowth)
{
    size += sizeOfGrowth;
}

void Unit::increaseSize( int sizeReduction /*= 1*/ )
{
    size -= sizeReduction;
}

int Unit::getSize()
{
    return size;
}