// trance value_holder.hpp - Value holder for conditions in statement.
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

#ifndef IG_TRANCE_VALUE_HOLDER_HPP_ONCE_
#define IG_TRANCE_VALUE_HOLDER_HPP_ONCE_

#include <trance/config.hpp>

#if defined( TRANCE_HAS_RVALUE_REFERENCES )
#   include <utility>
#endif // TRANCE_HAS_RVALUE_REFERENCES

#include <boost/function.hpp>

#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_reference.hpp>

#if !defined( TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS )
#   include <trance/safe_bool.hpp>
#endif // TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS

namespace trance
{

namespace value_holder_detail_
{

struct _default_evaluator
{
    template < typename T >
    bool
    operator()( const T &_value ) TRANCE_NOEXCEPT
    { return static_cast< bool >( _value ); }
};

} // namespace value_holder_detail_

template <
  typename T
, typename Predicate = ::boost::function< bool( T ) >
>
struct value_holder
{
    template < typename, typename >
    friend class value_holder;

private:
    T         _m_value, * const _m_indirect_value;
    Predicate _m_pred;

    inline bool
    _internal_condition( void ) const TRANCE_NOEXCEPT
    { return _m_pred( ::boost::ref( *_m_indirect_value ) ); }

public:
    template < typename U, typename P >
    value_holder( const value_holder< U, P > &_vh )
      : _m_value( _vh._m_value ), _m_indirect_value( &_m_value )
      , _m_pred( _vh._m_pred ) {}

#if !defined( TRANCE_HAS_RVALUE_REFERENCES )
    value_holder( const T &_value )
      : _m_value( _value ), _m_indirect_value( &_m_value )
      , _m_pred( value_holder_detail_::_default_evaluator() ) {}

    template < typename P >
    value_holder( const T &_value, P _pred )
      : _m_value( _value ), _m_indirect_value( &_m_value )
      , _m_pred( _pred ) {}
#else
    template < typename U, typename P >
    value_holder( value_holder< U, P > &&_vh )
      : _m_value( ::std::move( _vh._m_value ) ), _m_indirect_value( &_m_value )
      , _m_pred( ::std::move( _vh._m_pred ) ) {}

    template < typename U >
    value_holder( U &&_value )
      : _m_value( ::std::forward< U >( _value ) )
      , _m_indirect_value( &_m_value )
      , _m_pred( value_holder_detail_::_default_evaluator() ) {}

    template < typename U, typename P >
    value_holder( U &&_value, P _pred )
      : _m_value( ::std::forward< U >( _value ) )
      , _m_indirect_value( &_m_value ), _m_pred( _pred ) {}
#endif // TRANCE_HAS_RVALUE_REFERENCES

#if !defined( TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS )
    operator safe_bool_t( void ) const TRANCE_NOEXCEPT
    { return safe_bool( _internal_condition() ); }
#else
    explicit
    operator bool( void ) const TRANCE_NOEXCEPT
    { return _internal_condition(); }
#endif // TRANCE_HAS_EXPLICIT_CONVERSION_OPERATORS

    T &
    get( void ) TRANCE_NOEXCEPT
    { return _m_value; }

    const T &
    get( void ) const TRANCE_NOEXCEPT
    { return _m_value; }
};

#if !defined( TRANCE_HAS_RVALUE_REFERENCES )
template < typename T >
value_holder< typename ::boost::remove_reference< T >::type >
make_holder( T &&_value )
{ return value_holder< typename ::boost::remove_reference< T >::type >( ::std::forward< T >( _value ) ); }

template < typename T, typename P >
value_holder< typename ::boost::remove_reference< T >::type, P >
make_holder( T &&_value, P _pred )
{ return value_holder< typename ::boost::remove_reference< T >::type, P >( std::forward< T >( _value ), _pred ); }
#else
template < typename T >
value_holder< T >
make_holder( T &_value )
{ return value_holder< T >( _value ); }

template < typename T >
value_holder< const T >
make_holder( const T &_value )
{ return value_holder< const T >( _value ); }

template < typename T, typename P >
value_holder< T, P >
make_holder( T &_value, P _pred )
{ return value_holder< T, P >( _value, _pred ); }

template < typename T, typename P >
value_holder< const T, P >
make_holder( const T &_value, P _pred )
{ return value_holder< const T, P >( _value, _pred ); }
#endif

} // namespace trance

#endif // IG_TRANCE_VALUE_HOLDER_HPP_ONCE_

