#include <functional>
using namespace std;

#include <boost/test/minimal.hpp>

#include <trance/value_holder.hpp>

int
test_main( int, char *[] )
{
    // static_cast< bool >( 0 )
    if ( trance::value_holder< int > x = 0 )
    { BOOST_FAIL( "conditioning failed" ); }

    // static_cast< bool >( 0 )
    if ( trance::value_holder< int > x = trance::make_holder( 0 ) )
    { BOOST_FAIL( "conditioning failed" ); }

    // 1 < 0
    if ( trance::value_holder< int > x = trance::make_holder( 0, bind1st( less< int >(), 1 ) ) )
    { BOOST_FAIL( "conditioning failed" ); }

    return 0;
}

