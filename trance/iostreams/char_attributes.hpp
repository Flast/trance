// trance char_attributes.hpp - Character Attributes Manipulator
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

#ifndef IG_TRANCE_IOSTREAMS_CHAR_ATTRIBUTES_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_CHAR_ATTRIBUTES_HPP_ONCE_

#include <trance/config.hpp>
#include <trance/iostreams/detail/config.hpp>

namespace trance
{

namespace iostreams
{

struct attribute
{
    typedef ::boost::uint32_t value_type;

    BOOST_STATIC_CONSTEXPR value_type reset = ~static_cast< value_type >( 0u ); // [0m

    BOOST_STATIC_CONSTEXPR value_type highlight = 1u << 0; // [1m
    //BOOST_STATIC_CONSTEXPR value_type ???       = 1u << 1; // [2m
    BOOST_STATIC_CONSTEXPR value_type underline = 1u << 3; // [4m
    BOOST_STATIC_CONSTEXPR value_type blink     = 1u << 4; // [5m
    BOOST_STATIC_CONSTEXPR value_type inverse   = 1u << 6; // [7m
    BOOST_STATIC_CONSTEXPR value_type invisible = 1u << 7; // [8m or [16m
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

inline iostreams_detail::_attribute_forwarder< attribute >
chattr( attribute::value_type attr = attribute::reset ) TRANCE_NOEXCEPT
{
    const iostreams_detail::_attribute_forwarder< attribute > _attr = { attr };
    return _attr;
}

} // namespace iostreams

} // namespace trance

#endif // IG_TRANCE_IOSTREAMS_CHAR_ATTRIBUTES_HPP_ONCE_

