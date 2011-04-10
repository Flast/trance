// trance safe_bool.hpp - Safely boolian type Library
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

#ifndef IG_TRANCE_SAFE_BOOL_HPP_ONCE_
#define IG_TRANCE_SAFE_BOOL_HPP_ONCE_

#include <trance/config.hpp>

namespace trance
{

namespace safe_bool_detail_
{

struct _safe_bool_impl
{
    void _dummy( void ) {};
};

typedef void ( _safe_bool_impl::*safe_bool_t )( void );

BOOST_STATIC_CONSTEXPR safe_bool_t safe_bool_true = &_safe_bool_impl::_dummy;
BOOST_STATIC_CONSTEXPR safe_bool_t safe_bool_false = 0;

} // namespace safe_bool_detail_

using safe_bool_detail_::safe_bool_t;
using safe_bool_detail_::safe_bool_true;
using safe_bool_detail_::safe_bool_false;

inline safe_bool_t
safe_bool( bool b ) TRANCE_NOEXCEPT
{ return b ? safe_bool_true : safe_bool_false; }

} // namespace trance

#endif // IG_TRANCE_SAFE_BOOL_HPP_ONCE_

