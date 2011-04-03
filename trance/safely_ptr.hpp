// trance safely_ptr.hpp - Local Function Library
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

#ifndef IG_TRANCE_SAFELY_PTR_HPP_ONCE_
#define IG_TRANCE_SAFELY_PTR_HPP_ONCE_

#include <cstddef>
#include <algorithm>
#include <utility>
#include <functional>

#include <boost/static_assert.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/common_type.hpp>

#include <boost/utility/enable_if.hpp>

#include <trance/config.hpp>
#include <trance/safe_bool.hpp>

namespace trance
{

// TODO: Implementation this.
class nullptr_exception {};

template < typename >
class safely_ptr;

template < typename T, typename U >
inline safely_ptr< T >
safely_cast( safely_ptr< U > _ptr ) TRANCE_NOEXCEPT
{
    typedef ::boost::mpl::or_<
      ::boost::mpl::and_<
        ::boost::mpl::not_< ::boost::is_array< T > >,
        ::boost::mpl::not_< ::boost::is_array< U > >
      >,
      ::boost::mpl::and_<
        ::boost::is_array< T >,
        ::boost::is_array< U >
      >
    > array_or_not_array;
    BOOST_STATIC_ASSERT( array_or_not_array::value );

    typedef ::boost::is_convertible<
      BOOST_DEDUCED_TYPENAME safely_ptr< U >::pointer,
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer
    > convertible_type;
    BOOST_STATIC_ASSERT( convertible_type::value );

    typedef BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer cast_type;
    return safely_ptr< T >( static_cast< cast_type >( _ptr.get() ) );
}

template < typename T >
class safely_ptr
{
public:
    typedef T   element_type;
    typedef T * pointer;
    typedef T & reference;

private:
    pointer _M_ptr;

    void
    _null_check( void ) const
    {
        if ( get() == pointer() )
        { throw nullptr_exception(); }
    }

public:
    TRANCE_CONSTEXPR
    safely_ptr( void ) TRANCE_NOEXCEPT
      : _M_ptr() {}

#if !defined( BOOST_NO_NULLPTR )
    TRANCE_CONSTEXPR
    safely_ptr( ::std::nullptr_t )
      : _M_ptr() {}
#endif // !BOOST_NO_NULLPTR

    explicit
    safely_ptr( pointer _ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr ) {}

    safely_ptr( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( safely_cast< element_type >( _ptr ).get() ) {}

#if defined( BOOST_HAS_RVALUE_REFS )
    safely_ptr( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( safely_cast< element_type >( _ptr ).get() ) {}
#endif // !BOOST_NO_RVALUE_REFERENCES

    safely_ptr &
    operator=( pointer _ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr );
        return *this;
    }

    safely_ptr &
    operator=( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr.get() );
        return *this;
    }

    template < typename U >
    safely_ptr &
    operator=( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
    {
        safely_cast< element_type >( _ptr ).swap( this );
        return *this;
    }

#if !defined( BOOST_NO_RVALUE_REFERENCES )
    safely_ptr &
    operator=( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr.get() );
        return *this;
    }

    template < typename U >
    safely_ptr &
    operator=( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
    {
        safely_cast< element_type >( _ptr ).swap( this );
        return *this;
    }
#endif // !BOOST_NO_RVALUE_REFERENCES

    reference
    operator*( void ) const
    {
        _null_check();
        return *get();
    }

    pointer
    operator->( void ) const
    {
        _null_check();
        return get();
    }

#if !defined( BOOST_NO_EXPLICIT_CONVERSION_OPERATORS )
    explicit
    operator bool( void ) const TRANCE_NOEXCEPT
    { return get() == pointer() ? true : false; }
#else
    operator safe_bool_t( void ) const TRANCE_NOEXCEPT
    { return safe_bool( get() == pointer() ); }
#endif // !BOOST_NO_EXPLICIT_CONVERSION_OPERATORS

    pointer
    get( void ) const TRANCE_NOEXCEPT
    { return _M_ptr; }

    pointer
    release( void ) TRANCE_NOEXCEPT
    {
        pointer _p = get();
        _M_ptr = pointer();
        return _p;
    }

    void
    reset( pointer _ptr = pointer() ) TRANCE_NOEXCEPT
    { safely_ptr( _ptr ).swap( *this ); }

    void
    swap( safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        using ::std::swap;
        swap( _M_ptr, _ptr._M_ptr );
    }
};

template < typename T >
class safely_ptr< T[] >
{
public:
    typedef T   element_type;
    typedef T * pointer;
    typedef T & reference;

private:
    pointer _M_ptr;

    void
    _null_check( void ) const
    {
        if ( get() == pointer() )
        { throw nullptr_exception(); }
    }

public:
    TRANCE_CONSTEXPR
    safely_ptr( void ) TRANCE_NOEXCEPT
      : _M_ptr() {}

#if !defined( BOOST_NO_NULLPTR )
    TRANCE_CONSTEXPR
    safely_ptr( ::std::nullptr_t )
      : _M_ptr() {}
#endif

