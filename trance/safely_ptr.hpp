// trance safely_ptr.hpp - Safely pointer container Library
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

#include <boost/mpl/assert.hpp>
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

namespace safely_ptr_detail_
{

template < typename T, typename U >
struct array_or_not
  : public ::boost::mpl::or_<
      ::boost::mpl::and_<
        ::boost::mpl::not_< ::boost::is_array< T > >,
        ::boost::mpl::not_< ::boost::is_array< U > >
      >,
      ::boost::mpl::and_<
        ::boost::is_array< T >,
        ::boost::is_array< U >
      >
    > {};

} // namespace safely_ptr_detail_

//  All of pointer_cast operator requirements:
//  1) Both of template parameter T and U is array or not array.
//  example:
//    safely_ptr< int > px;
//    pointer_cast< int >( px ); // OK.
//    pointer_cast< int[] >( px ); // ill-formed.
//      // Cannot cast non-array to array.
//    safely_ptr< int[] > ax;
//    pointer_cast< int >( ax ); // ill-formed.
//      // Cannot cast array to non-array.

// static_pointer_cast< T > works like static_cast< T * >.
//  example:
//    safely_ptr< const int > px;
//    static_pointer_cast< const int >( px ); // OK.
//    static_pointer_cast< const float >( px ); // ill-formed.
//      // Not convertible const int * to const float *.
//    static_pointer_cast< int >( px ); // ill-formed.
//      // Not convertible const int * to int *.
template < typename T, typename U >
inline safely_ptr< T >
static_pointer_cast( safely_ptr< U > _ptr ) TRANCE_NOEXCEPT
{
    BOOST_MPL_ASSERT(( safely_ptr_detail_::array_or_not< T, U > ));
    return safely_ptr< T >( static_cast<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer
    >( _ptr.get() ) );
}

// reinterpret_pointer_cast< T > works like reinterpret_cast< T * >
//  example:
//    safely_ptr< const int > px;
//    reinterpret_pointer_cast< const int >( px ); // OK.
//    reinterpret_pointer_cast< const float >( px ); // OK.
//    reinterpret_pointer_cast< int >( px ); // ill-formed.
//      // Not convertible const int * to int *.
template < typename T, typename U >
inline safely_ptr< T >
reinterpret_pointer_cast( safely_ptr< U > _ptr ) TRANCE_NOEXCEPT
{
    BOOST_STATIC_ASSERT(( safely_ptr_detail_::array_or_not< T, U >::value ));
    return safely_ptr< T >( reinterpret_cast<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer
    >( _ptr.get() ) );
}

// const_pointer_cast< T > works like const_cast< T * >
//  example:
//    safely_ptr< const int > px;
//    const_pointer_cast< const int >( px ); // OK.
//    const_pointer_cast< const float >( px ); // ill-formed.
//      // Not convertible const int * to const float *.
//    const_pointer_cast< int >( px ); // OK.
template < typename T, typename U >
inline safely_ptr< T >
const_pointer_cast( safely_ptr< U > _ptr ) TRANCE_NOEXCEPT
{
    BOOST_STATIC_ASSERT(( safely_ptr_detail_::array_or_not< T, U >::value ));
    return safely_ptr< T >( const_cast<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer
    >( _ptr.get() ) );
}

// dynamic_pointer_cast< T > works like dynamic_cast< T * >
//  example:
//    struct B { virtual ~B(); };
//    struct D : B {};
//    safely_ptr< B > pb;
//    dynamic_pointer_cast< D >( pb ); // OK.
//    dynamic_pointer_cast< int >( pb ); // ill-formed.
//      // Not convertible B * to int *.
template < typename T, typename U >
inline safely_ptr< T >
dynamic_pointer_cast( safely_ptr< U > _ptr ) TRANCE_NOEXCEPT
{
    BOOST_STATIC_ASSERT(( safely_ptr_detail_::array_or_not< T, U >::value ));
    return safely_ptr< T >( dynamic_cast<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer
    >( _ptr.get() ) );
}

