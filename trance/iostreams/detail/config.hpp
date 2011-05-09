// trance config.hpp - Configuration for Espace Sequence
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

#ifndef IG_TRANCE_IOSTREAMS_DETAIL_CONFIG_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_DETAIL_CONFIG_HPP_ONCE_

#include <trance/config.hpp>

#include <boost/cstdint.hpp>

#include <boost/type_traits/function_traits.hpp>

#if defined( linux )     \
 || defined( __linux )   \
 || defined( __linux__ ) \
 || defined( __GNU__ )   \
 || defined( __GLIBC__ ) \
// when Linux
#   define TRANCE_IOSTREAMS_CONFIG_PLATFORM "trance/iostreams/detail/linux.hpp"
#elif defined( __CYGWIN__ )
// when Cygwin
#   define TRANCE_IOSTREAMS_CONFIG_PLATFORM "trance/iostreams/detail/cygwin.hpp"
#elif defined( _WIN32 )    \
   || defined( __WIN32__ ) \
   || defined( WIN32 )     \
// when Windows
#   define TRANCE_IOSTREAMS_CONFIG_PLATFORM "trance/iostreams/detail/windows.hpp"
#endif

#define TRANCE_IOSTREAMS_CHAR_FORWARD( _str )     _str
#define TRANCE_IOSTREAMS_WCHAR_T_FORWARD( _str )  BOOST_PP_CAT( L, _str )
#define TRANCE_IOSTREAMS_CHAR16_T_FORWARD( _str ) BOOST_PP_CAT( u, _str )
#define TRANCE_IOSTREAMS_CHAR32_T_FORWARD( _str ) BOOST_PP_CAT( U, _str )

#define TRANCE_IOSTREAMS_CHAR_PAIR   ( char    , TRANCE_IOSTREAMS_CHAR_FORWARD     )
#define TRANCE_IOSTREAMS_WCHAR_PAIR  ( wchar_t , TRANCE_IOSTREAMS_WCHAR_T_FORWARD  )
#define TRANCE_IOSTREAMS_CHAR16_PAIR ( char16_t, TRANCE_IOSTREAMS_CHAR16_T_FORWARD )
#define TRANCE_IOSTREAMS_CHAR32_PAIR ( char32_t, TRANCE_IOSTREAMS_CHAR32_T_FORWARD )

#if !defined( TRANCE_HAS_CHAR16_T ) && !defined( TRANCE_HAS_CHAR32_T )
// when C++03 mode
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 2
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  (                                    \
    TRANCE_IOSTREAMS_CHAR_PAIR,        \
    TRANCE_IOSTREAMS_WCHAR_PAIR        \
  )                                    \

#elif defined( TRANCE_HAS_CHAR16_T ) && !defined( TRANCE_HAS_CHAR32_T )
// when C++0x with char16_t
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 3
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  (                                    \
    TRANCE_IOSTREAMS_CHAR_PAIR,        \
    TRANCE_IOSTREAMS_WCHAR_PAIR,       \
    TRANCE_IOSTREAMS_CHAR16_PAIR       \
  )                                    \

#elif !defined( TRANCE_HAS_CHAR16_T ) && defined( TRANCE_HAS_CHAR32_T )
// when C++0x with char32_t
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 3
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  (                                    \
    TRANCE_IOSTREAMS_CHAR_PAIR,        \
    TRANCE_IOSTREAMS_WCHAR_PAIR,       \
    TRANCE_IOSTREAMS_CHAR32_PAIR       \
  )                                    \

#else
// when C++0x with both
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 4
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  (                                    \
    TRANCE_IOSTREAMS_CHAR_PAIR,        \
    TRANCE_IOSTREAMS_WCHAR_PAIR,       \
    TRANCE_IOSTREAMS_CHAR16_PAIR,      \
    TRANCE_IOSTREAMS_CHAR32_PAIR       \
  )                                    \

#endif // TRANCE_HAS_CHAR16_T && TRANCE_HAS_CHAR32_T

#define TRANCE_IOSTREAMS_GET_CHAR_PAIR( i_ ) \
  BOOST_PP_TUPLE_ELEM(                       \
    TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE,        \
    i_,                                      \
    TRANCE_IOSTREAMS_CHAR_TUPLE )            \

#define TRANCE_IOSTREAMS_GET_CHAR_TYPE( i_ ) \
  BOOST_PP_TUPLE_ELEM( 2, 0, TRANCE_IOSTREAMS_GET_CHAR_PAIR( i_ ) )
#define TRANCE_IOSTREAMS_GET_CHAR_FORWARD( i_ ) \
  BOOST_PP_TUPLE_ELEM( 2, 1, TRANCE_IOSTREAMS_GET_CHAR_PAIR( i_ ) )

namespace trance
{

namespace iostreams
{

namespace iostreams_detail
{

struct _attribute_forwarder
{
    typedef ::boost::uint32_t value_type;

    value_type _M_value;
};

namespace _param_detail
{

#define TRANCE_IOSTREAMS_MANIP_LAMBDA                \
  iostreams_detail::_param_detail::_param_manip_impl \

template <
  typename _Param,
  //typename _Delimiter,
  typename _Prefixer,
  typename _Suffixer
>
struct _param_manip_impl
{
    _Param     _M_param;
    //_Delimiter _M_delimiter;
    _Prefixer _M_pref;
    _Suffixer _M_suf;

    explicit
    _param_manip_impl( const _Param &_x )
      : _M_param( _x ), //_M_delimiter(),
        _M_pref(), _M_suf() {}

    _param_manip_impl( const _Param &_x, //_Delimiter _delim,
      _Prefixer _pref, _Suffixer _suf )
      : _M_param( _x ), //_M_delimiter( _delim ),
        _M_pref( _pref ), _M_suf( _suf ) {}
};

} // namespace _param_detail

} // namespace iostreams_detail

} // namespace iostreams

} // namespace trance

#include TRANCE_IOSTREAMS_CONFIG_PLATFORM

#endif // IG_TRANCE_IOSTREAMS_DETAIL_CONFIG_HPP_ONCE_

