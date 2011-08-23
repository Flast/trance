// trance default.hpp - Compiler Default Configuration Library
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

#ifndef IG_TRANCE_CONFIG_COMPILER_DEFAULT_HPP_ONCE_
#define IG_TRANCE_CONFIG_COMPILER_DEFAULT_HPP_ONCE_

#ifndef TRANCE_ATTRIBUTE_WHEN_GCC
#   define TRANCE_ATTRIBUTE_WHEN_GCC( _attributes )
#endif
#ifndef TRANCE_ATTRIBUTE_WHEN_MSVC
#   define TRANCE_ATTRIBUTE_WHEN_MSVC( _attributes )
#endif

#ifndef TRANCE_ATTRIBUTE_NORETURN
#   define TRANCE_ATTRIBUTE_NORETURN
#endif

#ifndef TRANCE_ATTRIBUTE_DLL
#   define TRANCE_ATTRIBUTE_DLL( _spec )
#endif

#ifndef TRANCE_ATTRIBUTE_NOTHROW
#   define TRANCE_ATTRIBUTE_NOTHROW
#endif

#ifndef TRANCE_UNREACHABLE_HERE
namespace trance
{
namespace detail
{
inline void TRANCE_ATTRIBUTE_NORETURN
_unreacheable( void )
{ *reinterpret_cast< int * >( 0 ) = 0; }
} // namespace detail
} // namespace trance
// Force SEGV
#   define TRANCE_UNREACHABLE_HERE ::trance::detail::_unreacheable
#endif

#endif // IG_TRANCE_CONFIG_COMPILER_DEFAULT_HPP_ONCE_

