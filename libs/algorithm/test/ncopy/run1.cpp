#include <string>
#include <iterator>

#include <boost/test/minimal.hpp>

#include <trance/algorithm/ncopy.hpp>

int
test_main( int, char *[] )
{
    const std::string orig = "/libs/algorithm/test/ncopy/run1.cpp";

    std::string output;
    trance::ncopy( orig.begin(), orig.end(), 5, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "/libs" );

    std::string().swap( output );
    trance::ncopy( orig.rbegin(), orig.rend(), 8, std::back_inserter( output ) );
    BOOST_REQUIRE( output == "ppc.1nur" );

    return 0;
}

