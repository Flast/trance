#include <typeinfo>

#include <boost/test/minimal.hpp>

#include <trance/typeinfo.hpp>

int
test_main( int, char *[] )
{
    BOOST_REQUIRE( typeid( int ) == TRANCE_TYPEID( 0 ) );
    BOOST_REQUIRE( typeid( int ) == TRANCE_TYPEID( int ) );
    BOOST_REQUIRE( typeid( int ) == TRANCE_TYPEID_BY_EXPR( 0 ) );
    BOOST_REQUIRE( typeid( int ) == TRANCE_TYPEID_BY_TYPE( int ) );

    BOOST_REQUIRE( TRANCE_TYPEID( 0 ) == typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID( int ) == typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID_BY_EXPR( 0 ) == typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID_BY_TYPE( int ) == typeid( int ) );

    BOOST_REQUIRE( typeid( double ) != TRANCE_TYPEID( 0 ) );
    BOOST_REQUIRE( typeid( double ) != TRANCE_TYPEID( int ) );
    BOOST_REQUIRE( typeid( double ) != TRANCE_TYPEID_BY_EXPR( 0 ) );
    BOOST_REQUIRE( typeid( double ) != TRANCE_TYPEID_BY_TYPE( int ) );

    BOOST_REQUIRE( TRANCE_TYPEID( 0.0 ) != typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID( float ) != typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID_BY_EXPR( 0.0 ) != typeid( int ) );
    BOOST_REQUIRE( TRANCE_TYPEID_BY_TYPE( float ) != typeid( int ) );

    return 0;
}

