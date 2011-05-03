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

#if defined( BOOST_NO_CHAR16_T ) && defined( BOOST_NO_CHAR32_T )
// when C++03 mode
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 2
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  ( \
    TRANCE_IOSTREAMS_CHAR_PAIR, \
    TRANCE_IOSTREAMS_WCHAR_PAIR \
  ) \

#elif !defined( BOOST_NO_CHAR16_T ) && defined( BOOST_NO_CHAR32_T )
// when C++0x with char16_t
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 3
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  ( \
    TRANCE_IOSTREAMS_CHAR_PAIR,  \
    TRANCE_IOSTREAMS_WCHAR_PAIR, \
    TRANCE_IOSTREAMS_CHAR16_PAIR \
  ) \

#elif defined( BOOST_NO_CHAR16_T ) && !defined( BOOST_NO_CHAR32_T )
// when C++0x with char32_t
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 3
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  ( \
    TRANCE_IOSTREAMS_CHAR_PAIR,  \
    TRANCE_IOSTREAMS_WCHAR_PAIR, \
    TRANCE_IOSTREAMS_CHAR32_PAIR \
  ) \

#else
// when C++0x with both
#   define TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE 4
#   define TRANCE_IOSTREAMS_CHAR_TUPLE \
  ( \
    TRANCE_IOSTREAMS_CHAR_PAIR,   \
    TRANCE_IOSTREAMS_WCHAR_PAIR   \
    TRANCE_IOSTREAMS_CHAR16_PAIR, \
    TRANCE_IOSTREAMS_CHAR32_PAIR  \
  ) \

#endif // BOOST_NO_CHAR16_T && BOOST_NO_CHAR32_T

#endif // IG_TRANCE_IOSTREAMS_DETAIL_CONFIG_HPP_ONCE_