template < typename T >
class safely_ptr
{
public:
    typedef T   element_type;
    typedef T * pointer;
    typedef T & reference;

private:
    pointer _m_ptr;

    void
    _null_check( void ) const
    {
        if ( get() == pointer() )
        { throw nullptr_exception(); }
    }

public:
    TRANCE_CONSTEXPR
    safely_ptr( void ) TRANCE_NOEXCEPT
      : _m_ptr() {}

#if defined( TRANCE_HAS_NULLPTR )
    TRANCE_CONSTEXPR
    safely_ptr( ::std::nullptr_t )
      : _m_ptr() {}
#endif // TRANCE_HAS_NULLPTR

    explicit
    safely_ptr( pointer _ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr ) {}

    safely_ptr( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( static_pointer_cast< element_type >( _ptr ).get() ) {}

#if defined( TRANCE_HAS_RVALUE_REFERENCES )
    safely_ptr( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( static_pointer_cast< element_type >( _ptr ).get() ) {}
#endif // TRANCE_HAS_RVALUE_REFERENCES

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
        static_pointer_cast< element_type >( _ptr ).swap( this );
        return *this;
    }

#if defined( TRANCE_HAS_RVALUE_REFERENCES )
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
        static_pointer_cast< element_type >( _ptr ).swap( this );
        return *this;
    }
#endif // TRANCE_HAS_RVALUE_REFERENCES

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

#if defined( TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS )
    explicit
    operator bool( void ) const TRANCE_NOEXCEPT
    { return get() == pointer() ? true : false; }
#else
    operator safe_bool_t( void ) const TRANCE_NOEXCEPT
    { return safe_bool( get() != pointer() ); }
#endif // !TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS

    pointer
    get( void ) const TRANCE_NOEXCEPT
    { return _m_ptr; }

    pointer
    release( void ) TRANCE_NOEXCEPT
    {
        pointer _p = get();
        _m_ptr = pointer();
        return _p;
    }

    void
    reset( pointer _ptr = pointer() ) TRANCE_NOEXCEPT
    { safely_ptr( _ptr ).swap( *this ); }

    void
    swap( safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        using ::std::swap;
        swap( _m_ptr, _ptr._m_ptr );
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
    pointer _m_ptr;

    void
    _null_check( void ) const
    {
        if ( get() == pointer() )
        { throw nullptr_exception(); }
    }

public:
    TRANCE_CONSTEXPR
    safely_ptr( void ) TRANCE_NOEXCEPT
      : _m_ptr() {}

#if defined( TRANCE_HAS_NULLPTR )
    TRANCE_CONSTEXPR
    safely_ptr( ::std::nullptr_t )
      : _m_ptr() {}
#endif

    explicit
    safely_ptr( pointer _ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr ) {}

    safely_ptr( const safely_ptr &_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( const safely_ptr< U > &_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( static_pointer_cast< element_type[] >( _ptr ).get() ) {}

#if defined( BOOST_HAS_RVALUE_REFS )
    safely_ptr( safely_ptr &&_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( _ptr.get() ) {}

    template < typename U >
    safely_ptr( safely_ptr< U > &&_ptr ) TRANCE_NOEXCEPT
      : _m_ptr( static_pointer_cast< element_type[] >( _ptr ).get() ) {}
#endif // !TRANCE_HAS_RVALUE_REFERENCES

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
        static_pointer_cast< element_type[] >( _ptr ).swap( this );
        return *this;
    }

#if defined( TRANCE_HAS_RVALUE_REFERENCES )
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
        static_pointer_cast< element_type[] >( _ptr ).swap( this );
        return *this;
    }
#endif // TRANCE_HAS_RVALUE_REFERENCES

    reference
    operator[]( ::std::size_t _x ) const
    {
        _null_check();
        return get()[ _x ];
    }

#if defined( TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS )
    explicit
    operator bool( void ) const TRANCE_NOEXCEPT
    { return get() == pointer() ? true : false; }
#endif
    operator safe_bool_t( void ) const TRANCE_NOEXCEPT
    { return safe_bool( get() != pointer() ); }
#endif // TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS

    pointer
    get( void ) const TRANCE_NOEXCEPT
    { return _m_ptr; }

    pointer
    release( void ) TRANCE_NOEXCEPT
    {
        pointer _p = get();
        _m_ptr = pointer();
        return _p;
    }

    void
    reset( pointer _ptr = pointer() ) TRANCE_NOEXCEPT
    { safely_ptr( _ptr ).swap( *this ); }

    void
    swap( safely_ptr &_ptr ) TRANCE_NOEXCEPT
    {
        using ::std::swap;
        swap( _m_ptr, _ptr._m_ptr );
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

#if defined( TRANCE_HAS_NULLPTR )
template < typename T >
inline bool
operator==( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !_x; }

template < typename T >
inline bool
operator==( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !_x; }
#endif // TRANCE_HAS_NULLPTR

template < typename T, typename U >
inline bool
operator!=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _x == _y ); }

#if defined( TRANCE_HAS_NULLPTR )
template < typename T >
inline bool
operator!=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return static_cast< bool >( _x ); }

template < typename T >
inline bool
operator!=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return static_cast< bool >( _x ); }
#endif // TRANCE_HAS_NULLPTR

