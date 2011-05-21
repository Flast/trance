#include <boost/test/minimal.hpp>

#include <boost/array.hpp>
#include <boost/range/numeric.hpp>

#include <trance/local_function.hpp>

int
test_main( int, char *[] )
{
    using boost::accumulate;
    using boost::array;

    const array< int, 6 > orig_data = {{ 0, 1, 2, 3, 4, 5 }};

    TRANCE_LOCAL_FUNCTION( int, _add, ( int _x, int _y ),
    {
        return _x + _y;
    } );
    BOOST_REQUIRE( 15 == accumulate( orig_data, 0, _add ) );

    return 0;
}

