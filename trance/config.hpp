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

// XXX NOTE -- 2011/04/06 -- XXX
//  Trance.Config is written for Boost 1.47.0.
//  If you want to use as trunk, define TRANCE_CONFIG_USE_AS_TRUNK.

#ifndef IG_TRANCE_CONFIG_HPP_ONCE_
#define IG_TRANCE_CONFIG_HPP_ONCE_

#include <boost/config.hpp>
#include <boost/version.hpp>

// Boost 1.34.0 or earlier
#if BOOST_VERSION < 103500
//#   warning "Boost 1.34.0 or earlier are not supported in Trance.Config."
#endif // BOOST_VERSION < 103500

// Compiler features

// Boost 1.35.0 and a part of 1.36.0
// Those BOOST_HAS_* macros are deprecated.
#if !defined( BOOST_HAS_CONCEPTS ) || defined( BOOST_NO_CONCEPTS )
#   ifndef BOOST_NO_CONCEPTS
#       define BOOST_NO_CONCEPTS
#   endif // BOOST_NO_CONCEPTS
#else
#   define TRANCE_HAS_CONCEPTS
#endif // BOOST_HAS_CONCEPTS

#if !defined( BOOST_HAS_DECLTYPE ) || defined( BOOST_NO_DECLTYPE )
#   ifndef BOOST_NO_DECLTYPE
#       define BOOST_NO_DECLTYPE
#   endif // BOOST_NO_DECLTYPE
#else
#   define TRANCE_HAS_DECLTYPE
#endif // BOOST_HAS_DECLTYPE

#if !defined( BOOST_HAS_LONG_LONG ) || defined( BOOST_NO_LONG_LONG )
#   ifndef BOOST_NO_LONG_LONG
#       define BOOST_NO_LONG_LONG
#   endif // BOOST_NO_LONG_LONG
#else
#   define TRANCE_HAS_LONG_LONG
#endif // BOOST_HAS_LONG_LONG

#if !defined( BOOST_HAS_RVALUE_REFS ) || defined( BOOST_NO_RVALUE_REFERENCES )
#   ifndef BOOST_NO_RVALUE_REFERENCES
#       define BOOST_NO_RVALUE_REFERENCES
#   endif // BOOST_NO_RVALUE_REFERENCES
#else
#   define TRANCE_HAS_RVALUE_REFERENCES
#endif // BOOST_HAS_RVALUE_REFS

#if !defined( BOOST_HAS_STATIC_ASSERT ) || defined( BOOST_NO_STATIC_ASSERT )
#   ifndef BOOST_NO_STATIC_ASSERT
#       define BOOST_NO_STATIC_ASSERT
#   endif // BOOST_NO_STATIC_ASSERT
#else
#   define TRANCE_HAS_STATIC_ASSERT
#endif // BOOST_HAS_STATIC_ASSERT

#if !defined( BOOST_HAS_VARIADIC_TMPL ) || defined( BOOST_NO_VARIADIC_TEMPLATES )
#   ifndef BOOST_NO_VARIADIC_TEMPLATES
#       define BOOST_NO_VARIADIC_TEMPLATES
#   endif // BOOST_NO_VARIADIC_TEMPLATES
#else
#   define TRANCE_HAS_VARIADIC_TEMPLATES
#endif // BOOST_HAS_VARIADIC_TMPL

// Boost 1.36.0 or later (rest configures)
#if 103600 <= BOOST_VERSION

#   ifndef BOOST_NO_CHAR16_T
#       define TRANCE_HAS_CHAR16_T
#   endif // BOOST_NO_CHAR16_T

#   ifndef BOOST_NO_CHAR32_T
#       define TRANCE_HAS_CHAR32_T
#   endif // BOOST_NO_CHAR32_T

#   ifndef BOOST_NO_CONSTEXPR
#       define TRANCE_HAS_CONSTEXPR
#   endif // BOOST_NO_CONSTEXPR

