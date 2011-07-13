#include <string>
#include <iterator>

#include <boost/test/minimal.hpp>

#include <boost/range/adaptor/reversed.hpp>

#include <trance/range/copy_n.hpp>

int
test_main( int, char *[] )
{
    const std::string orig = "/libs/algorithm/test/copy_n/run1.cpp";

    std::string output;
    trance::copy_n( orig, 5, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "/libs" );

    std::string().swap( output );
    trance::copy_n( orig | boost::adaptors::reversed, 8, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "ppc.1nur" );

    return 0;
}


