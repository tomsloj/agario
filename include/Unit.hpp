#ifndef UNIT_H
#define UNIT_H

class Unit
{
    private:
        int size;
        int X;
        int Y;
    public:
        Unit();
        Unit( int X, int Y, int size = 1 );
        void grow(const int sizeOfGrowth);
        void increaseSize( int sizeReduction = 1 );
};

#endif 