#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Game_Tests

#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "../include/Unit.hpp"
#include "../src/Unit.cpp"

#include "../include/Cell.hpp"
#include "../src/Cell.cpp"

#include "../include/Player.hpp"
#include "../src/Player.cpp"

#include "../include/ManualPlayer.hpp"
#include "../src/ManualPlayer.cpp"

#include "../include/Bot.hpp"
#include "../src/Bot.cpp"

#include "../include/Game.hpp"
#include "../src/Game.cpp"

#include "../include/Board.hpp"
#include "../src/Board.cpp"

#include "../include/GlobalValues.hpp"

using namespace sf;

/**
 * tests to class Unit 
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
 * tests to class Cell
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

BOOST_AUTO_TEST_CASE( distanceTest3 )
{
    Cell cell(12.5, 31.22, 0, false);
    Cell cell2(7.12, 49.2, 1, true);
    BOOST_REQUIRE_CLOSE( cell.distance(cell2), 18.767653, 0.0001);
}

BOOST_AUTO_TEST_CASE( updateSpeedTest1 )
{
    Cell cell(122.123, 333.777, 0, true);
    cell.updateSpeed();

    BOOST_REQUIRE_CLOSE( cell.getSpeed(), ( basicSpeed + (0.1 * basicSpeed) * (2 - level) )/ sqrt(cell.getRadius()/2), 0.0001);
}

BOOST_AUTO_TEST_CASE( updateSpeedTest2 )
{
    Cell cell(122.123, 333.777, 2.0, true);
    cell.updateSpeed();

    BOOST_REQUIRE_CLOSE( cell.getSpeed(), ( basicSpeed + (0.1 * basicSpeed) * (2 - level) ) / sqrt(cell.getRadius()/2) + 2.0, 0.0001 );
    sleep(sf::milliseconds(2));
    cell.updateSpeed();
    BOOST_REQUIRE_CLOSE( cell.getSpeed(), ( basicSpeed + (0.1 * basicSpeed) * (2 - level) ) / sqrt(cell.getRadius()/2) + 2.0 - 0.1, 0.0001 );
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

BOOST_AUTO_TEST_CASE( updateTest3 )
{
    double x = 0;
    double y = 0;
    double xDirection = -1;
    double yDirection = -1;
    Cell cell(x, y, 2.0, true);

    int mass = 700;
    cell.setMass(mass);
    cell.setRadius(mass);

    double radius = cell.getRadius();
    cell.setPosition(sf::Vector2f(radius, radius));
    cell.setDirecction(xDirection, yDirection);

    cell.updateSpeed();
    double speed = cell.getSpeed();

    cell.update();

    BOOST_REQUIRE_CLOSE( cell.getPosition().x, radius, 0.0001 );
    BOOST_REQUIRE_CLOSE( cell.getPosition().y, radius, 0.0001 );
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * tests to class Player
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

/**
 * tests to class ManualPlayer
 */

BOOST_AUTO_TEST_SUITE( testPlayer )

BOOST_AUTO_TEST_CASE( setMousePositionTest1 )
{
    double posX = 92.2;
    double posY = 123.1;
    ManualPlayer p(posX, posY);

    double x = 321.9;
    double y = 422;

    p.setMousePosition(sf::Vector2i(x, y));

    double newX = p.cells[0]->getPosition().x;
    double newY = p.cells[0]->getPosition().y;

    //check direction
    BOOST_REQUIRE_CLOSE( newX / newY, x / y, 5 );

    //chech if distance is smaller
    BOOST_CHECK_LT( (newX - posX) * (newX - posX) + (newY - posY) * (newY - posY), (x- posX) * (x - posX) + (y - posY) * (y - posY) );
}

BOOST_AUTO_TEST_CASE( divideTest1 )
{
    double posX = 92.2;
    double posY = 123.1;
    ManualPlayer p(posX, posY);

    double x = 321.9;
    double y = 422;

    p.divide(sf::Vector2i(x, y));

    double newX = p.cells[1]->getPosition().x;
    double newY = p.cells[1]->getPosition().y;

    BOOST_CHECK_EQUAL(p.cells.size(), 2);

    //check place of new cell
    //check direction
    BOOST_REQUIRE_CLOSE( newX / newY, x / y, 5 );

    //chech if distance is smaller
    BOOST_CHECK_LT( (newX - posX) * (newX - posX) + (newY - posY) * (newY - posY), (x- posX) * (x - posX) + (y - posY) * (y - posY) );
}

