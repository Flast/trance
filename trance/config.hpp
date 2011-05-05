// trance config.hpp - Configuration Library
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

#ifndef IG_TRANCE_CONFIG_HPP_ONCE_
#define IG_TRANCE_CONFIG_HPP_ONCE_

#include <boost/config.hpp>

// Compiler features

#if defined( BOOST_NO_CONSTEXPR )
#   define TRANCE_CONSTEXPR
#else
#   define TRANCE_CONSTEXPR constexpr
#endif // BOOST_NO_CONSTEXPR

// work around for noexcept
#define TRANCE_NOEXCEPT

// work around for throw() or noexcept
// note: std::bad_alloc's members are granted throw() in C++98/03,
//       but in C++0x(a.k.a C++11), are granted noexcept.
#define TRANCE_EMPTY_THROW_SPEC_OR_NOEXCEPT throw()

#if !defined( BOOST_NO_DELETED_FUNCTIONS )
#   define TRANCE_DELETED_FUNCTION = delete
#else
#   define TRANCE_DELETED_FUNCTION
#endif // !BOOST_NO_DELETED_FUNCTIONS

// Standard Library features

#if !defined( BOOST_NO_0X_HDR_TYPE_TRAITS )
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::std
#else
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::boost
#endif // !BOOST_NO_0X_HDR_TYPE_TRAITS

#endif // IG_TRANCE_CONFIG_HPP_ONCE_

