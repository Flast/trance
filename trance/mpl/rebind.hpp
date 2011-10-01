// trance rebind.hpp - Rebinding type.
//
// Copyright (c) 2011 - 2011 Kohei Takahashi (Flast)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef IG_TRANCE_MPL_REBIND_HPP_ONCE_
#define IG_TRANCE_MPL_REBIND_HPP_ONCE_

#include <trance/config.hpp>

#ifndef TRANCE_HAS_VARIADIC_TEMPLATES
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/arithmetic/inc.hpp>
#   include <boost/preprocessor/comparison/less_equal.hpp>
#   include <boost/preprocessor/repetition/for.hpp>
#   include <boost/preprocessor/repetition/enum_params.hpp>
#   include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#   include <boost/preprocessor/repetition/enum_trailing.hpp>
#endif

namespace trance
{

namespace mpl
{

#ifdef TRANCE_HAS_VARIADIC_TEMPLATES

template < typename, typename... >
struct rebind;

template <
  template < typename... > class F
, typename... old_args
, typename... new_args
>
struct rebind< F< old_args... >, new_args... >
{ typedef F< new_args... > type; };

#else // TRANCE_HAS_VARIADIC_TEMPLATES

namespace detail
{

struct _not_a_type;

} // namespace detail

template <
  typename
, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
    TRANCE_MPL_LIMIT_VARIADIC_EMULATE, typename Arg, detail::_not_a_type
  )
>
struct rebind;

#define ENUM_IDENTITY( unused_z_, unused_c_, value ) value
#define REBIND_IMPL( unused_r_, n_ )                              \
  template <                                                      \
    template < BOOST_PP_ENUM_PARAMS( n_, typename arg ) > class F \
  , BOOST_PP_ENUM_PARAMS( n_, typename old_arg )                  \
  , BOOST_PP_ENUM_PARAMS( n_, typename new_arg )                  \
  >                                                               \
  struct rebind<                                                  \
    F< BOOST_PP_ENUM_PARAMS( n_, old_arg ) >                      \
  , BOOST_PP_ENUM_PARAMS( n_, new_arg )                           \
    BOOST_PP_ENUM_TRAILING(                                       \
      BOOST_PP_SUB( TRANCE_MPL_LIMIT_VARIADIC_EMULATE, n_ )       \
    , ENUM_IDENTITY                                               \
    , detail::_not_a_type                                         \
    )                                                             \
  >                                                               \
  { typedef F< BOOST_PP_ENUM_PARAMS( n_, new_arg ) > type; };     \

#define PRED( unused_r_, n_ ) BOOST_PP_LESS_EQUAL( n_, TRANCE_MPL_LIMIT_VARIADIC_EMULATE )
#define NEXT( unused_r_, n_ ) BOOST_PP_INC( n_ )
BOOST_PP_FOR( 1, PRED, NEXT, REBIND_IMPL )

#undef NEXT
#undef PRED

#undef REBIND_IMPL
#undef ENUM_IDENTITY

#endif // TRANCE_HAS_VARIADIC_TEMPLATES

} // namespace mpl

} // namespace trance

#endif // IG_TRANCE_MPL_REBIND_HPP_ONCE_