BOOST_AUTO_TEST_SUITE_END()

/**
 * tests to class Bot
 */

BOOST_AUTO_TEST_SUITE( testBot )

BOOST_AUTO_TEST_CASE( botBehaviourTest1 )
{
    std::vector<Cell*> vec;
    std::vector<Unit*> uvec;

    vec.push_back(new Cell(0, 0, 0, false, 2));
    vec.push_back(new Cell(10, 10, 0, false, 30));
    vec.push_back(new Cell(20, 20, 0, false, 20));

    Bot bot = Bot(vec[1]);

    bot.setNextPosition(uvec, vec);

    double dist1 = (vec[0]->getPosition().x - vec[1]->getPosition().x)*(vec[0]->getPosition().x - vec[1]->getPosition().x) +
                    (vec[0]->getPosition().y - vec[1]->getPosition().y)*(vec[0]->getPosition().y - vec[1]->getPosition().y);

    double dist2 = (vec[2]->getPosition().x - vec[1]->getPosition().x)*(vec[2]->getPosition().x - vec[1]->getPosition().x) +
                    (vec[2]->getPosition().y - vec[1]->getPosition().y)*(vec[2]->getPosition().y - vec[1]->getPosition().y);                

    // check if bot goes toward smaller bigger cell
    BOOST_CHECK_LT( dist2, dist1 );
}

BOOST_AUTO_TEST_CASE( botBehaviourTest2 )
{
    std::vector<Cell*> vec;
    std::vector<Unit*> uvec;

    vec.push_back(new Cell(0, 0, 0, false, 2));
    vec.push_back(new Cell(10, 10, 0, false, 30));
    vec.push_back(new Cell(20, 20, 0, false, 20));

    uvec.push_back(new Unit(5, 5, 1));

    Bot bot = Bot(vec[1]);

    bot.setNextPosition(uvec, vec);

    double dist1 = (vec[0]->getPosition().x - vec[1]->getPosition().x)*(vec[0]->getPosition().x - vec[1]->getPosition().x) +
                    (vec[0]->getPosition().y - vec[1]->getPosition().y)*(vec[0]->getPosition().y - vec[1]->getPosition().y);

    double dist2 = (vec[2]->getPosition().x - vec[1]->getPosition().x)*(vec[2]->getPosition().x - vec[1]->getPosition().x) +
                    (vec[2]->getPosition().y - vec[1]->getPosition().y)*(vec[2]->getPosition().y - vec[1]->getPosition().y);                

    // check if bot goes toward smaller bigger cell and ignore food cells
    BOOST_CHECK_LT( dist2, dist1 );
}

BOOST_AUTO_TEST_CASE( botBehaviourTest3 )
{
    std::vector<Cell*> vec;
    std::vector<Unit*> uvec;

    vec.push_back(new Cell(17, 17, 0, false, 5));
    vec.push_back(new Cell(10, 10, 0, false, 30));
    vec.push_back(new Cell(20, 20, 0, false, 50));

    Bot bot = Bot(vec[1]);

    bot.setNextPosition(uvec, vec);

    double dist1 = (0 - vec[1]->getPosition().x)*(0 - vec[1]->getPosition().x) +
                    (0 - vec[1]->getPosition().y)*(0 - vec[1]->getPosition().y);

    double dist2 = (vec[2]->getPosition().x - vec[1]->getPosition().x)*(vec[2]->getPosition().x - vec[1]->getPosition().x) +
                    (vec[2]->getPosition().y - vec[1]->getPosition().y)*(vec[2]->getPosition().y - vec[1]->getPosition().y);                

    // check if bot run from bigger cell and don't go to chase smaller one
    BOOST_CHECK_LT( dist1, dist2 );
}

BOOST_AUTO_TEST_SUITE_END()