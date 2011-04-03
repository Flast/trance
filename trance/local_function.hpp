// trance local_function.hpp - Local Function Library
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

#ifndef IG_TRANCE_LOCAL_FUNCTION_HPP_ONCE_
#define IG_TRANCE_LOCAL_FUNCTION_HPP_ONCE_

#include <boost/config.hpp>

#include <boost/preprocessor/cat.hpp>

#include <trance/config.hpp>

// example:
//  TRANCE_LOCAL_FUNCTION( void, function, ( const char *str ),
//  {
//      std::cout << str << std::endl;
//  } )
//  function( "Hellow, world" );

// You can take pointer to local function. For example:
//  TRANCE_LOCAL_FUNCTION( void, function, ( const char *str ),
//  {
//      std::cout << str << std::endl;
//  } )
//  void ( *pf1 )( const char * ) = function; // implicitly convertion
//  void ( *pf2 )( const char * ) = &function; // also explicitly can

#if defined( BOOST_NO_LAMBDAS )

// If compiler does not support C++0x style lambda expression,
// use static member function to emulate the (non-capture) lambda.
#define TRANCE_LOCAL_FUNCTION( _lf_return, _lf_function, _lf_args, _lf_body )   \
  struct BOOST_PP_CAT( _trance_local_function_impl_, __LINE__ )                 \
  {                                                                             \
      static inline _lf_return                                                  \
      _function _lf_args                                                        \
      _lf_body                                                                  \
  };                                                                            \
  _lf_return ( &_lf_function )_lf_args =                                        \
    BOOST_PP_CAT( _trance_local_function_impl_, __LINE__ )::_function;          \

#else

// Use reference because to be able to get pointer to function.
#define TRANCE_LOCAL_FUNCTION( _lf_return, _lf_function, _lf_args, _lf_body )   \
  _lf_return ( &_lf_function )_lf_args =                                        \
    *static_cast< _lf_return ( * )_lf_args >(                                   \
      []_lf_args -> _lf_return                                                  \
      _lf_body );                                                               \

#endif // BOOST_NO_LAMBDAS

#endif // IG_TRANCE_LOCAL_FUNCTION_HPP_ONCE_

