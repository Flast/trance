// trance typeinfo.hpp - Local Function Library
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

#ifndef IG_TRANCE_TYPEINFO_HPP_ONCE_
#define IG_TRANCE_TYPEINFO_HPP_ONCE_

#include <typeinfo>

#include <trance/config.hpp>

#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
#   include <cstdlib>
#   include <cxxabi.h>
#endif // BOOST_GNU_STDLIB

namespace trance
{

namespace typeinfo_detail
{

class _type_info_impl
  : public ::std::type_info
{
    template < typename >
    friend _type_info_impl &
    _type_id_by_type( void );

    typedef ::std::type_info _base_t;

#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
    static inline char *
    _demangle( const char *_name )
    { return __cxxabiv1::__cxa_demangle( _name, 0, 0, 0 ); }

    char *_M_demangled_name;

    explicit
    _type_info_impl( const char *_n )
      : _base_t( _n ),
        _M_demangled_name( _demangle( _n ) ) {}
#endif // BOOST_GNU_STDLIB

public:
    ~_type_info_impl( void ) TRANCE_NOEXCEPT
    {
#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
        ::std::free( _M_demangled_name );
#endif // BOOST_GNU_STDLIB
    }

    const char *
    demangled_name( void ) const
    { return _M_demangled_name; }
};

template < typename T >
inline _type_info_impl &
_type_id_by_type( void )
{
    static _type_info_impl _impl_instance( typeid( T ).name() );
    return _impl_instance;
}

#if defined( BOOST_NO_RVALUE_REFERENCES )

template < typename T >
inline _type_info_impl &
_type_id_by_expr( T & )
{ return _type_id_by_type< T >(); }

template < typename T >
inline _type_info_impl &
_type_id_by_expr( const T & )
{ return _type_id_by_type< const T >(); }

#else // BOOST_NO_RVALUE_REFERENCES

template < typename T >
inline _type_info_impl &
_type_id_by_expr( T && )
{ return _type_id_by_type< T >(); }

#endif // BOOST_NO_RVALUE_REFERENCES

} // namespace typeinfo_detail

#define TRANCE_TYPEID_BY_TYPE( _T ) \
  ::trance::typeinfo_detail::_type_id_by_type< _T >()

#define TRANCE_TYPEID_BY_EXPR( _Expr ) \
  ::trance::typeinfo_detail::_type_id_by_expr( _Expr )

} // namespace trance

#endif // IG_TRANCE_TYPEINFO_HPP_ONCE_

