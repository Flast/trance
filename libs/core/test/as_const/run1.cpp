#include <boost/test/minimal.hpp>

#include <trance/as_const.hpp>

void
c( int & )
{ BOOST_FAIL( "overload resolution failed" ); }

void
c( const int & ) {}

void
cv( volatile int & )
{ BOOST_FAIL( "overload resolution failed" ); }

void
cv( const volatile int & ) {}

int
test_main( int, char *[] )
{
    int x = 0;
    c( trance::as_const( x ) ); // non-cv to const
    cv( trance::as_const( x ) ); // non-cv to const volatile

    const int cx = 0;
    c( trance::as_const( cx ) ); // const to const
    cv( trance::as_const( cx ) ); // const to const volatile

    volatile int vx = 0;
    cv( trance::as_const( vx ) ); // volatile to const volatile

    const volatile int cvx = 0;
    cv( trance::as_const( cvx ) ); // const volatile to const volatile

    return 0;
}

