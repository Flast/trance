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

#ifdef STRING_MANIP_RECURSIVE

#define j_ BOOST_PP_FRAME_ITERATION( 2 )

#define CHAR_TYPE_PAIR BOOST_PP_TUPLE_ELEM( CHAR_TUPLE_SIZE, j_, CHAR_TUPLE )
#define CHAR_TYPE      BOOST_PP_TUPLE_ELEM( 2, 0, CHAR_TYPE_PAIR )
#define CHAR_PREFIX    BOOST_PP_TUPLE_ELEM( 2, 1, CHAR_TYPE_PAIR )

#define OSTREAM( _Traits ) ::std::basic_ostream< CHAR_TYPE, _Traits >

template < typename _CharTraits >
inline OSTREAM( _CharTraits ) &
MANIP_NAME( OSTREAM( _CharTraits ) &_ostr ) TRANCE_NOEXCEPT
{
    _ostr <<
      CHAR_PREFIX( "\x1b" )
      CHAR_PREFIX( MANIP );
    return _ostr;
}

#undef OSTREAM

#undef CHAR_PREFIX
#undef CHAR_TYPE
#undef CHAR_TYPE_PAIR

#undef j_

#else // STRING_MANIP_RECURSIVE

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define i_ BOOST_PP_FRAME_ITERATION( 1 )
#define STRING_MANIP_RECURSIVE

#define CURRENT_PAIR BOOST_PP_TUPLE_ELEM( STRING_MANIPS_COUNT, i_, STRING_MANIPS )
#define MANIP_NAME   BOOST_PP_TUPLE_ELEM( 2, 0, CURRENT_PAIR )
#define MANIP        BOOST_PP_TUPLE_ELEM( 2, 1, CURRENT_PAIR )

#define CHAR_TUPLE_SIZE TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE
#define CHAR_TUPLE      TRANCE_IOSTREAMS_CHAR_TUPLE

#define BOOST_PP_ITERATION_PARAMS_2 ( 3, ( \
  0, \
  BOOST_PP_DEC( CHAR_TUPLE_SIZE ), \
  "trance/iostreams/detail/string_manip.hpp" ) )
#include BOOST_PP_ITERATE()

#undef CHAR_TUPLE
#undef CHAR_TUPLE_SIZE

#undef MANIP
#undef MANIP_NAME
#undef CURRENT_PAIR

#undef STRING_MANIP_RECURSIVE
#undef i_

#endif // STRING_MANIP_RECURSIVE

