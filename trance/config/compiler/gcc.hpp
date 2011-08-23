// trance gcc.hpp - GCC Local Configuration Library
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

#ifndef IG_TRANCE_CONFIG_COMPILER_GCC_HPP_ONCE_
#define IG_TRANCE_CONFIG_COMPILER_GCC_HPP_ONCE_

#define TRANCE_CONFIG_GCC_MODE
#define TRANCE_ATTRIBUTE_WHEN_GCC( _attributes ) __attribute__( _attributes )

#if __GNUC__ > 2 || ( __GNUC__ == 2 && __GNUC_MINOR__ >= 95 )
// All of GCC (2.95 or later) support noreturn.
#   define TRANCE_ATTRIBUTE_NORETURN __attribute__((noreturn))

// XXX: No documentation for first supported version.
#   define TRANCE_ATTRIBUTE_DLL( _spec ) __attribute__((BOOST_PP_CAT( dll, _spec )))
#endif

// All of GCC (3.3 or later) support nothrow.
#if __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3 )
#   define TRANCE_ATTRIBUTE_NOTHROW __attribute__((nothrow))
#endif

#if __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ >= 5 )
#   define TRANCE_UNREACHABLE_HERE __builtin_unreacheable
#endif

#endif // IG_TRANCE_CONFIG_COMPILER_GCC_HPP_ONCE_

