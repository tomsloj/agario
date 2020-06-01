#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Game_Tests

#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "../include/Unit.hpp"
#include "../src/Unit.cpp"

#include "../include/Cell.hpp"
#include "../src/Cell.cpp"

#include "../include/Board.hpp"
#include "../src/Board.cpp"

#include "../include/Player.hpp"
#include "../src/Player.cpp"

#include "../include/ManualPlayer.hpp"
#include "../src/ManualPlayer.cpp"

#include "../include/Bot.hpp"
#include "../src/Bot.cpp"

#include "../include/GlobalValues.hpp"

using namespace sf;

/**
 * testy klasy Unit 
 */
BOOST_AUTO_TEST_SUITE( testUnit )


BOOST_AUTO_TEST_CASE( creatingUnitTest1 )
{
    Unit u = Unit( 0.0, 0.0 );
    BOOST_CHECK_EQUAL( u.getMass(), 1 );
}

BOOST_AUTO_TEST_CASE( creatingUnitTest2 )
{
    int size = 1234;
    Unit u = Unit( 0.0, 0.0, size );
    BOOST_CHECK_EQUAL( u.getMass(), size );
}

BOOST_AUTO_TEST_CASE( growingUnitTest1 )
{
    int size = 730;
    int growthSize = 459;
    Unit u = Unit( 0.0, 0.0, size );
    u.grow(growthSize);
    BOOST_CHECK_EQUAL( u.getMass(), size + growthSize );
}

BOOST_AUTO_TEST_CASE( growingUnitTest2 )
{
    int growthSize = 9421;
    Unit u = Unit( 0.0, 0.0 );
    u.grow(growthSize);
    BOOST_CHECK_EQUAL( u.getMass(), 1 + growthSize );
}

BOOST_AUTO_TEST_CASE( increaseSizeUnitTest1 )
{
    int size = 1234;
    int increase = 442;
    Unit u = Unit( 0.0, 0.0, size );
    u.decreaseMass( increase );
    BOOST_CHECK_EQUAL( u.getMass(), size - increase );
}


BOOST_AUTO_TEST_CASE( setRadiusUnitTest1 )
{
    double mass = 400;
    Unit u;
    u.setRadius(mass);
    BOOST_CHECK_CLOSE( u.getRadius(), sqrt(mass), 0.0001 );
}


