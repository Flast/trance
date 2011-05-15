#include <string>

#include <boost/test/minimal.hpp>

#include <trance/typeinfo.hpp>

int
test_main( int, char *[] )
{
    BOOST_REQUIRE( std::string( "int" ) == TRANCE_TYPEID( 0 ).demangled_name() );
    BOOST_REQUIRE( std::string( "int" ) == TRANCE_TYPEID( int ).demangled_name() );
    return 0;
}

