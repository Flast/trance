#include <string>
#include <iterator>

#include <boost/test/minimal.hpp>

#include <boost/range/adaptor/reversed.hpp>

#include <trance/range/ncopy.hpp>

int
test_main( int, char *[] )
{
    const std::string orig = "/libs/algorithm/test/ncopy/run1.cpp";

    std::string output;
    trance::ncopy( orig, 5, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "/libs" );

    std::string().swap( output );
    trance::ncopy( orig | boost::adaptors::reversed, 8, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "ppc.1nur" );

    return 0;
}


