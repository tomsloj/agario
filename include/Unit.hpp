#ifndef UNIT_H
#define UNIT_H

class Unit
{
    private:
        int size;
        double X;
        double Y;
    public:
        Unit();
        Unit( double X, double Y, int size = 1 );
        void grow(const int sizeOfGrowth);
        void increaseSize( int sizeReduction = 1 );
        int getSize();
};

#endif 