#   ifndef BOOST_NO_DEFAULTED_FUNCTIONS
#       define TRANCE_HAS_DEFAULTED_FUNCTIONS
#   endif // BOOST_NO_DEFAULTED_FUNCTIONS

#   ifndef BOOST_NO_DELETED_FUNCTIONS
#       define TRANCE_HAS_DELETED_FUNCTIONS
#   endif // BOOST_NO_DELETED_FUNCTIONS

#   ifndef BOOST_NO_EXPLICIT_CONVERSION_OPERATORS
#       define TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS
#   endif // BOOST_NO_EXPLICIT_CONVERSION_OPERATORS

#   ifndef BOOST_NO_EXTERN_TEMPLATE
#       define TRANCE_HAS_EXTERN_TEMPLATE
#   endif // BOOST_NO_EXTERN_TEMPLATE

#   ifndef BOOST_NO_RAW_LITERALS
#       define TRANCE_HAS_RAW_LITERALS
#   endif // BOOST_NO_RAW_LITERALS

#   ifndef BOOST_NO_SCOPED_ENUMS
#       define TRANCE_HAS_SCOPED_ENUMS
#   endif // BOOST_NO_SCOPED_ENUMS

#   ifndef BOOST_NO_UNICODE_LITERALS
#       define TRACE_HAS_UNICODE_LITERALS
#   endif // BOOST_NO_UNICODE_LITERALS

#endif // 103600 <= BOOST_VERSION

// Boost 1.38.0 or later
#if 103800 <= BOOST_VERSION

#   ifndef BOOST_NO_INITIALIZER_LISTS
#       define TRANCE_HAS_INITIALIZER_LISTS
#   endif // BOOST_NO_INITIALIZER_LISTS

#endif // 103800 <= BOOST_VERSION

// Boost 1.40.0 or later
#if 104000 <= BOOST_VERSION

#   ifndef BOOST_NO_AUTO_DECLARATIONS
#       define TRANCE_HAS_AUTO_DECLARATIONS
#   endif // BOOST_NO_AUTO_DECLARATIONS

#   ifndef BOOST_NO_AUTO_MULTIDECLARATIONS
#       define TRANCE_HAS_AUTO_MULTIDECLARATIONS
#   endif // BOOST_NO_AUTO_MULTIDECLARATIONS

#   ifndef BOOST_NO_TEMPLATE_ALIASES
#       define TRANCE_HAS_TEMPLATE_ALIASES
#   endif // BOOST_NO_TEMPLATE_ALIASES

#   ifndef BOOST_NO_LAMBDAS
#       define TRANCE_HAS_LAMBDAS
#   endif // BOOST_NO_LAMBDAS

#   ifndef BOOST_NO_NULLPTR
#       define TRANCE_HAS_NULLPTR
#   endif // BOOST_NO_NULLPTR

#endif // 104000 <= BOOST_VERSION

// Boost 1.41.0 or later
#if 104100 <= BOOST_VERSION

#   ifndef BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#       define TRANCE_HAS_FUNCTION_TEMPLATE_DEFAULT_ARGS
#   endif // BOOST_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS

#endif // 104100 <= BOOST_VERSION

// Boost 1.44.0 or later
#if 104400 <= BOOST_VERSION

#   ifndef BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#       define TRANCE_HAS_COMPLETE_VALUE_INITIALIZATION
#   endif // BOOST_NO_COMPLETE_VALUE_INITIALIZATION

#endif // 104400 <= BOOST_VERSION

// Boost 1.45.0 or later
#if 104500 <= BOOST_VERSION

#   ifndef BOOST_NO_VARIADIC_MACROS
#       define TRANCE_HAS_VARIADIC_MACROS
#   endif // BOOST_NO_VARIADIC_MACROS

#endif // 104500 <= BOOST_VERSION

#if 104700 <= BOOST_VERSION

