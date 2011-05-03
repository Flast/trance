// trance param_manip.hpp - Parameter based manipulator
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

#ifdef PARAM_MANIP_RECURSIVE

#define j_ BOOST_PP_FRAME_ITERATION( 2 )

#define CHAR_TYPE_PAIR BOOST_PP_TUPLE_ELEM( CHAR_TUPLE_SIZE, j_, CHAR_TUPLE )
#define CHAR_TYPE      BOOST_PP_TUPLE_ELEM( 2, 0, CHAR_TYPE_PAIR )
#define CHAR_PREFIX    BOOST_PP_TUPLE_ELEM( 2, 1, CHAR_TYPE_PAIR )

#define OSTREAM( _Traits ) ::std::basic_ostream< CHAR_TYPE, _Traits >

template < typename _CharTraits, TRANCE_IOSTREAMS_PARAM_TEMPLATE_LIST >
inline OSTREAM( _CharTraits ) &
operator<<( OSTREAM( _CharTraits ) &_ostr,
  const _param_manip_impl< TRANCE_IOSTREAMS_PARAM_TEMPLATE_ARGS > &_param )
{
    _ostr << CHAR_PREFIX( "\x1b" );
    _param._M_pref( _ostr );
    _ostr << _param._M_param;
    _param._M_suf( _ostr );
    return _ostr;
}

#undef OSTREAM

#undef CHAR_PREFIX
#undef CHAR_TYPE
#undef CHAR_TYPE_PAIR

#undef j_

#else // PARAM_MANIP_RECURSIVE

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define i_ BOOST_PP_FRAME_ITERATION( 1 )
#define PARAM_MANIP_RECURSIVE

#define CURRENT_PAIR               \
  BOOST_PP_TUPLE_ELEM(             \
    TRANCE_IOSTREAMS_MANIPS_COUNT, \
    i_,                            \
    TRANCE_IOSTREAMS_MANIPS )      \

#define MANIP_NAME BOOST_PP_TUPLE_ELEM( 2, 0, CURRENT_PAIR )
#define MANIP_TYPE BOOST_PP_TUPLE_ELEM( 2, 1, CURRENT_PAIR )

typedef ::boost::function_traits< void MANIP_TYPE >::arg1_type MANIP_NAME;

namespace iostreams_detail
{

namespace _param_detail
{

#define CHAR_TUPLE_SIZE TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE
#define CHAR_TUPLE      TRANCE_IOSTREAMS_CHAR_TUPLE

#define BOOST_PP_ITERATION_PARAMS_2 ( 3, ( \
  0, \
  BOOST_PP_DEC( CHAR_TUPLE_SIZE ), \
  "trance/iostreams/detail/param_manip.hpp" ) )
#include BOOST_PP_ITERATE()

} // namespace _param_detail

} // namespace iostreams_detail

#undef CHAR_TUPLE
#undef CHAR_TUPLE_SIZE

#undef MANIP_TYPE
#undef MANIP_NAME
#undef CURRENT_PAIR

#undef PARAM_MANIP_RECURSIVE
#undef i_

#endif // PARAM_MANIP_RECURSIVE

