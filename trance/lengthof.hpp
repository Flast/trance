// trance lengthof.hpp - Array length Library
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

#ifndef IG_TRANCE_LENGTHOF_HPP_ONCE_
#define IG_TRANCE_LENGTHOF_HPP_ONCE_

#include <trance/config.hpp>

#include <cstddef>

#if !defined( BOOST_NO_0X_HDR_ARRAY )
#   include <array>
#endif // BOOST_NO_0X_HDR_ARRAY

#if !defined( BOOST_NO_0X_HDR_TYPE_TRAITS )
#   include <type_traits>
#else
#   include <boost/type_traits/remove_cv.hpp>
#   include <boost/type_traits/remove_reference.hpp>
#endif // BOOST_NO_0X_HDR_TYPE_TRAITS

#include <boost/type_traits/integral_constant.hpp>

#include <trance/detail/typeof.hpp>

namespace boost
{

// forward decl
template < class, std::size_t >
class array;

} // namespace boost

namespace trance
{

namespace lengthof_detail
{

#define TRANCE_LENGTHOF_BY_TYPE( _type_id )                               \
  static_cast< ::std::size_t >(                                           \
    ::trance::lengthof_detail::_lengthof_by_type< _type_id, true >::value \
  )                                                                       \

#define TRANCE_LENGTHOF_BY_EXPR( _Expr )            \
  static_cast< ::std::size_t >(                     \
    ::trance::lengthof_detail::_lengthof_by_expr(   \
      TRANCE_DETAIL_TYPEOF( _Expr )                 \
    )                                               \
  )                                                 \

template < typename, bool >
struct _lengthof_by_type;

template < typename T >
struct _lengthof_by_type< T, true >
  : public _lengthof_by_type<
      BOOST_DEDUCED_TYPENAME TRANCE_TYPE_TRAITS_NAMESPACE::remove_cv<
        BOOST_DEDUCED_TYPENAME TRANCE_TYPE_TRAITS_NAMESPACE::remove_reference<
          T
        >::type
      >::type,
      false
    > {};

// for C style array
template < typename T, ::std::size_t N >
struct _lengthof_by_type< T[ N ], false >
  : public ::boost::integral_constant< ::std::size_t, N > {};

// for Boost.Array
template < typename T, ::std::size_t N >
struct _lengthof_by_type< ::boost::array< T, N >, false >
  : public ::boost::integral_constant< ::std::size_t, N > {};

// for STL Array (C++0x)
#if !defined( BOOST_NO_0X_HDR_ARRAY )
template < typename T, ::std::size_t N >
struct _lengthof_by_type< ::std::array< T, N >, false >
  : public ::boost::integral_constant< ::std::size_t, N > {};
#endif // !BOOST_NO_0X_HDR_ARRAY

template < typename T >
TRANCE_CONSTEXPR ::std::size_t
_lengthof_by_expr( T * ) TRANCE_NOEXCEPT
{ return TRANCE_LENGTHOF_BY_TYPE( T ); }

} // namespace lengthof_detail

} // namespace trance

#endif // IG_TRANCE_LENGTHOF_HPP_ONCE_

