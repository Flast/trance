// trance linux.hpp - Configuration for Linux
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

#ifndef IG_TRANCE_IOSTREAMS_DETAIL_LINUX_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_DETAIL_LINUX_HPP_ONCE_

#include <trance/config.hpp>

#include <cstddef>
#include <iosfwd>

#include <boost/cstdint.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

namespace trance
{

namespace iostreams
{

#define TRANCE_IOSTREAMS_CLEAR_MANIPS_INFO      \
  ( "trance/iostreams/detail/string_manip.hpp", \
    6,                                          \
    (                                           \
      ( clear_below, "[0J" ),                   \
      ( clear_above, "[1J" ),                   \
      ( clear      , "[2J" ),                   \
      ( clear_right, "[0K" ),                   \
      ( clear_left , "[1K" ),                   \
      ( clear_line , "[2K" ))                   \
  )                                             \

#define TRANCE_IOSTREAMS_MOVE_IMPL( _suf )      \
  TRANCE_IOSTREAMS_MANIP_LAMBDA<                \
    unsigned int,                               \
    iostreams_detail::_detail::_square_bracket, \
    iostreams_detail::_detail::_suf             \
  >                                             \

#define TRANCE_IOSTREAMS_MOVE_1DIM_MANIPS_INFO                \
  ( "trance/iostreams/detail/param_manip.hpp",                \
    4,                                                        \
    (                                                         \
      ( move_up   , (TRANCE_IOSTREAMS_MOVE_IMPL( _put_A )) ), \
      ( move_down , (TRANCE_IOSTREAMS_MOVE_IMPL( _put_B )) ), \
      ( move_right, (TRANCE_IOSTREAMS_MOVE_IMPL( _put_C )) ), \
      ( move_left , (TRANCE_IOSTREAMS_MOVE_IMPL( _put_D )) )) \
  )                                                           \

namespace iostreams_detail
{

namespace _detail
{

#define ESC_SEQ_INITIALIZER_DEF( _unused_z, i_, _unused_param )   \
  template < typename _CharTraits >                               \
  inline ::std::basic_ostream<                                    \
    TRANCE_IOSTREAMS_GET_CHAR_TYPE( i_ ),                         \
    _CharTraits                                                   \
  > &                                                             \
  _esc_seq_initializer(                                           \
    ::std::basic_ostream<                                         \
      TRANCE_IOSTREAMS_GET_CHAR_TYPE( i_ ),                       \
      _CharTraits                                                 \
    > &_ostr )                                                    \
  {                                                               \
      _ostr << TRANCE_IOSTREAMS_GET_CHAR_FORWARD( i_ )( '\x1b' ); \
      return _ostr;                                               \
  }                                                               \

BOOST_PP_REPEAT( TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE, ESC_SEQ_INITIALIZER_DEF, _ )

#undef ESC_SEQ_INITIALIZER_DEF

// nothing to do
template < typename _CharT, typename _CharTraits >
inline ::std::basic_ostream< _CharT, _CharTraits > &
_esc_seq_finalizer( ::std::basic_ostream< _CharT, _CharTraits > &_ostr )
{ return _ostr; }

#define _ENTRY_OPERATOR_DETAIL( _suf, _type, _forward )                    \
  template < typename _CharTraits >                                        \
  ::std::basic_ostream< _type, _CharTraits > &                             \
  operator()( ::std::basic_ostream< _type, _CharTraits > &_ostr ) const    \
  { return _ostr << BOOST_PP_CAT( TRANCE_IOSTREAMS_, _forward )( _suf ); } \

#if !defined( TRANCE_HAS_CHAR16_T ) && !defined( TRANCE_HAS_CHAR32_T )
// when C++03 mode
#define _ENTRY_IMPL( _entry, _char )                              \
  struct _entry                                                   \
  {                                                               \
      _ENTRY_OPERATOR_DETAIL( _char, char    , CHAR_FORWARD     ) \
      _ENTRY_OPERATOR_DETAIL( _char, wchar_t , WCHAR_T_FORWARD  ) \
  }                                                               \

#elif defined( TRANCE_HAS_CHAR16_T ) && !defined( TRANCE_HAS_CHAR32_T )
// when C++0x with char16_t
#define _ENTRY_IMPL( _entry, _char )                              \
  struct _entry                                                   \
  {                                                               \
      _ENTRY_OPERATOR_DETAIL( _char, char    , CHAR_FORWARD     ) \
      _ENTRY_OPERATOR_DETAIL( _char, wchar_t , WCHAR_T_FORWARD  ) \
      _ENTRY_OPERATOR_DETAIL( _char, char16_t, CHAR16_T_FORWARD ) \
  }                                                               \

#elif !defined( TRANCE_HAS_CHAR16_T ) && defined( TRANCE_HAS_CHAR32_T )
// when C++0x with char32_t
#define _ENTRY_IMPL( _entry, _char )                              \
  struct _entry                                                   \
  {                                                               \
      _ENTRY_OPERATOR_DETAIL( _char, char    , CHAR_FORWARD     ) \
      _ENTRY_OPERATOR_DETAIL( _char, wchar_t , WCHAR_T_FORWARD  ) \
      _ENTRY_OPERATOR_DETAIL( _char, char32_t, CHAR32_T_FORWARD ) \
  }                                                               \

#else
// when C++0x with both
#define _ENTRY_IMPL( _entry, _char )                              \
  struct _entry                                                   \
  {                                                               \
      _ENTRY_OPERATOR_DETAIL( _char, char    , CHAR_FORWARD     ) \
      _ENTRY_OPERATOR_DETAIL( _char, wchar_t , WCHAR_T_FORWARD  ) \
      _ENTRY_OPERATOR_DETAIL( _char, char16_t, CHAR16_T_FORWARD ) \
      _ENTRY_OPERATOR_DETAIL( _char, char32_t, CHAR32_T_FORWARD ) \
  }                                                               \

#endif // TRANCE_HAS_CHAR16_T && TRANCE_HAS_CHAR32_T

_ENTRY_IMPL( _square_bracket, '[' );

_ENTRY_IMPL( _put_A, 'A' );
_ENTRY_IMPL( _put_B, 'B' );
_ENTRY_IMPL( _put_C, 'C' );
_ENTRY_IMPL( _put_D, 'D' );

#undef _ENTRY_IMPL
#undef _ENTRY_OPERATOR_DETAIL

inline size_t
_find_ntz( ::boost::uint8_t _x ) TRANCE_NOEXCEPT
{
    ::std::size_t i = 0;
    for ( ; !( _x & 1 ); ++i, _x >>= 1 );
    return i;
}

inline ::boost::uint8_t
_mask( _attribute_forwarder::value_type _x ) TRANCE_NOEXCEPT
{ return _x & ( ( 1u << 8 ) - 1 ); }

#define INSERT_SEMICOLON_WHEN( begin, itr ) \
  if ( begin == itr ) {} else *itr++ = ';'

template < typename _CharT >
inline void
_insert_when( ::boost::uint8_t pred,
  _CharT * const begin, _CharT *&itr, const _CharT value ) TRANCE_NOEXCEPT
{
    if ( !pred )
    { return; }

    INSERT_SEMICOLON_WHEN( begin, itr );
    *itr++ = value;
    *itr++ = '0' + _find_ntz( pred );
}

} // namespace _detail

template < typename _CharT, typename _Traits >
inline ::std::basic_ostream< _CharT, _Traits > &
operator<<( ::std::basic_ostream< _CharT, _Traits > &_ostr,
  const _attribute_forwarder &_af )
{
    _CharT _buf[ 16 ] = { '\x1b', '[' };
    _CharT *itr = _buf + 2;
    //if ( _af._M_value == attribute::reset )
    //{ *itr++ = '0'; }
    //else
    {
        using namespace _detail;
        if ( ::boost::uint8_t _tmp = _mask( _af._M_value ) )
        {
            for ( _CharT c = '1'; _tmp; _tmp >>= 1, ++c )
            {
                if ( _tmp & ~1 )
                { continue; }

                INSERT_SEMICOLON_WHEN( _buf, itr );
                *itr++ = c;
            }
        }
        _insert_when( _mask( _af._M_value >>  8 ), _buf, itr, '3' );
        _insert_when( _mask( _af._M_value >> 16 ), _buf, itr, '4' );
    }

    *itr = 'm';
    _ostr << _buf;
    return _ostr;
}
#undef INSERT_SEMICOLON_WHEN

} // namespace iostreams_detail

} // namespace iostreams

} // namespace trance

#endif // IG_TRANCE_IOSTREAMS_DETAIL_LINUX_HPP_ONCE_