#   ifndef BOOST_NO_NOEXCEPT
#       define TRANCE_HAS_NOEXCEPT
#   endif // BOOST_NO_NOEXCEPT

#   ifndef BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX
#       define TRANCE_HAS_UNIFIED_INITIALIZATION_SYNTAX
#   endif // BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX

#endif // 104700 <= BOOST_VERSION

// Boost 1.47.0 does not support yet.
#if defined( TRANCE_CONFIG_USE_AS_TRUNK )

#   ifndef BOOST_NO_DECLTYPE_N3276
#       define TRANCE_HAS_DECLTYPE_N3276
#   endif // BOOST_NO_DECLTYPE_N3276

#endif // TRANCE_CONFIG_USE_AS_TRUNK

// Utilities

#ifdef TRANCE_HAS_CONSTEXPR
#   define TRANCE_CONSTEXPR constexpr
#else
#   define TRANCE_CONSTEXPR
#endif // TRANCE_HAS_CONSTEXPR

#ifdef TRANCE_HAS_DELETED_FUNCTIONS
#   define TRANCE_DELETED_FUNCTION = delete
#else
#   define TRANCE_DELETED_FUNCTION
#endif // TRANCE_HAS_DELETED_FUNCTIONS

#ifdef TRANCE_HAS_NOEXCEPT
#   define TRANCE_NOEXCEPT noexcept
#   define TRANCE_THROW_SPEC_OR_NOEXCEPT noexcept
#else
#   define TRANCE_NOEXCEPT
// note: std::bad_alloc's members are granted throw() in C++98/03,
//       but in C++0x(a.k.a C++11), are granted noexcept.
#   define TRANCE_THROW_SPEC_OR_NOEXCEPT throw()
#endif // TRANCE_HAS_NOEXCEPT

// Standard Library features

// Boost 1.38.0 or later
#if 103800 <= BOOST_VERSION

#   ifdef BOOST_NO_STD_UNORDERED
#       ifndef BOOST_NO_0X_HDR_UNORDERED_MAP
#           define BOOST_NO_0X_HDR_UNORDERED_MAP
#       endif

#       ifndef BOOST_NO_0X_HDR_UNORDERED_SET
#           define BOOST_NO_0X_HDR_UNORDERED_SET
#       endif
#   endif // BOOST_NO_STD_UNORDERED

#   ifndef BOOST_NO_0X_HDR_UNORDERED_MAP
#       define TRANCE_HAS_0X_HDR_UNORDERED_MAP
#   endif // BOOST_NO_0X_HDR_UNORDERED_MAP

#   ifndef BOOST_NO_0X_HDR_UNORDERED_SET
#       define TRANCE_HAS_0X_HDR_UNORDERED_SET
#   endif // BOOST_NO_0X_HDR_UNORDERED_SET

#endif // 103800 <= BOOST_VERSION

#if 104000 <= BOOST_VERSION

#   ifndef BOOST_NO_0X_HDR_ARRAY
#       define TRANCE_HAS_0X_HDR_ARRAY
#   endif // BOOST_NO_0X_HDR_ARRAY

#   ifndef BOOST_NO_0X_HDR_CHRONO
#       define TRANCE_HAS_0X_HDR_CHRONO
#   endif // BOOST_NO_0X_HDR_CHRONO

#   ifndef BOOST_NO_0X_HDR_CODECVT
#       define TRANCE_HAS_0X_HDR_CODECVT
#   endif // BOOST_NO_0X_HDR_CODECVT

// TODO: check defined version
//#   ifndef BOOST_NO_0X_HDR_CONCEPTS
//#       define TRANCE_HAS_0X_HDR_CONCEPTS
//#   endif // BOOST_NO_0X_HDR_CONCEPTS

#   ifndef BOOST_NO_0X_HDR_CONDITION_VARIABLE
#       define TRANCE_HAS_0X_HDR_CONDITION_VARIABLE
#   endif // BOOST_NO_0X_HDR_CONDITION_VARIABLE

