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

#define TRANCE_IOSTREAMS_MOVE_UPDOWN_MANIPS_INFO \
  ( "trance/iostreams/detail/string_manip.hpp",  \
    3,                                           \
    (                                            \
      ( move_down1, "D" ),                       \
      ( new_line  , "E" ),                       \
      ( move_up1  , "M" ))                       \
  )                                              \

namespace iostreams_detail
{

namespace _detail
{

#define ESC_SEQ_INITIALIZER_DEF( _unused_z, i_, _unused_param )   \
  template < typename CharTraits >                                \
  inline ::std::basic_ostream<                                    \
    TRANCE_IOSTREAMS_GET_CHAR_TYPE( i_ ),                         \
    CharTraits                                                    \
  > &                                                             \
  _esc_seq_initializer(                                           \
    ::std::basic_ostream<                                         \
      TRANCE_IOSTREAMS_GET_CHAR_TYPE( i_ ),                       \
      CharTraits                                                  \
    > &_ostr )                                                    \
  {                                                               \
      _ostr << TRANCE_IOSTREAMS_GET_CHAR_FORWARD( i_ )( '\x1b' ); \
      return _ostr;                                               \
  }                                                               \

BOOST_PP_REPEAT( TRANCE_IOSTREAMS_CHAR_TUPLE_SIZE, ESC_SEQ_INITIALIZER_DEF, _ )

#undef ESC_SEQ_INITIALIZER_DEF

// nothing to do
template < typename CharT, typename CharTraits >
inline ::std::basic_ostream< CharT, CharTraits > &
_esc_seq_finalizer( ::std::basic_ostream< CharT, CharTraits > &_ostr )
{ return _ostr; }

#define ENTRY_OPERATOR_DETAIL( _suf, _type, _forward )                     \
  template < typename CharTraits >                                         \
  ::std::basic_ostream< _type, CharTraits > &                              \
  operator()( ::std::basic_ostream< _type, CharTraits > &_ostr ) const     \
  { return _ostr << BOOST_PP_CAT( TRANCE_IOSTREAMS_, _forward )( _suf ); } \

#define ENTRY_IMPL( _entry, _char )                                  \
  struct _entry                                                      \
  {                                                                  \
      ENTRY_OPERATOR_DETAIL( _char, char    , CHAR_FORWARD     )     \
      ENTRY_OPERATOR_DETAIL( _char, wchar_t , WCHAR_T_FORWARD  )     \
      TRANCE_IOSTREAMS_ENABLE_IF_HAS_CHAR16_T(                       \
        ENTRY_OPERATOR_DETAIL( _char, char16_t, CHAR16_T_FORWARD ) ) \
      TRANCE_IOSTREAMS_ENABLE_IF_HAS_CHAR32_T(                       \
        ENTRY_OPERATOR_DETAIL( _char, char32_t, CHAR32_T_FORWARD ) ) \
  }                                                                  \

ENTRY_IMPL( _square_bracket, '[' );

ENTRY_IMPL( _put_A, 'A' );
ENTRY_IMPL( _put_B, 'B' );
ENTRY_IMPL( _put_C, 'C' );
ENTRY_IMPL( _put_D, 'D' );

#undef ENTRY_IMPL
#undef ENTRY_OPERATOR_DETAIL

inline size_t
_find_ntz( ::boost::uint8_t _x ) TRANCE_NOEXCEPT
{
    ::std::size_t i = 0;
    for ( ; !( _x & 1 ); ++i, _x >>= 1 );
    return i;
}

template < typename Attribute >
inline ::boost::uint8_t
_mask( typename Attribute::value_type _x ) TRANCE_NOEXCEPT
{ return _x & ( ( 1u << 8 ) - 1 ); }

#define INSERT_SEMICOLON_WHEN( begin, itr ) \
  if ( begin == itr ) {} else *itr++ = ';'

template < typename CharT >
inline void
_insert_when( ::boost::uint8_t pred,
  CharT * const begin, CharT *&itr, const CharT value ) TRANCE_NOEXCEPT
{
    if ( !pred )
    { return; }

    INSERT_SEMICOLON_WHEN( begin, itr );
    *itr++ = value;
    *itr++ = '0' + _find_ntz( pred );
}

} // namespace _detail

template < typename CharT, typename Traits, typename Attribute >
inline ::std::basic_ostream< CharT, Traits > &
operator<<( ::std::basic_ostream< CharT, Traits > &_ostr,
  const _attribute_forwarder< Attribute > &_af )
{
    CharT _buf[ 16 ] = { '\x1b', '[' };
    CharT *itr = _buf + 2;
    if ( _af._m_value == Attribute::reset )
    { *itr++ = '0'; }
    else
    {
        using namespace _detail;
        typedef ::boost::uint8_t mask_t( typename Attribute::value_type );
        mask_t &mask = _mask< Attribute >;

        if ( ::boost::uint8_t _tmp = mask( _af._m_value ) )
        {
            for ( CharT c = '1'; _tmp; _tmp >>= 1, ++c )
            {
                if ( _tmp & ~1 )
                { continue; }

                INSERT_SEMICOLON_WHEN( _buf, itr );
                *itr++ = c;
            }
        }
        _insert_when( mask( _af._m_value >>  8 ), _buf, itr, '3' );
        _insert_when( mask( _af._m_value >> 16 ), _buf, itr, '4' );
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

