// trance typeinfo.hpp - Type identification Library
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

#include <cstddef>
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

class _type_info_base
{
    type_info_base( const _type_info_base & )
#if !defined( BOOST_NO_DELETED_FUNCTIONS )
      = delete
#endif // BOOST_NO_DELETED_FUNCTIONS
      ;

    _type_info_base &
    operator=( const _type_info_base & )
#if !defined( BOOST_NO_DELETED_FUNCTIONS )
      = delete
#endif // BOOST_NO_DELETED_FUNCTIONS
      ;

protected:
    const ::std::type_info &_M_internal;

    explicit
    _type_info_base( const ::std::type_info &_ti )
      : _M_internal( _ti ) {}

public:
    const char *
    name( void ) const
    { return _M_internal.name(); }

    bool
    before( const ::std::type_info &_other ) const TRANCE_NOEXCEPT
    { return _M_internal.before( _other ); }

    bool
    operator==( const ::std::type_info &_other ) const TRANCE_NOEXCEPT
    { return _M_internal.operator==( _other ); }

    bool
    operator!=( const ::std::type_info &_other ) const TRANCE_NOEXCEPT
    { return _M_internal.operator!=( _other ); }

    operator const ::std::type_info &( void ) const TRANCE_NOEXCEPT
    { return _M_internal; }
};

#if defined( __GNUC__ ) && defined( __GNUC_MINOR__ )
#   if __GNUC__ >= 4 \
    && __GNUC_MINOR__ >= 6 \
    && defined( __GXX_EXPERIMENTAL_CXX0X__ )
#       define TRANCE_HAS_TYPEINFO_HASH_CODE true
#       define TRANCE_USE_TYPEINFO_PARTIAL_SPEC
#   else
#       define TRANCE_HAS_TYPEINFO_HASH_CODE false
#   endif // GCC >= 4.6 && -std=c++0x
#else // __GNUC__ && __GNUC_MINOR__
#   define TRANCE_HAS_TYPEINFO_HASH_CODE \
  ::trance::typeinfo_detail::_has_hash_code< ::std::type_info >::value
#   define TRANCE_USE_TYPEINFO_PARTIAL_SPEC

template < typename T >
struct _has_hash_code
{
    typedef char                         no_type;
    typedef struct { char _dummy[ 8 ]; } yes_type;

    template < typename >
    static no_type
    check( ... );

    template < typename U >
    static yes_type
    check( U *, ::std::size_t ( U::* )( void ) const = &T::hash_code );

    BOOST_STATIC_CONSTEXPR bool value =
      sizeof( check< T >( 0 ) ) == sizeof( yes_type );
};
#endif

template < bool >
class _type_info
  : public _type_info_base
{
    typedef _type_info_base _base_t;

protected:
    _type_info( const ::std::type_info &_ti )
      : _base_t( _ti ) {}
};

#if defined( TRANCE_USE_TYPEINFO_PARTIAL_SPEC )
#undef TRANCE_USE_TYPEINFO_PARTIAL_SPEC
template <>
class _type_info< true >
  : public _type_info_base
{
    typedef _type_info_base _base_t;

protected:
    _type_info( const ::std::type_info &_ti )
      : _base_t( _ti ) {}

public:
    ::std::size_t
    hash_code( void ) const TRANCE_NOEXCEPT
    { return _base_t::_M_internal.hash_code(); }
};
#endif // TRANCE_USE_TYPEINFO_PARTIAL_SPEC

} // namespace typeinfo_detail

class type_info
  : public typeinfo_detail::_type_info< TRANCE_HAS_TYPEINFO_HASH_CODE >
{
    typedef typeinfo_detail::_type_info< TRANCE_HAS_TYPEINFO_HASH_CODE > _base_t;

protected:
    type_info( const ::std::type_info &_ti )
      : _base_t( _ti ) {}

public:
    virtual const char *
    demangled_name( void ) const = 0;
};

namespace typeinfo_detail
{

class _type_info_impl
  : public type_info
{
    template < typename >
    friend const type_info &
    _type_id_by_type( void );

    typedef char * _demangled_name_type;

    _demangled_name_type _M_demangled_name;

    static inline _demangled_name_type
    _demangle( const ::std::type_info &_ti )
    {
        const char * const mangled_name = _ti.name();
#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
        return __cxxabiv1::__cxa_demangle( mangled_name, 0, 0, 0 );
#else
        return mangled_name;
#endif // BOOST_GNU_STDLIB
    }

    explicit
    _type_info_impl( const ::std::type_info &_ti )
      : type_info( _ti ),
        _M_demangled_name( _demangle( _ti ) ) {}

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
inline const type_info &
_type_id_by_type( void )
{
    static _type_info_impl _impl_instance( typeid( T ) );
    return _impl_instance;
}

#if defined( BOOST_NO_RVALUE_REFERENCES )

template < typename T >
inline const type_info &
_type_id_by_expr( T & )
{ return _type_id_by_type< T >(); }

template < typename T >
inline const type_info &
_type_id_by_expr( const T & )
{ return _type_id_by_type< const T >(); }

#else // BOOST_NO_RVALUE_REFERENCES

template < typename T >
inline const type_info &
_type_id_by_expr( T && )
{ return _type_id_by_type< T >(); }

#endif // BOOST_NO_RVALUE_REFERENCES

} // namespace typeinfo_detail

#define TRANCE_TYPEID_BY_TYPE( _T ) \
  static_cast< const ::trance::type_info & >( ::trance::typeinfo_detail::_type_id_by_type< _T >() )

#define TRANCE_TYPEID_BY_EXPR( _Expr ) \
  static_cast< const ::trance::type_info & >( ::trance::typeinfo_detail::_type_id_by_expr( _Expr ) )

} // namespace trance

#endif // IG_TRANCE_TYPEINFO_HPP_ONCE_

