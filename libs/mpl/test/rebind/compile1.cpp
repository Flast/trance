#include <boost/mpl/assert.hpp>

#include <boost/type_traits/is_same.hpp>

#include <trance/mpl/rebind.hpp>

template < typename > struct S1;
BOOST_MPL_ASSERT(( boost::is_same<
  trance::mpl::rebind< S1< void >, int >::type
, S1< int >
> ));

template < typename, typename > struct S2;
BOOST_MPL_ASSERT(( boost::is_same<
  trance::mpl::rebind< S2< void, void >, int, char >::type
, S2< int, char >
> ));

template < typename, typename, typename > struct S3;
BOOST_MPL_ASSERT(( boost::is_same<
  trance::mpl::rebind< S3< void, void, void >, int, char, float >::type
, S3< int, char, float >
> ));

