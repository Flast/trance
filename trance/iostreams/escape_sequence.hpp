// trance escape_sequence.hpp - Generic Escape Sequence Manipulator
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

#ifndef IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_

#include <trance/config.hpp>

#include <iosfwd>

#include <boost/cstdint.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iterate.hpp>

namespace trance
{

namespace iostreams
{

#define STRING_MANIPS_COUNT 6
#define STRING_MANIPS      \
  (                        \
    ( clear_below, "[0J" ), \
    ( clear_above, "[1J" ), \
    ( clear      , "[2J" ), \
    ( clear_right, "[0K" ), \
    ( clear_left , "[1K" ), \
    ( clear_line , "[2K" ), \
())                        \

#define BOOST_PP_ITERATION_PARAMS_1 \
  ( 3, ( 0, BOOST_PP_DEC( STRING_MANIPS_COUNT ), <trance/iostreams/detail/manip_string.hpp> ) )
#include BOOST_PP_ITERATE()
#undef STRING_MANIPS
#undef STRING_MANIPS_COUNT

struct attribute
{
    typedef ::boost::uint32_t value_type;

    BOOST_STATIC_CONSTEXPR value_type reset = ~static_cast< ::boost::uint32_t >( 0u ); // [0m

    BOOST_STATIC_CONSTEXPR value_type highlight = 1u << 0; // [1m
    //BOOST_STATIC_CONSTEXPR value_type ???       = 1u << 1; // [2m
    BOOST_STATIC_CONSTEXPR value_type underline = 1u << 3; // [4m
    //BOOST_STATIC_CONSTEXPR value_type blink     = 1u << 4; // [5m
    BOOST_STATIC_CONSTEXPR value_type inverse   = 1u << 6; // [7m
    //BOOST_STATIC_CONSTEXPR value_type invisible = 1u << 7; // [8m or [16m
    BOOST_STATIC_CONSTEXPR value_type _effect_mask = ( 1u << 8 ) - 1;

    BOOST_STATIC_CONSTEXPR value_type black  = 1u <<  8; // [30m
    BOOST_STATIC_CONSTEXPR value_type red    = 1u <<  9; // [31m or [17m
    BOOST_STATIC_CONSTEXPR value_type green  = 1u << 10; // [32m or [18m
    BOOST_STATIC_CONSTEXPR value_type yellow = 1u << 11; // [33m or [19m
    BOOST_STATIC_CONSTEXPR value_type blue   = 1u << 12; // [34m or [20m
    BOOST_STATIC_CONSTEXPR value_type purple = 1u << 13; // [35m or [21m
    BOOST_STATIC_CONSTEXPR value_type cyan   = 1u << 14; // [36m or [22m
    BOOST_STATIC_CONSTEXPR value_type white  = 1u << 15; // [37m or [23m
    BOOST_STATIC_CONSTEXPR value_type _color_mask = ( ( 1u << 8 ) - 1 ) << 8;

    BOOST_STATIC_CONSTEXPR value_type back_black  = 1u << 16; // [40m
    BOOST_STATIC_CONSTEXPR value_type back_red    = 1u << 17; // [41m
    BOOST_STATIC_CONSTEXPR value_type back_green  = 1u << 18; // [42m
    BOOST_STATIC_CONSTEXPR value_type back_yellow = 1u << 19; // [43m
    BOOST_STATIC_CONSTEXPR value_type back_blue   = 1u << 20; // [44m
    BOOST_STATIC_CONSTEXPR value_type back_purple = 1u << 21; // [45m
    BOOST_STATIC_CONSTEXPR value_type back_cyan   = 1u << 22; // [46m
    BOOST_STATIC_CONSTEXPR value_type back_white  = 1u << 23; // [47m
    BOOST_STATIC_CONSTEXPR value_type _backcolor_mask = ( ( 1u << 8 ) - 1 ) << 16;
};

namespace iostreams_detail
{

struct _attribute_forwarder
{ attribute::value_type _M_value; };

inline size_t
_find_ntz( ::boost::uint8_t _x ) TRANCE_NOEXCEPT
{
    ::std::size_t i = 0;
    for ( ; !( _x & 1 ); ++i, _x >>= 1 );
    return i;
}

inline ::boost::uint8_t
_mask( attribute::value_type _x ) TRANCE_NOEXCEPT
{ return _x & ( ( 1u << 8 ) - 1 ); }

#define INSERT_SEMICOLON_WHEN( begin, itr ) \
  if ( begin == itr ) {} else *itr++ =';'

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

template < typename _CharT, typename _Traits >
inline ::std::basic_ostream< _CharT, _Traits > &
operator<<( ::std::basic_ostream< _CharT, _Traits > &_ostr,
  const _attribute_forwarder &_af ) TRANCE_NOEXCEPT
{
    _CharT _buf[ 16 ] = { '\x1b', '[' };
    _CharT *itr = _buf + 2;
    if ( _af._M_value == attribute::reset )
    { *itr++ = '0'; }
    else
    {
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

} // iostreams_detail

inline iostreams_detail::_attribute_forwarder
chattr( attribute::value_type attr = attribute::reset ) TRANCE_NOEXCEPT
{ return { attr }; }

} // namespace iostreams

} // namespace trance


#endif // IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_