// TODO: check defined version
//#   ifndef BOOST_NO_0X_HDR_CONTAINER_CONCEPTS
//#       define TRANCE_HAS_0X_HDR_CONCEPTS
//#   endif // BOOST_NO_0X_HDR_CONTAINER_CONCEPTS

#   ifndef BOOST_NO_0X_HDR_FORWARD_LIST
#       define TRANCE_HAS_0X_HDR_FORWARD_LIST
#   endif // BOOST_NO_0X_HDR_FORWARD_LIST

#   ifndef BOOST_NO_0X_HDR_FUTURE
#       define TRANCE_HAS_0X_HDR_FUTURE
#   endif // BOOST_NO_0X_HDR_FUTURE

#   ifndef BOOST_NO_0X_HDR_INITIALIZER_LIST
#       define TRANCE_HAS_0X_HDR_INITIALIZER_LIST
#   endif // BOOST_NO_0X_HDR_INITIALIZER_LIST

// TODO: check defined version
//#   ifndef BOOST_NO_0X_HDR_ITERATOR_CONCEPTS
//#       define TRANCE_HAS_0X_HDR_ITERATOR_CONCEPTS
//#   endif // BOOST_NO_0X_HDR_ITERATOR_CONCEPTS

// TODO: check defined version
//#   ifndef BOOST_NO_0X_HDR_MEMORY_CONCEPTS
//#       define TRANCE_HAS_0X_HDR_MEMORY_CONCEPTS
//#   endif // BOOST_NO_0X_HDR_MEMORY_CONCEPTS

#   ifndef BOOST_NO_0X_HDR_MUTEX
#       define TRANCE_HAS_0X_HDR_MUTEX
#   endif // BOOST_NO_0X_HDR_MUTEX

#   ifndef BOOST_NO_0X_HDR_RANDOM
#       define TRANCE_HAS_0X_HDR_RANDOM
#   endif // BOOST_NO_0X_HDR_RANDOM

#   ifndef BOOST_NO_0X_HDR_RATIO
#       define TRANCE_HAS_0X_HDR_RATIO
#   endif // BOOST_NO_0X_HDR_RATIO

#   ifndef BOOST_NO_0X_HDR_REGEX
#       define TRANCE_HAS_0X_HDR_REGEX
#   endif // BOOST_NO_0X_HDR_REGEX

#   ifndef BOOST_NO_0X_HDR_SYSTEM_ERROR
#       define TRANCE_HAS_0X_HDR_SYSTEM_ERROR
#   endif // BOOST_NO_0X_HDR_SYSTEM_ERROR

#   ifndef BOOST_NO_0X_HDR_THREAD
#       define TRANCE_HAS_0X_HDR_THREAD
#   endif // BOOST_NO_0X_HDR_THREAD

#   ifndef BOOST_NO_0X_HDR_TUPLE
#       define TRANCE_HAS_0X_HDR_TUPLE
#   endif // BOOST_NO_0X_HDR_TUPLE

#   ifndef BOOST_NO_0X_HDR_TYPE_TRAITS
#       define TRANCE_HAS_0X_HDR_TYPE_TRAITS
#   endif // BOOST_NO_0X_HDR_TYPE_TRAITS

#endif // 104000 <= BOOST_VERSION

// Boost 1.44.0 or later
#if 104400 <= BOOST_VERSION

#   ifndef BOOST_NO_0X_HDR_TYPEINDEX
#       define TRANCE_HAS_0X_HDR_TYPEINDEX
#   endif // BOOST_NO_0X_HDR_TYPEINDEX

#endif // 104400 <= BOOST_VERSION

// Boost 1.45.0 or later
#if 104500 <= BOOST_VERSION

#   ifndef BOOST_NO_NUMERIC_LIMITS_LOWEST
#       define TRANCE_HAS_NUMERIC_LIMITS_LOWEST
#   endif // BOOST_NO_NUMERIC_LIMITS_LOWEST

