#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Student_Tests

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( exampleTestSuite )


BOOST_AUTO_TEST_CASE( example1 )
{
    BOOST_CHECK( 1 == 1);
}

BOOST_AUTO_TEST_SUITE_END()