    explicit
    safely_ptr( pointer _ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr ) {}

    safely_ptr( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( safely_cast< element_type[] >( _ptr ).get() ) {}

#if defined( BOOST_HAS_RVALUE_REFS )
    safely_ptr( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
      : _M_ptr( safely_cast< element_type[] >( _ptr ).get() ) {}
#endif // !BOOST_NO_RVALUE_REFERENCES

    safely_ptr &
    operator=( pointer _ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr );
        return *this;
    }

    safely_ptr &
    operator=( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr.get() );
        return *this;
    }

    template < typename U >
    safely_ptr &
    operator=( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
    {
        safely_cast< element_type[] >( _ptr ).swap( this );
        return *this;
    }

#if !defined( BOOST_NO_RVALUE_REFERENCES )
    safely_ptr &
    operator=( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
    {
        reset( _ptr.get() );
        return *this;
    }

    template < typename U >
    safely_ptr &
    operator=( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
    {
        safely_cast< element_type[] >( _ptr ).swap( this );
        return *this;
    }
#endif // !BOOST_NO_RVALUE_REFERENCES

    reference
    operator[]( ::std::size_t _x ) const
    {
        _null_check();
        return get()[ _x ];
    }

#if !defined( BOOST_NO_EXPLICIT_CONVERSION_OPERATORS )
    explicit
    operator bool( void ) const TRANCE_NOEXCEPT
    { return get() == pointer() ? true : false; }
#else
    operator safe_bool_t( void ) const TRANCE_NOEXCEPT
    { return safe_bool( get() == pointer() ); }
#endif // !BOOST_NO_EXPLICIT_CONVERSION_OPERATORS

    pointer
    get( void ) const TRANCE_NOEXCEPT
    { return _M_ptr; }

    pointer
    release( void ) TRANCE_NOEXCEPT
    {
        pointer _p = get();
        _M_ptr = pointer();
        return _p;
    }

    void
    reset( pointer _ptr = pointer() ) TRANCE_NOEXCEPT
    { safely_ptr( _ptr ).swap( *this ); }

    void
    swap( safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        using ::std::swap;
        swap( _M_ptr, _ptr._M_ptr );
    }
};

template < typename T >
inline void
swap( safely_ptr< T > &_x, safely_ptr< T > &_y ) TRANCE_NOEXCEPT
{ _x.swap( _y ); }

template < typename T, typename U >
inline bool
operator==( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return _x.get() == _y.get(); }

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator==( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !_x; }

template < typename T >
inline bool
operator==( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !_x; }
#endif // !BOOST_NO_NULLPTR

template < typename T, typename U >
inline bool
operator!=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _x == _y ); }

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator!=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return static_cast< bool >( _x ); }

template < typename T >
inline bool
operator!=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return static_cast< bool >( _x ); }
#endif // !BOOST_NO_NULLPTR

template < typename T, typename U >
inline bool
operator<( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::common_type<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer,
      BOOST_DEDUCED_TYPENAME safely_ptr< U >::pointer
    >::type _CT;
    return ::std::less< _CT >( _x.get(), _y.get() );
}

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator<( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{
    typedef BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer pointer;
    return ::std::less< pointer >()( _x.get(), nullptr );
}

template < typename T >
inline bool
operator<( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{
    typedef BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer pointer;
    return ::std::less< pointer >()( nullptr, _x.get() );
}
#endif // !BOOST_NO_NULLPTR

template < typename T, typename U >
inline bool
operator<=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _y < _x ); }

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator<=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !( nullptr < _x ); }

template < typename T >
inline bool
operator<=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !( _x < nullptr ); }
#endif // !BOOST_NO_NULLPTR

template < typename T, typename U >
inline bool
operator>( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return _y < _x; }

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator>( const safely_ptr< T > &_x, ::std:nullptr_t ) TRANCE_NOEXCEPT
{ return nullptr < _x; }

template < typename T >
inline bool
operator>( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return _x < nullptr; }
#endif // !BOOST_NO_NULLPTR

template < typename T, typename U >
inline bool
operator>=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _x < _y ); }

#if !defined( BOOST_NO_NULLPTR )
template < typename T >
inline bool
operator>=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !( _x < nullptr ); }

template < typename T >
inline bool
operator>=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !( nullptr < _x ); }
#endif // !BOOST_NO_NULLPTR

} // namespace trance

namespace std
{

template < typename T >
struct hash;

// std::hash specialization for trance::safely_ptr.
template < typename T >
struct hash< ::trance::safely_ptr< T > >
  : public unary_function< ::trance::safely_ptr< T >, size_t >
{
    size_t
    operator()( const ::trance::safely_ptr< T > &_x ) const
    {
        typedef ::trance::safely_ptr< T > _SP;
        return std::hash< BOOST_DEDUCED_TYPENAME _SP::pointer >()( _x.get() );
    }
};

} // namespace std

#endif // IG_TRANCE_SAFELY_PTR_HPP_ONCE_
