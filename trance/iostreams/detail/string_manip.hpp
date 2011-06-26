// trance string_manip.hpp - String based manipulator
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

#ifndef BOOST_PP_IS_ITERATING
#   error "detail/string_manip.hpp should not include directly."
#endif

#if BOOST_PP_ITERATION_DEPTH() == 1

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#define i_ BOOST_PP_FRAME_ITERATION( 1 )

#define CURRENT_PAIR               \
  BOOST_PP_TUPLE_ELEM(             \
    TRANCE_IOSTREAMS_MANIPS_COUNT, \
    i_,                            \
    TRANCE_IOSTREAMS_MANIPS )      \

#define MANIP_NAME BOOST_PP_TUPLE_ELEM( 2, 0, CURRENT_PAIR )
#define MANIP      BOOST_PP_TUPLE_ELEM( 2, 1, CURRENT_PAIR )

#define OSTREAM( n_, _Traits )            \
  ::std::basic_ostream<                   \
    TRANCE_IOSTREAMS_GET_CHAR_TYPE( n_ ), \
    _Traits                               \
  >                                       \

#define BOOST_PP_LOCAL_LIMITS \
  ( 0, BOOST_PP_DEC( TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE ) )
#define BOOST_PP_LOCAL_MACRO( n_ )                                  \
  template < typename _CharTraits >                                 \
  inline OSTREAM( n_, _CharTraits ) &                               \
  MANIP_NAME( OSTREAM( n_, _CharTraits ) &_ostr )                   \
  {                                                                 \
      namespace iostreams = ::trance::iostreams;                    \
      using namespace iostreams::iostreams_detail::_detail;         \
      _esc_seq_initializer( _ostr );                                \
        _ostr << TRANCE_IOSTREAMS_GET_CHAR_FORWARD( n_ )( MANIP );  \
      _esc_seq_finalizer( _ostr );                                  \
      return _ostr;                                                 \
  }                                                                 \

#include BOOST_PP_LOCAL_ITERATE()

#undef OSTREAM

#undef MANIP
#undef MANIP_NAME
#undef CURRENT_PAIR

#undef i_

#endif // BOOST_PP_ITERATION_DEPTH

