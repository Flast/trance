#include <string>

#include <boost/test/minimal.hpp>

#include <trance/typeinfo.hpp>

int
test_main( int, char *[] )
{
    const std::string expected( "int" );
    BOOST_REQUIRE( expected == TRANCE_TYPEID( 0 ).demangled_name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID( int ).demangled_name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID_BY_EXPR( 0 ).demangled_name() );
    BOOST_REQUIRE( expected == TRANCE_TYPEID_BY_TYPE( int ).demangled_name() );
    return 0;
}

