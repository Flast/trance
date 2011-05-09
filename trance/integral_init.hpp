// trance integral_init.hpp - Initialized integral value
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

#ifndef IG_TRANCE_INTEGRAL_INIT_HPP_ONCE_
#define IG_TRANCE_INTEGRAL_INIT_HPP_ONCE_

#include <trance/config.hpp>

namespace trance
{

template < typename T, T _value >
struct integral_init
{
    typedef       T   value_type;
    typedef       T & reference;
    typedef const T & const_reference;

    value_type _M_value;

    TRANCE_CONSTEXPR
    integral_init( void )
      : _M_value( _value ) {};

    TRANCE_CONSTEXPR
    integral_init( const_reference value )
      : _M_value( value ) {};

    operator reference( void ) TRANCE_NOEXCEPT
    { return _M_value; }

    operator const_reference( void ) const TRANCE_NOEXCEPT
    { return _M_value; }
};

} // namespace trance

#endif // IG_TRANCE_INTEGRAL_INIT_HPP_ONCE_

