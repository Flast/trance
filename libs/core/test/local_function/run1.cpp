#include <boost/test/minimal.hpp>

#include <trance/local_function.hpp>

int
test_main( int, char *[] )
{
    TRANCE_LOCAL_FUNCTION( void, _exec1, ( void ), {} );
    void ( *_pexec1 )( void ) = _exec1;
    BOOST_REQUIRE( _pexec1 == _exec1 );

    TRANCE_LOCAL_FUNCTION( void, _exec2, ( void ), {} );
    void ( *_pexec2 )( void ) = _exec2;
    BOOST_REQUIRE( _pexec1 != _pexec2 );

    return 0;
}

