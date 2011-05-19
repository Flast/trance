#include <string>
#include <typeinfo>

#include <boost/test/minimal.hpp>

#include <trance/typeinfo.hpp>

int
test_main( int, char *[] )
{
    const std::type_info &stdinfo = typeid( int );
    const std::string expected = stdinfo.name();

    BOOST_REQUIRE( expected == TRANCE_TYPEID( 0 ).name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID( int ).name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID_BY_EXPR( 0 ).name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID_BY_TYPE( int ).name() );

    return 0;
}

