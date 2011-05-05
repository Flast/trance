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
#include <boost/version.hpp>

// Compiler features

// TODO: check supported version
#if !defined( BOOST_NO_NULLPTR )
#   define TRANCE_HAS_NULLPTR
#endif // BOOST_NO_NULLPTR

// TODO: check supported version
#if !defined( BOOST_NO_CONSTEXPR )
#   define TRANCE_HAS_CONSTEXPR
#   define TRANCE_CONSTEXPR constexpr
#else
#   define TRANCE_CONSTEXPR
#endif // BOOST_NO_CONSTEXPR

// TODO: check supported version
#if !defined( BOOST_NO_LAMBDAS )
#   define TRANCE_HAS_LAMBDAS
#endif // BOOST_NO_LAMBDAS

// TODO: check supported version
#if !defined( BOOST_NO_RVALUE_REFERENCES )
#   define TRANCE_HAS_RVALUE_REFERENCES
#endif // BOOST_NO_RVALUE_REFERENCES

// TODO: check supported version
#if !defined( BOOST_NO_EXPLICIT_CONVERSION_OPERATORS )
#   define TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS
#endif // !BOOST_NO_EXPLICIT_CONVERSION_OPERATORS

// BOOST_NO_NOEXCEPT requires Boost 1.47 or later.
#if !BOOST_VERSION < 104700 || defined( BOOST_NO_NOEXCEPT )
#   define TRANCE_HAS_NOEXCEPT
#   define TRANCE_NOEXCEPT noexcept
#   define TRANCE_THROW_SPEC_OR_NOEXCEPT noexcept
#else
#   define TRANCE_NOEXCEPT
// note: std::bad_alloc's members are granted throw() in C++98/03,
//       but in C++0x(a.k.a C++11), are granted noexcept.
#   define TRANCE_THROW_SPEC_OR_NOEXCEPT throw()
#endif // BOOST_NO_NOEXCEPT

// TODO: check supported version
#if !defined( BOOST_NO_DELETED_FUNCTIONS )
#   define TRANCE_HAS_DELETED_FUNCTIONS
#   define TRANCE_DELETED_FUNCTION = delete
#else
#   define TRANCE_DELETED_FUNCTION
#endif // BOOST_NO_DELETED_FUNCTIONS

// TODO: check supported version
#if !defined( BOOST_NO_CHAR16_T )
#   define TRANCE_HAS_CHAR16_T
#endif // BOOST_NO_CHAR16_T

// TODO: check supported version
#if !defined( BOOST_NO_CHAR32_T )
#   define TRANCE_HAS_CHAR32_T
#endif // BOOST_NO_CHAR32_T

// Standard Library features

// TODO: check supported version
#if !defined( BOOST_NO_0X_HDR_TYPE_TRAITS )
#   define TRANCE_HAS_0X_HDR_TYPE_TRAITS
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::std
#   define TRANCE_TYPE_TRAITS_HDR <type_traits>
#else
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::boost
#   define TRANCE_TYPE_TRAITS_HDR <boost/type_traits.hpp>
#endif // BOOST_NO_0X_HDR_TYPE_TRAITS

// TODO: check supported version
#if !defined( BOOST_NO_0X_HDR_ARRAY )
#   define TRANCE_HAS_0X_HDR_ARRAY
#   define TRANCE_ARRAY_NAMESPACE ::std
#   define TRANCE_ARRAY_HDR <array>
#else
#   define TRANCE_ARRAY_NAMESPACE ::boost
#   define TRANCE_ARRAY_HDR <boost/array.hpp>

#endif // BOOST_NO_0X_HDR_ARRAY

#endif // IG_TRANCE_CONFIG_HPP_ONCE_

