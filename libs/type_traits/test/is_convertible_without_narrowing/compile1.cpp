#include <boost/mpl/assert.hpp>

#include <trance/type_traits/is_convertible_without_narrowing.hpp>

// allow cv-qualifiers
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<                char, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const          char, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<       volatile char, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const volatile char, char > ));

// allow ref-qualifiers
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<                char &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const          char &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<       volatile char &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const volatile char &, char > ));

#ifdef TRANCE_DETAIL_ENABLE_CXX0X_NARROWING_CONVERSION

// ignore narrowing conversion in C++0x
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing<                int, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing< const          int, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing<       volatile int, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing< const volatile int, char > ));

BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing<                int &, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing< const          int &, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing<       volatile int &, char > ));
BOOST_MPL_ASSERT_NOT(( trance::is_convertible_without_narrowing< const volatile int &, char > ));

#else

// allow narrowing conversion in C++03
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<                int, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const          int, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<       volatile int, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const volatile int, char > ));

BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<                int &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const          int &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing<       volatile int &, char > ));
BOOST_MPL_ASSERT(( trance::is_convertible_without_narrowing< const volatile int &, char > ));

#endif // TRANCE_DETAIL_ENABLE_CXX0X_NARROWING_CONVERSION