#endif // 104500 <= BOOST_VERSION

// Alternatives

// Boost.Unorderd supported after 1.36.0.
#ifdef TRANCE_HAS_0X_HDR_UNORDERED_MAP // require 1.38.0
#   define TRANCE_UNORDERED_MAP_NAMESPACE ::std
#   define TRANCE_UNORDERED_MAP_HDR <unordered_map>
#else
#   define TRANCE_UNORDERED_MAP_NAMESPACE ::boost
#   define TRANCE_UNORDERED_MAP_HDR <boost/unordered_map.hpp>
#endif // TRANCE_HAS_0X_HDR_UNORDERED_MAP

// Boost.Unorderd supported after 1.36.0.
#ifdef TRANCE_HAS_0X_HDR_UNORDERED_SET // require 1.38.0
#   define TRANCE_UNORDERED_SET_NAMESPACE ::std
#   define TRANCE_UNORDERED_SET_HDR <unordered_set>
#else
#   define TRANCE_UNORDERED_SET_NAMESPACE ::boost
#   define TRANCE_UNORDERED_SET_HDR <boost/unordered_set.hpp>
#endif // TRANCE_HAS_0X_HDR_UNORDERED_SET

// Boost.Array supported after 1.17.0.
#ifdef TRANCE_HAS_0X_HDR_ARRAY // require 1.40.0
#   define TRANCE_ARRAY_NAMESPACE ::std
#   define TRANCE_ARRAY_HDR <array>
#else
#   define TRANCE_ARRAY_NAMESPACE ::boost
#   define TRANCE_ARRAY_HDR <boost/array.hpp>
#endif // TRANCE_HAS_0X_HDR_ARRAY

// Boost.Chrono not supported in 1.46.1 yet.
#ifdef TRANCE_HAS_0X_HDR_CHRONO // require 1.40.0
#   define TRANCE_CHRONO_NAMESPACE ::std
#   define TRANCE_CHRONO_HDR <chrono>
#elif defined( TRANCE_CONFIG_USE_AS_TRUNK )
#   define TRANCE_CHRONO_NAMESPACE ::boost
#   define TRANCE_CHRONO_HDR <boost/chrono.hpp>
#else
#   define TRANCE_CHRONO_NAMESPACE
#   define TRANCE_CHRONO_HDR <trance/config/chrono.hpp>
#endif // TRANCE_HAS_0X_HDR_CHRONO

// Boost.Thread supported after 1.25.0.
#ifdef TRANCE_HAS_0X_HDR_CONDITION_VARIABLE // require 1.40.0
#   define TRANCE_CONDITION_VARIABLE_NAMESPACE ::std
#   define TRANCE_CONDITION_VARIABLE_HDR <condition_variable>
#else
#   define TRANCE_CONDITION_VARIABLE_NAMESPACE ::boost
#   define TRANCE_CONDITION_VARIABLE_HDR <boost/thread/condition_variable.hpp>
#endif // TRANCE_HAS_0X_HDR_CONDITION_VARIABLE

// Boost.Thread supported after 1.25.0.
#ifdef TRANCE_HAS_0X_HDR_FUTURE // require 1.40.0
#   define TRANCE_FUTURE_NAMESPACE ::std
#   define TRANCE_FUTURE_HDR <future>
#else
#   define TRANCE_FUTURE_NAMESPACE ::boost
#   define TRANCE_FUTURE_HDR <boost/thread/future.hpp>
#endif // TRANCE_HAS_0X_HDR_FUTURE

// Boost.Thread supported after 1.25.0.
#ifdef TRANCE_HAS_0X_HDR_MUTEX // require 1.40.0
#   define TRANCE_MUTEX_NAMESPACE ::std
#   define TRANCE_MUTEX_HDR <mutex>
#else
#   define TRANCE_MUTEX_NAMESPACE ::boost
#   define TRANCE_MUTEX_HDR <boost/thread/mutex.hpp>
#endif // TRANCE_HAS_0X_HDR_MUTEX