BOOST_AUTO_TEST_CASE( streamOperatorsUnitTest1 )
{
    Unit u1 = Unit(32.92, 123.43, 843);
    u1.setColor(sf::Color( 123, 21, 21, 8));
    Unit u2;

    std::ofstream outFile;
    outFile.open ("bin/test");
    outFile << u1;
    outFile.close();

    std::ifstream inFile;
    inFile.open ("bin/test");
    inFile >> u2;
    inFile.close();
    
    remove("bin/test");

    BOOST_CHECK_EQUAL( u1.getColor().r, u2.getColor().r );
    BOOST_CHECK_EQUAL( u1.getColor().g, u2.getColor().g );
    BOOST_CHECK_EQUAL( u1.getColor().b, u2.getColor().b );
    BOOST_CHECK_EQUAL( u1.getMass(), u2.getMass() );
    BOOST_CHECK_EQUAL( u1.getPosition().x, u2.getPosition().x );
    BOOST_CHECK_EQUAL( u1.getPosition().y, u2.getPosition().y );  
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * testy klasy Cell
 */

BOOST_AUTO_TEST_SUITE( testBoard )

BOOST_AUTO_TEST_CASE( distanceTest1 )
{
    Cell cell(12.5, 31.22, 0, false);
    Unit unit(7.12, 49.2);
    BOOST_REQUIRE_CLOSE( cell.distance(unit), 18.767653, 0.0001);
}

BOOST_AUTO_TEST_CASE( distanceTest2 )
{
    Cell cell(122.123, 333.777, 50.0, true);
    Unit unit(122.123, 333.777);
    BOOST_REQUIRE_CLOSE( cell.distance(unit), 0, 0.0001);
}

BOOST_AUTO_TEST_CASE( updateSpeedTest1 )
{
    Cell cell(122.123, 333.777, 0, true);
    cell.updateSpeed();

    BOOST_REQUIRE_CLOSE( cell.getSpeed(), basicSpeed / sqrt(cell.getRadius()/2), 0.0001);
}

BOOST_AUTO_TEST_CASE( updateSpeedTest2 )
{
    Cell cell(122.123, 333.777, 2.0, true);
    cell.updateSpeed();

    BOOST_REQUIRE_CLOSE( cell.getSpeed(), basicSpeed / sqrt(cell.getRadius()/2) + 2.0, 0.0001 );
    sleep(sf::milliseconds(2));
    cell.updateSpeed();
    BOOST_REQUIRE_CLOSE( cell.getSpeed(), basicSpeed / sqrt(cell.getRadius()/2) + 2.0 - 0.1, 0.0001 );
}

BOOST_AUTO_TEST_CASE( updateTest1 )
{
    double x = 122.123;
    double y = 321.111;
    double xDirection = 1;
    double yDirection = 1;
    Cell cell(x, y, 2.0, true);
    cell.setDirecction(xDirection, yDirection);

    cell.updateSpeed();
    double speed = cell.getSpeed();

    cell.update();

    BOOST_REQUIRE_CLOSE( cell.getPosition().x, x + xDirection * speed, 0.0001 );
    BOOST_REQUIRE_CLOSE( cell.getPosition().y, y + yDirection * speed, 0.0001 );
}

BOOST_AUTO_TEST_CASE( updateTest2 )
{
    double x = gameWindowWidth;
    double y = gameWindowHeight;
    double xDirection = 1;
    double yDirection = 1;
    Cell cell(x, y, 2.0, true);

    int mass = 450;
    cell.setMass(mass);
    cell.setRadius(mass);

    double radius = cell.getRadius();
    cell.setPosition(sf::Vector2f(x - radius, y - radius));
    cell.setDirecction(xDirection, yDirection);

    cell.updateSpeed();
    double speed = cell.getSpeed();

    cell.update();

    BOOST_REQUIRE_CLOSE( cell.getPosition().x, gameWindowWidth - radius, 0.0001 );
    BOOST_REQUIRE_CLOSE( cell.getPosition().y, gameWindowHeight - radius, 0.0001 );
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * testy klasy Board
 */

BOOST_AUTO_TEST_SUITE( testBoard )

BOOST_AUTO_TEST_CASE( addCellsSizeTest1 )
{
    Board board( Vector2u(100, 200));
    int number = 13;
    BOOST_CHECK_EQUAL( board.getCells().size(), 0 );
    for ( int i = 0; i < number; ++i )
    {
        Cell *cell = new Cell();
        board.addCell(cell);
    }
    BOOST_CHECK_EQUAL( board.getCells().size(), number );
    
}

BOOST_AUTO_TEST_CASE( addCellsDataTest1 )
{
    Board board( Vector2u(150, 30));
    
    Cell *cell1 = new Cell();
    board.addCell(cell1);

    Cell *cell2 = new Cell();
    board.addCell(cell2);

    Cell *cell3 = new Cell();
    board.addCell(cell3);

    BOOST_CHECK_EQUAL( board.getCells().size(), 3 );
    BOOST_CHECK_EQUAL( board.getCells()[0], cell1 );
    BOOST_CHECK_EQUAL( board.getCells()[1], cell2 );
    BOOST_CHECK_EQUAL( board.getCells()[2], cell3 ); 
}

BOOST_AUTO_TEST_CASE( deleteCellsDataTest1 )
{
    Board board( Vector2u(150, 30));
    
    Cell *cell1 = new Cell();
    board.addCell(cell1);

    Cell *cell2 = new Cell();
    board.addCell(cell2);

    Cell *cell3 = new Cell();
    board.addCell(cell3);

    board.deleteCell(cell2);

    BOOST_CHECK_EQUAL( board.getCells().size(), 2 );
    BOOST_CHECK_EQUAL( board.getCells()[0], cell1 );
    BOOST_CHECK_EQUAL( board.getCells()[1], cell3 );
}

BOOST_AUTO_TEST_CASE( addFeedUnitsSizeTest1 )
{
    Board board( Vector2u(100, 200));
    int number = 13;
    BOOST_CHECK_EQUAL( board.getFeedUnits().size(), 0 );
    for ( int i = 0; i < number; ++i )
    {
        Unit *unit = new Unit();
        board.addFeedUnit(unit);
    }
    BOOST_CHECK_EQUAL( board.getFeedUnits().size(), number );
    
}

BOOST_AUTO_TEST_CASE( addFeedUnitsDataTest1 )
{
    Board board( Vector2u(150, 30));
    
    Unit *unit1 = new Unit();
    board.addFeedUnit(unit1);

    Unit *unit2 = new Unit();
    board.addFeedUnit(unit2);

    Unit *unit3 = new Unit();
    board.addFeedUnit(unit3);

    BOOST_CHECK_EQUAL( board.getFeedUnits().size(), 3 );
    BOOST_CHECK_EQUAL( board.getFeedUnits()[0], unit1 );
    BOOST_CHECK_EQUAL( board.getFeedUnits()[1], unit2 );
    BOOST_CHECK_EQUAL( board.getFeedUnits()[2], unit3 ); 
}

BOOST_AUTO_TEST_CASE( deleteUnitsDataTest1 )
{
    Board board( Vector2u(150, 30));
    
    Unit *unit1 = new Unit();
    board.addFeedUnit(unit1);

    Unit *unit2 = new Unit();
    board.addFeedUnit(unit2);

    Unit *unit3 = new Unit();
    board.addFeedUnit(unit3);

    board.deleteFeedUnit(unit2);

    BOOST_CHECK_EQUAL( board.getFeedUnits().size(), 2 );
    BOOST_CHECK_EQUAL( board.getFeedUnits()[0], unit1 );
    BOOST_CHECK_EQUAL( board.getFeedUnits()[1], unit3 );
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * testy klasy Player
 */

BOOST_AUTO_TEST_SUITE( testPlayer )

BOOST_AUTO_TEST_CASE( addCellSizeTest1 )
{
    Player p(92, 123.1, 0.2, 72);
    int number = 23;

    BOOST_CHECK_EQUAL( p.cells.size(), 1 );

    for( unsigned int i = 0; i < number; ++i )
        p.addCell(new Cell());

    BOOST_CHECK_EQUAL( p.cells.size(), number + 1 );
}

BOOST_AUTO_TEST_CASE( removeCellSizeTest1 )
{
    Player p(92, 123.1, 0.2, 72);
    int number = 23;

    Cell* c1;
    Cell* c2;

    BOOST_CHECK_EQUAL( p.cells.size(), 1 );
    p.addCell(c1);
    p.addCell(c2);
    BOOST_CHECK_EQUAL( p.cells.size(), 3 );
    p.removeCell(c2);
    BOOST_CHECK_EQUAL( p.cells.size(), 2 );
    p.removeCell(c1);
    BOOST_CHECK_EQUAL( p.cells.size(), 1 );
}

BOOST_AUTO_TEST_SUITE_END()