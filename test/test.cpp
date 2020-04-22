#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Student_Tests

#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>

#include "../include/Unit.hpp"
#include "../src/Unit.cpp"

#include "../include/Cell.hpp"
#include "../src/Cell.cpp"

#include "../include/Board.hpp"
#include "../src/Board.cpp"

using namespace sf;

BOOST_AUTO_TEST_SUITE( testUnit )


BOOST_AUTO_TEST_CASE( creatingUnitTest1 )
{
    Unit u = Unit( 0.0, 0.0 );
    BOOST_CHECK( u.getMass() == 1 );
}

BOOST_AUTO_TEST_CASE( creatingUnitTest2 )
{
    int size = 1234;
    Unit u = Unit( 0.0, 0.0, size );
    BOOST_CHECK( u.getMass() == size );
}

BOOST_AUTO_TEST_CASE( growingUnitTest1 )
{
    int size = 730;
    int growthSize = 459;
    Unit u = Unit( 0.0, 0.0, size );
    u.grow(growthSize);
    BOOST_CHECK( u.getMass() == size + growthSize );
}

BOOST_AUTO_TEST_CASE( growingUnitTest2 )
{
    int growthSize = 9421;
    Unit u = Unit( 0.0, 0.0 );
    u.grow(growthSize);
    BOOST_CHECK( u.getMass() == 1 + growthSize );
}

BOOST_AUTO_TEST_CASE( increaseSizeUnitTest1 )
{
    int size = 1234;
    int increase = 442;
    Unit u = Unit( 0.0, 0.0, size );
    u.increaseMass( increase );
    BOOST_CHECK( u.getMass() == size - increase );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( testBoard )

BOOST_AUTO_TEST_CASE( addCellsSizeTest1 )
{
    
    Board board( Vector2f(100.0, 200.0));
    int number = 13;
    BOOST_CHECK( board.getCells().size() == 0 );
    for ( int i = 0; i < number; ++i )
    {
        Cell *cell = new Cell();
        board.addCell(cell);
    }
    BOOST_CHECK( board.getCells().size() == number );
    
}

BOOST_AUTO_TEST_CASE( addCellsDataTest1 )
{
    
    Board board( Vector2f(150.0, 30.0));
    
    Cell *cell1 = new Cell();
    board.addCell(cell1);

    Cell *cell2 = new Cell();
    board.addCell(cell2);

    Cell *cell3 = new Cell();
    board.addCell(cell3);

    BOOST_CHECK( board.getCells().size() == 3 );
    BOOST_CHECK( board.getCells()[0] == cell1 );
    BOOST_CHECK( board.getCells()[1] == cell2 );
    BOOST_CHECK( board.getCells()[2] == cell3 ); 
}




BOOST_AUTO_TEST_SUITE_END()