template < typename T, typename U >
inline bool
operator<( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{
    typedef BOOST_DEDUCED_TYPENAME ::boost::common_type<
      BOOST_DEDUCED_TYPENAME safely_ptr< T >::pointer,
      BOOST_DEDUCED_TYPENAME safely_ptr< U >::pointer
    >::type CT;
    return ::std::less< CT >( _x.get(), _y.get() );
}

#if defined( TRANCE_HAS_NULLPTR )
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
#endif // TRANCE_HAS_NULLPTR

template < typename T, typename U >
inline bool
operator<=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _y < _x ); }

#if defined( TRANCE_HAS_NULLPTR )
template < typename T >
inline bool
operator<=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !( nullptr < _x ); }

template < typename T >
inline bool
operator<=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !( _x < nullptr ); }
#endif // TRANCE_HAS_NULLPTR

template < typename T, typename U >
inline bool
operator>( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return _y < _x; }

#if defined( TRANCE_HAS_NULLPTR )
template < typename T >
inline bool
operator>( const safely_ptr< T > &_x, ::std:nullptr_t ) TRANCE_NOEXCEPT
{ return nullptr < _x; }

template < typename T >
inline bool
operator>( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return _x < nullptr; }
#endif // TRANCE_HAS_NULLPTR

template < typename T, typename U >
inline bool
operator>=( const safely_ptr< T > &_x,
  const safely_ptr< U > &_y ) TRANCE_NOEXCEPT
{ return !( _x < _y ); }

#if defined( TRANCE_HAS_NULLPTR )
template < typename T >
inline bool
operator>=( const safely_ptr< T > &_x, ::std::nullptr_t ) TRANCE_NOEXCEPT
{ return !( _x < nullptr ); }

template < typename T >
inline bool
operator>=( ::std::nullptr_t, const safely_ptr< T > &_x ) TRANCE_NOEXCEPT
{ return !( nullptr < _x ); }
#endif // TRANCE_HAS_NULLPTR

} // namespace trance

namespace std
{

template < typename >
struct hash;

// std::hash specialization for trance::safely_ptr.
template < typename T >
struct hash< ::trance::safely_ptr< T > >
{
    typedef size_t result_type;
    typedef ::trance::safely_ptr< T > argument_type;

    result_type
    operator()( const argument_type &_x ) const
    {
        return std::hash<
          BOOST_DEDUCED_TYPENAME argument_type::pointer
        >()( _x.get() );
    }
};

} // namespace std

#endif // IG_TRANCE_SAFELY_PTR_HPP_ONCE_

