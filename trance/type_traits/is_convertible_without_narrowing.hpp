// trance is_convertible_without_narrowing.hpp - Convertible checker
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

#ifndef IG_TRANCE_TYPE_TRAITS_IS_CONVERTIBLE_WITHOUT_NARROWING
#define IG_TRANCE_TYPE_TRAITS_IS_CONVERTIBLE_WITHOUT_NARROWING

#include <trance/config.hpp>

// Narrowing conversion is only C++0x semantics.
// In C++03 environment, trance::is_convertible_without_narrowing works as boost::is_convertible.

#if defined( TRANCE_HAS_INITIALIZER_LISTS ) \
 && defined( TRANCE_HAS_UNIFIED_INITIALIZATION_SYNTAX ) \
 && defined( TRANCE_HAS_0X_HDR_INITIALIZER_LIST )
#   define TRANCE_DETAIL_ENABLE_CXX0X_NARROWING_CONVERSION
#   include <initializer_list>
#endif

#include TRANCE_TYPE_TRAITS_HDR

#include <boost/static_assert.hpp>

#include <boost/utility/declval.hpp>

#ifndef TRANCE_HAS_DECLTYPE
#   include <boost/mpl/bool.hpp>
#endif

namespace trance
{

#ifdef TRANCE_DETAIL_ENABLE_CXX0X_NARROWING_CONVERSION

namespace type_traits_detail
{

template < typename From, typename To >
struct _is_convable_wo_nc_impl
{
#ifdef TRANCE_HAS_DECLTYPE
    typedef TRANCE_TYPE_TRAITS_NAMESPACE::true_type  _true_type;
    typedef TRANCE_TYPE_TRAITS_NAMESPACE::false_type _false_type;
#else
    typedef char                          _true_type;
    typedef struct { char _unused[ 2 ]; } _false_type;
#endif

    template < typename >
    struct _protector
    {
        BOOST_STATIC_CONSTEXPR bool _m_stop = false;
    };

    template < typename U >
    static _true_type
    _m_check( ::std::initializer_list< To > ) TRANCE_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( _protector< U >::_m_stop && "_m_check() must not be used" );
        return _true_type();
    }

    template < typename U, typename T >
    static _false_type
    _m_check( ::std::initializer_list< T > ) TRANCE_NOEXCEPT
    {
        BOOST_STATIC_ASSERT( _protector< U >::_m_stop && "_m_check() must not be used" );
        return _false_type();
    }

#ifdef TRANCE_HAS_DECLTYPE
    typedef decltype( _m_check< int >( { ::boost::declval< From >() } ) ) type;
#else
    typedef boost::mpl::bool_< sizeof( _true_type ) == sizeof( _m_check< int >( { ::boost::declval< From >() } ) ) > type;
#endif

};

} // namespace type_traits_detail

template < typename From, typename To >
struct is_convertible_without_narrowing
  : public type_traits_detail::_is_convable_wo_nc_impl< From, To >::type {};

#else

template < typename From, typename To >
struct is_convertible_without_narrowing
  : public TRANCE_TYPE_TRAITS_NAMESPACE::is_convertible< From, To > {};

#endif // TRANCE_DETAIL_ENABLE_CXX0X_NARROWING_CONVERSION

} // namespace trance

#endif // IG_TRANCE_TYPE_TRAITS_IS_CONVERTIBLE_WITHOUT_NARROWING

