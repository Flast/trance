#include <boost/test/minimal.hpp>

#include <trance/value_holder.hpp>

int
test_main( int, char *[] )
{
    // Always condition is true.
    if ( trance::value_holder< int > x = 0 )
    { BOOST_FAIL( "conditioning failed" ); }

    // Always condition is true.
    if ( trance::value_holder< int, bool( * )( int ) > x = 0 )
    { BOOST_FAIL( "conditioning failed" ); }

    // Always condition is true.
    if ( trance::value_holder< int, bool( & )( int ) > x = 0 )
    { BOOST_FAIL( "conditioning failed" ); }

    return 0;
}