// Boost.Random supported after 1.15.0.
#ifdef TRANCE_HAS_0X_HDR_RANDOM // require 1.40.0
#   define TRANCE_RANDOM_NAMESPACE ::std
#   define TRANCE_RANDOM_HDR <random>
#else
#   define TRANCE_RANDOM_NAMESPACE ::boost
#   define TRANCE_RANDOM_HDR <boost/random.hpp>
#endif // TRANCE_HAS_0X_HDR_RANDOM

// Boost.Ratio not supported in 1.46.1 yet.
#ifdef TRANCE_HAS_0X_HDR_RATIO // require 1.40.0
#   define TRANCE_RATIO_NAMESPACE ::std
#   define TRANCE_RATIO_HDR <ratio>
#elif defined( TRANCE_CONFIG_USE_AS_TRUNK )
#   define TRANCE_RATIO_NAMESPACE ::boost
#   define TRANCE_RATIO_HDR <boost/ratio.hpp>
#else
#   define TRANCE_RATIO_NAMESPACE
#   define TRANCE_RATIO_HDR <trance/config/ratio.hpp>
#endif // TRANCE_HAS_0X_HDR_RATIO

// Boost.Regex supported after 1.18.0.
#ifdef TRANCE_HAS_0X_HDR_REGEX // require 1.40.0
#   define TRANCE_REGEX_NAMESPACE ::std
#   define TRANCE_REGEX_HDR <regex>
#else
#   define TRANCE_REGEX_NAMESPACE ::boost
#   define TRANCE_REGEX_HDR <boost/regex.hpp>
#endif // TRANCE_HAS_0X_HDR_REGEX

// Boost.System supported after 1.35.0.
#ifdef TRANCE_HAS_0X_HDR_SYSTEM_ERROR // require 1.40.0
#   define TRANCE_SYSTEM_ERROR_NAMESPACE ::std
#   define TRANCE_SYSTEM_ERROR_HDR <system_error>
#else
#   define TRANCE_SYSTEM_ERROR_NAMESPACE ::boost
#   define TRANCE_SYSTEM_ERROR_HDR <boost/system/system_error.hpp>
#endif // TRANCE_HAS_0X_HDR_SYSTEM_ERROR

// Boost.Thread supported after 1.25.0.
#ifdef TRANCE_HAS_0X_HDR_THREAD // require 1.40.0
#   define TRANCE_THREAD_NAMESPACE ::std
#   define TRANCE_THREAD_HDR <thread>
#else
#   define TRANCE_THREAD_NAMESPACE ::boost
#   define TRANCE_THREAD_HDR <boost/thread.hpp>
#endif // TRANCE_HAS_0X_HDR_THREAD

// Boost.Tuple supported after 1.24.0.
#ifdef TRANCE_HAS_0X_HDR_TUPLE // require 1.40.0
#   define TRANCE_TUPLE_NAMESPACE ::std
#   define TRANCE_TUPLE_HDR <tuple>
#else
#   define TRANCE_TUPLE_NAMESPACE ::boost
#   define TRANCE_TUPLE_HDR <boost/tuple.hpp>
#endif // TRANCE_HAS_0X_HDR_TUPLE

// Boost.Type Traits supported after 1.13.0.
#ifdef TRANCE_HAS_0X_HDR_TYPE_TRAITS // require 1.40.0
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::std
#   define TRANCE_TYPE_TRAITS_HDR <type_traits>
#else
#   define TRANCE_TYPE_TRAITS_NAMESPACE ::boost
#   define TRANCE_TYPE_TRAITS_HDR <boost/type_traits.hpp>
#endif // TRANCE_HAS_0X_HDR_TYPE_TRAITS

#include <trance/config/attribute.hpp>

#endif // IG_TRANCE_CONFIG_HPP_ONCE_

