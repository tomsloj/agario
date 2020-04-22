#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Student_Tests

#include <boost/test/unit_test.hpp>

#include "../include/Unit.hpp"
#include "../src/Unit.cpp"

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