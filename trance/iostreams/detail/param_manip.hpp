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

#ifndef BOOST_PP_IS_ITERATING
#   error "detail/param_manip.hpp should not include directly."
#endif

#if BOOST_PP_ITERATION_DEPTH() == 1

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#define i_ BOOST_PP_FRAME_ITERATION( 1 )

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

#define OSTREAM( n_, Traits )             \
  ::std::basic_ostream<                   \
    TRANCE_IOSTREAMS_GET_CHAR_TYPE( n_ ), \
    Traits                                \
  >                                       \

#define BOOST_PP_LOCAL_LIMITS \
  ( 0, BOOST_PP_DEC( TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE ) )
#define BOOST_PP_LOCAL_MACRO( n_ )                          \
  template < typename CharTraits >                          \
  inline OSTREAM( n_, CharTraits ) &                        \
  operator<<(                                               \
    OSTREAM( n_, CharTraits ) &_ostr                        \
  , const MANIP_NAME &_param )                              \
  {                                                         \
      namespace iostreams = ::trance::iostreams;            \
      using namespace iostreams::iostreams_detail::_detail; \
      _esc_seq_initializer( _ostr );                        \
        _param._m_pref( _ostr );                            \
          _ostr << _param._m_param;                         \
        _param._m_suf( _ostr );                             \
      _esc_seq_finalizer( _ostr );                          \
      return _ostr;                                         \
  }                                                         \

#include BOOST_PP_LOCAL_ITERATE()

#undef OSTREAM

} // namespace _param_detail

} // namespace iostreams_detail

#undef MANIP_TYPE
#undef MANIP_NAME
#undef CURRENT_PAIR

#undef i_

#endif // BOOST_PP_ITERATION_DEPTH

