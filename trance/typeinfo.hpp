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

#include <trance/config.hpp>

#include <cstddef>
#include <string>
#include <typeinfo>

#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
#   include <cstdlib>
#   include <new>
#   include <stdexcept>
#   include <cxxabi.h>

// Boost 1.46.1's scoped_ptr.hpp missing detail/utilities.hpp for detail::do_swap.
#   include <boost/interprocess/detail/utilities.hpp>
#   include <boost/interprocess/smart_ptr/scoped_ptr.hpp>
#endif // BOOST_GNU_STDLIB

#include <trance/detail/typeof.hpp>

namespace trance
{

namespace typeinfo_detail
{

class _type_info_base
{
    type_info_base( const _type_info_base & ) TRANCE_DELETED_FUNCTION;

    _type_info_base &
    operator=( const _type_info_base & ) TRANCE_DELETED_FUNCTION;

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
    explicit
    type_info( const ::std::type_info &_ti )
      : _base_t( _ti ) {}

public:
    virtual const char *
    demangled_name( void ) const TRANCE_NOEXCEPT = 0;
};

class bad_typeid
{
    const char * const _M_what_message;

protected:
    TRANCE_CONSTEXPR explicit
    bad_typeid( const char *_mes ) TRANCE_NOEXCEPT
      : _M_what_message( _mes ) {}

public:
    TRANCE_CONSTEXPR const char *
    what( void ) const TRANCE_NOEXCEPT
    { return _M_what_message; }

    /*[[noreturn]]*/ virtual void
    rethrow_composite_error( void ) const = 0;
};

namespace typeinfo_detail
{

template < typename _Exception >
/*[[noreturn]]*/ inline void
_throw_bad_typeid_with( const char *_mes )
{
    struct _internal_composite_error
      : public bad_typeid, public _Exception
    {
        TRANCE_CONSTEXPR explicit
        _internal_composite_error( const char *_mes ) TRANCE_NOEXCEPT
          : bad_typeid( _mes ),
            _Exception(
              "Trance.Typeid: "
              "To process exception correctly, "
              "catch trance::bad_typeid."
            ) {}

        /*[[noreturn]]*/ void
        rethrow_composite_error( void ) const
        { throw _Exception( bad_typeid::what() ); }
    };

    throw _internal_composite_error( _mes );
}

struct _deleter_with_free
{
    inline void
    operator()( void *ptr )
    { ::std::free( ptr ); }
};

struct _messaged_bad_alloc
  : public ::std::bad_alloc
{
    const char *_M_what_message;

    explicit
    _messaged_bad_alloc( const char *_mes ) TRANCE_NOEXCEPT
      : _M_what_message( _mes ) {}

    const char *
    what( void ) const TRANCE_EMPTY_THROW_SPEC_OR_NOEXCEPT
    { return _M_what_message; }
};

inline ::std::string
_demangle( const ::std::type_info &_ti )
{
    const char * const mangled_name = _ti.name();
#if defined( BOOST_GNU_STDLIB ) && BOOST_GNU_STDLIB
    using namespace ::std;
    using ::abi::__cxa_demangle;
    using ::boost::interprocess::scoped_ptr;

    typedef scoped_ptr< char, _deleter_with_free > demangled_ptr;

    int status;
    demangled_ptr demangled( __cxa_demangle( mangled_name, 0, 0, &status ) );
    const string demangled_name( demangled.get() ? demangled.get() : "" );

    switch ( status )
    {
      case 0: break; // no error
      case -1: // memory allocation faild.
        _throw_bad_typeid_with< _messaged_bad_alloc >(
          "Trance.Typeid: abi::__cxa_demangle memory allocation faild."
        );
      case -2: // mangled name is not valid name.
        _throw_bad_typeid_with< invalid_argument >(
          "Trance.Typeid: Mangled name is not valid name. "
          "The ABI version is same and correct?"
        );
      case -3: // one of the arguments is invalid.
        _throw_bad_typeid_with< invalid_argument >(
          "Trance.Typeid: One of the arguments is invalid. "
          "Please submit a full bug report."
        );
      default: // unknown.
        _throw_bad_typeid_with< logic_error >(
          "Trance.Typeid: Unknown error occurred. "
          "Please submit a full bug report."
        );
    }
    return demangled_name;
#else
    return mangled_name;
#endif // BOOST_GNU_STDLIB
}

class _type_info_impl
  : public type_info
{
    template < typename >
    friend const type_info &
    _typeid_by_type( void );

    typedef ::std::string _demangled_name_type;

    _demangled_name_type _M_demangled_name;

    explicit
    _type_info_impl( const ::std::type_info &_ti )
      : type_info( _ti ),
        _M_demangled_name( _demangle( _ti ) ) {}

    struct _generics_typeid_invoke_tag {};

public:
    BOOST_STATIC_CONSTEXPR _generics_typeid_invoke_tag _generics_typeid_invoke
#if !defined( BOOST_NO_CONSTEXPR )
      = _generics_typeid_invoke_tag{}
#endif // BOOST_NO_CONSTEXPR
      ;

    _type_info_impl( _generics_typeid_invoke_tag, const ::std::type_info &_ti )
      : type_info( _ti ),
        _M_demangled_name( _demangle( _ti ) ) {}

    const char *
    demangled_name( void ) const TRANCE_NOEXCEPT
    { return _M_demangled_name.c_str(); }
};

#define TRANCE_TYPEID( _typeid_or_expr )                                   \
  static_cast< const ::trance::type_info & >(                              \
    ::trance::typeinfo_detail::_type_info_impl(                            \
      ::trance::typeinfo_detail::_type_info_impl::_generics_typeid_invoke, \
      typeid( _typeid_or_expr )                                            \
    )                                                                      \
  )                                                                        \

#define TRANCE_TYPEID_BY_TYPE( _typeid )                    \
  static_cast< const ::trance::type_info & >(               \
    ::trance::typeinfo_detail::_typeid_by_type< _typeid >() \
  )                                                         \

#define TRANCE_TYPEID_BY_EXPR( _Expr )          \
  static_cast< const ::trance::type_info & >(   \
    ::trance::typeinfo_detail::_typeid_by_expr( \
      TRANCE_DETAIL_TYPEOF( _Expr )             \
    )                                           \
  )                                             \

template < typename T >
inline const type_info &
_typeid_by_type( void )
{
    static _type_info_impl _impl_instance( typeid( T ) );
    return _impl_instance;
}

template < typename T >
inline const type_info &
_typeid_by_expr( T * )
{ return TRANCE_TYPEID_BY_TYPE( T ); }

} // namespace typeinfo_detail

} // namespace trance

#endif // IG_TRANCE_TYPEINFO_HPP_ONCE_

