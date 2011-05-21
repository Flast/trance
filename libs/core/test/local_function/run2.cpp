#include <boost/test/minimal.hpp>

#include <trance/local_function.hpp>

int
test_main( int, char *[] )
{
    TRANCE_LOCAL_FUNCTION( int, inc, ( int _n ),
    {
        return _n + 1;
    } );
    BOOST_REQUIRE( 1 == inc( 0 ) );

    TRANCE_LOCAL_FUNCTION( int, dec, ( int _n ),
    {
        return _n - 1;
    } );
    BOOST_REQUIRE( 0 == dec( 1 ) );
}

