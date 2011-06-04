// trance integer.hpp - GMP integer type
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

#ifndef IG_TRANCE_GMP_INTEGER_HPP_ONCE_
#define IG_TRANCE_GMP_INTEGER_HPP_ONCE_

#include <trance/config.hpp>

#include <cstring>
#include <iosfwd>
#include <algorithm> // for iter_swap

#include <boost/utility/enable_if.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/proto/proto.hpp>

#include <trance/as_const.hpp>

#include <trance/gmp/config.hpp>

#include <trance/proto/result_of.hpp>

namespace trance
{

namespace gmp
{

class integer;

namespace integer_detail
{

namespace bproto = ::boost::proto;

struct grammar
  : public bproto::or_<
      bproto::terminal< bproto::_ >
    , bproto::plus< grammar, grammar >
    //, bproto::minus< grammar, grammar >
    //, bproto::multiplies< grammar, grammar >
    //, bproto::divides< grammar, grammar >
    > {};

template < typename >
struct expression;

struct domain
  : public bproto::domain< bproto::generator< expression >, grammar > {};

template < typename _Expr >
struct expression
  : public bproto::extends< _Expr, expression< _Expr >, domain >
{
    typedef bproto::extends< _Expr, expression< _Expr >, domain > _base_t;

    expression( void )
      : _base_t( _Expr() ) {}

    expression( const _Expr &expr )
      : _base_t( expr ) {}
};

template < typename _ValueType >
class context
{
    typedef _ValueType _target_type;
    _target_type *_M_target;

public:
    explicit
    context( _target_type &_target )
      : _M_target( &_target ) {}

    template < typename, typename = void >
    struct eval;
};

} // namespace integer_detail

class integer
{
    template < typename >
    friend class integer_detail::context;

    template < typename _CharT, typename _CharTraits >
    friend ::std::basic_ostream< _CharT, _CharTraits > &
    operator<<( ::std::basic_ostream< _CharT, _CharTraits > &, const integer & );

    typedef mpz_t _internal_type;

    _internal_type _M_internal;

    typedef integer_detail::context< integer > _integer_context;

public:
    integer( void ) TRANCE_NOEXCEPT
    { mpz_init( _M_internal ); }

    integer( const integer &_other ) TRANCE_NOEXCEPT
    {
        mpz_init( _M_internal );
        mpz_set( _M_internal, _other._M_internal );
    }

#ifdef TRANCE_HAS_RVALUE_REFERENCES
    integer( integer &&_other ) TRANCE_NOEXCEPT
    { this->swap( _other ); }
#endif // TRANCE_HAS_RVALUE_REFERENCES

    template < typename _Expr >
    integer( const integer_detail::expression< _Expr > &expr )
    {
        mpz_init( _M_internal );

        // evalute and copy
        ::boost::proto::eval( expr, _integer_context( *this ) );
    }

    ~integer( void )
    { mpz_clear( _M_internal ); } TRANCE_NOEXCEPT

    integer &
    operator=( const integer &_other ) TRANCE_NOEXCEPT
    {
        mpz_set( _M_internal, _other._M_internal );
        return *this;
    }

#ifdef TRANCE_HAS_RVALUE_REFERENCES
    integer &
    operator=( integer &&_other ) TRANCE_NOEXCEPT
    {
        this->swap( _other );
        return *this;
    }
#endif // TRANCE_HAS_RVALUE_REFERENCES

    void
    swap( integer &_other ) TRANCE_NOEXCEPT
    { ::std::iter_swap( &_M_internal, &_other._M_internal ); }
};

template < typename >
struct is_integer
  : public ::boost::mpl::false_ {};

template <>
struct is_integer< integer >
  : public ::boost::mpl::true_ {};

BOOST_PROTO_DEFINE_OPERATORS( is_integer, integer_detail::domain )

template < typename _CharT, typename _CharTraits >
::std::basic_ostream< _CharT, _CharTraits > &
operator<<( ::std::basic_ostream< _CharT, _CharTraits > &_ostr, const integer &_value )
{
    struct _free_functor
    {
        typedef void _free( void *, size_t );

        _free *_M_free;
        char  *_M_str;

        _free_functor( void )
        {
            mp_get_memory_functions( 0, 0, &_M_free );
            if ( !_M_free )
            { throw; } // TODO
        }

        ~_free_functor( void )
        { _M_free( _M_str, ::std::strlen( _M_str ) + 1 ); }

        void
        set( char *str ) TRANCE_NOEXCEPT
        { _M_str = str; }

        char *
        get( void ) const TRANCE_NOEXCEPT
        { return _M_str; }
    } deleter;
    deleter.set( mpz_get_str( 0, 10, _value._M_internal ) );

    _ostr << as_const( deleter.get() );
    return _ostr;
}

namespace integer_detail
{

template < typename _CharT, typename _CharTraits, typename Expr >
::std::basic_ostream< _CharT, _CharTraits > &
operator<<(
  ::std::basic_ostream< _CharT, _CharTraits > &_ostr
, const expression< Expr > &_expr )
{
    typedef context< integer > icontext;

    integer i;
    _ostr << ::boost::proto::eval( _expr, icontext( i ) );
    return _ostr;
}

template < typename _target_type >
template < typename _Expr >
struct context< _target_type >::eval<
  _Expr
, typename ::boost::enable_if<
    bproto::matches< _Expr, bproto::terminal< bproto::_ > >
  >::type
>
{
    typedef context< _target_type > _this_context;
    typedef _target_type & result_type;

    result_type
    operator()( _Expr &expr, const _this_context &ctx ) const
    { return _eval_impl( expr, ctx ); }

    template < typename Expr >
    typename ::boost::enable_if<
      ::boost::is_same<
        typename bproto::result_of::value< Expr >::type
      , integer
      >
    , result_type
    >::type
    _eval_impl( Expr &expr, const _this_context &ctx ) const
    {
        mpz_set(
          ctx._M_target->_M_internal
        , bproto::value( expr )._M_internal
        );
        return *ctx._M_target;
    }
};

template < typename _target_type >
template < typename _Expr >
struct context< _target_type >::eval<
  _Expr
, typename ::boost::enable_if<
    bproto::matches<
      _Expr
    , bproto::plus< bproto::_, bproto::_ >
    >
  >::type
>
{
    typedef context< _target_type > _this_context;
    typedef _target_type & result_type;

    result_type
    operator()( _Expr &expr, const _this_context &ctx ) const
    { return _eval_impl( expr, ctx ); }

    template < typename Expr >
    typename ::boost::enable_if<
      ::boost::mpl::and_<
        ::boost::is_same<
          typename proto::left_result_of< Expr, _this_context >::type
        , integer
        >
      , ::boost::is_same<
          typename proto::right_result_of< Expr, _this_context >::type
        , integer
        >
      >
    , result_type
    >::type
    _eval_impl( Expr &expr, const _this_context &ctx ) const
    {
        typedef context< integer > icontext;
        using namespace bproto;

        integer tmp;
        integer &ltarget = bproto::eval( left( expr ), ctx );
        integer &rtarget = bproto::eval( right( expr ), icontext( tmp ) );

        mpz_add(
          ctx._M_target->_M_internal
        , ltarget._M_internal
        , rtarget._M_internal
        );
        return *ctx._M_target;
    }
};

} // namespace integer_detail

} // namespace gmp

} // namespace trance

#endif // IG_TRANCE_GMP_INTEGER_HPP_ONCE_

