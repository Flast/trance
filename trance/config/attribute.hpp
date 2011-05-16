// trance config.hpp - Compiler Attribute Configuration Library
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

#ifndef IG_TRANCE_CONFIG_ATTRIBUTE_HPP_ONCE_
#define IG_TRANCE_CONFIG_ATTRIBUTE_HPP_ONCE_

#include <boost/preprocessor/cat.hpp>

#if defined( __GNUC__ ) && defined( __GNUC_MINOR__ )
#   define TRANCE_CONFIG_GCC_MODE
#   define TRANCE_ATTRIBUTE_WHEN_GCC( _attributes ) __attribute__( _attributes )
#elif defined( _MSC_VER )
#   define TRANCE_CONFIG_MSVC_MODE
#   define TRANCE_ATTRIBUTE_WHEN_MSVC( _attributes ) __declspec _attributes
#endif

#ifndef TRANCE_ATTRIBUTE_WHEN_GCC
#   define TRANCE_ATTRIBUTE_WHEN_GCC( _attributes )
#endif
#ifndef TRANCE_ATTRIBUTE_WHEN_MSVC
#   define TRANCE_ATTRIBUTE_WHEN_MSVC( _attributes )
#endif

// noreturn attribute

#if defined( TRANCE_CONFIG_GCC_MODE )
// All of GCC (2.95 or later) support noreturn.
#   if __GNUC__ > 2 || ( __GNUC__ == 2 && __GNUC_MINOR__ >= 95 )
#       define TRANCE_ATTRIBUTE_NORETURN __attribute__((noreturn))
#   endif

#elif defined( TRANCE_CONFIG_MSVC_MODE )
// Visual C++ .NET 2003 or later support noreturn and documented.
#   if _MSC_VER >= 1310
#       define TRANCE_ATTRIBUTE_NORETURN __declspec(noreturn)
#   endif

#endif
// Unknown compiler or unsupported.
#ifndef TRANCE_ATTRIBUTE_NORETURN
#   define TRANCE_ATTRIBUTE_NORETURN
#endif

// DLL import/export attribute

#if defined( TRANCE_CONFIG_GCC_MODE )
// XXX: No documentation for first supported version.
#   if __GNUC__ > 2 || ( __GNUC__ == 2 && __GNUC_MINOR__ >= 95 )
#       define TRANCE_ATTRIBUTE_DLL( _spec ) __attribute__((BOOST_PP_CAT( dll, _spec )))
#   endif

#elif defined( TRANCE_CONFIG_MSVC_MODE )
// Visual C++ .NET 2003 or later support and documented.
#   if _MSC_VER >= 1310
#       define TRANCE_ATTRIBUTE_DLL( _spec ) __declspec(BOOST_PP_CAT( dll, _spec ))
#   endif

#endif
// Unknown compiler or unsupported.
#ifndef TRANCE_ATTRIBUTE_DLL
#   define TRANCE_ATTRIBUTE_DLL( _spec )
#endif

// nothrow attribute

#if defined( TRANCE_CONFIG_GCC_MODE )
// All of GCC (3.3 or later) support nothrow.
#   if __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3 )
#       define TRANCE_ATTRIBUTE_NOTHROW __attribute__((nothrow))
#   endif

#elif defined( TRANCE_CONFIG_MSVC_MODE )
// Visual C++ .NET 2003 or later support and documented.
#   if _MSC_VER >= 1310
#       define TRANCE_ATTRIBUTE_NOTHROW __declspec(nothrow)
#   endif

#endif
// Unknown compiler or unsupported.
#ifndef TRANCE_ATTRIBUTE_NOTHROW
#   define TRANCE_ATTRIBUTE_NOTHROW
#endif

#endif // IG_TRANCE_CONFIG_ATTRIBUTE_HPP_ONCE_

