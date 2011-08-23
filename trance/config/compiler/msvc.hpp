// trance msvc.hpp - MSVC Local Configuration Library
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

#ifndef IG_TRANCE_CONFIG_COMPILER_MSVC_HPP_ONCE_
#define IG_TRANCE_CONFIG_COMPILER_MSVC_HPP_ONCE_

#include <boost/preprocessor/cat.hpp>

#define TRANCE_CONFIG_MSVC_MODE
#define TRANCE_ATTRIBUTE_WHEN_MSVC( _attributes ) __declspec _attributes

#if _MSC_VER >= 1310
#   define TRANCE_ATTRIBUTE_NORETURN __declspec(noreturn)
#   define TRANCE_ATTRIBUTE_DLL( _spec ) __declspec(BOOST_PP_CAT( dll, _spec ))
#   define TRANCE_ATTRIBUTE_NOTHROW __declspec(nothrow)
#endif

#endif // IG_TRANCE_CONFIG_COMPILER_MSVC_HPP_ONCE_

