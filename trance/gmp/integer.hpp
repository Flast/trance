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

#include <iosfwd>
#include <cstring>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/switch.hpp>
#include <boost/mpl/always.hpp>

#include <boost/type_traits/is_convertible.hpp>

#ifndef TRANCE_GMP_DO_NOT_USE_HEADER
#   include <gmp.h>
#   define TRANCE_GMP_DO_NOT_USE_HEADER
#endif // TRANCE_GMP_DO_NOT_USE_HEADER

#include <trance/as_const.hpp>

namespace trance
{

namespace gmp
{

namespace gmp_detail
{

template < typename T >
struct case_
  : public ::boost::mpl::pair<
      ::boost::is_convertible< ::boost::mpl::_1, T >,
      ::boost::mpl::always< T >
    > {};

template < typename T >
struct default_
  : public ::boost::mpl::pair<
      ::boost::mpl::true_,
      ::boost::mpl::always< T >
    > {};

} // namespace gmp_detail

//template < typename Alloc >
class integer_type
{
    typedef mpz_t _internal_type;

    _internal_type _M_internal;
    bool           _M_is_initialized;

private:
    void
    _init( void ) TRANCE_NOEXCEPT
    {
        if ( !_M_is_initialized )
        {
            mpz_init( _M_internal );
            _M_is_initialized = true;
        }
    }

    void
    _clear( void ) TRANCE_NOEXCEPT
    {
        if ( _M_is_initialized )
        {
            mpz_clear( _M_internal );
            _M_is_initialized = false;
        }
    }

    void
    _reset_impl( unsigned long op ) TRANCE_NOEXCEPT
    {
        mpz_set_ui( _M_internal, op );
    }

    void
    _reset_impl( signed long op ) TRANCE_NOEXCEPT
    {
        mpz_set_si( _M_internal, op );
    }

    void
    _reset_impl( double op ) TRANCE_NOEXCEPT
    {
        mpz_set_d( _M_internal, op );
    }

    void
    _reset_impl( const integer_type &op ) TRANCE_NOEXCEPT
    {
        mpz_set( _M_internal, op._M_internal );
    }

public:
    typedef _internal_type value_type;

    // default ctor
    integer_type( void ) TRANCE_NOEXCEPT
      : _M_is_initialized( false )
    {
        reset();
    }

    integer_type( const integer_type &op ) TRANCE_NOEXCEPT
      : _M_is_initialized( false )
    {
        reset( op );
    }

    template < typename T >
    integer_type( const T &op ) TRANCE_NOEXCEPT
      : _M_is_initialized( false )
    {
        reset( op );
    }

    ~integer_type( void ) TRANCE_NOEXCEPT
    {
        _clear();
    }

    integer_type &
    operator=( const integer_type &op ) TRANCE_NOEXCEPT
    {
        reset( op );
        return *this;
    }

    template < typename T >
    integer_type &
    operator=( const T &op ) TRANCE_NOEXCEPT
    {
        reset( op );
        return *this;
    }

    void
    reset( void ) TRANCE_NOEXCEPT
    {
        _clear();
        _init();
    }

    template < typename T >
    void
    reset( const T &op ) TRANCE_NOEXCEPT
    {
        _init();

        typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::switch_<
          ::boost::mpl::vector<
            gmp_detail::case_< unsigned long >,
            gmp_detail::case_< signed long >,
            gmp_detail::case_< double >,
            gmp_detail::case_< const integer_type & >,
            gmp_detail::default_< unsigned long >
          >,
          T
        >::type result_type;
        _reset_impl( static_cast< result_type >( op ) );
    }

    void
    reset( /*const*/ char *str, int base = 10 )
    {
        _init();
        mpz_set_str( _M_internal, str, base );
        // TODO: check error
    }

    void
    swap( integer_type &rop ) TRANCE_NOEXCEPT
    {
        mpz_swap( _M_internal, rop._M_internal );
    }

    friend integer_type &
    operator+=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator+=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    friend integer_type &
    operator-=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator-=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    friend integer_type &
    operator*=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator*=( integer_type &, signed long ) TRANCE_NOEXCEPT;
    //friend integer_type &
    //operator*=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT;

    template < typename _CharT, typename _Traits >
    friend ::std::basic_ostream< _CharT, _Traits > &
    operator<<( ::std::basic_ostream< _CharT, _Traits > &,
      const integer_type & );

    //template < typename _CharT, typename _Traits >
    //friend ::std::basic_istream< _CharT, _Traits > &
    //operator>>( ::std::basic_istream< _CharT, _Traits > &, integer_type & );
};

integer_type &
operator+=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_add( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

integer_type &
operator+=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
{
    mpz_add_ui( rop._M_internal, rop._M_internal, op );
    return rop;
}

integer_type &
operator-=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_sub( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

integer_type &
operator-=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
{
    mpz_sub_ui( rop._M_internal, rop._M_internal, op );
    return rop;
}

integer_type &
operator*=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_mul( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

integer_type &
operator*=( integer_type &rop, signed long op ) TRANCE_NOEXCEPT
{
    mpz_mul_si( rop._M_internal, rop._M_internal, op );
    return rop;
}

//integer_type &
//operator*=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
//{
//    mpz_mul_ui( rop._M_internal, rop._M_internal, op );
//    return rop;
//}

template < typename _CharT, typename _Traits >
::std::basic_ostream< _CharT, _Traits > &
operator<<( ::std::basic_ostream< _CharT, _Traits > &ostr,
  const integer_type &op )
{
    void ( *_free )( void *, size_t );
    mp_get_memory_functions( 0, 0, &_free );
    if ( !_free )
    {
        // TODO
        throw;
    }

    char *str = mpz_get_str( 0, 10, op._M_internal );
    ostr << as_const( str );

    _free( str, ::std::strlen( str ) + 1 );

    return ostr;
}

//template < typename _CharT, typename _Traits >
//::std::basic_istream< _CharT, _Traits > &
//operator>>( ::std::basic_istream< _CharT, _Traits > &ostr, integer_type &op )
//{
//}

} // namespace gmp

} // namespace trance

#endif // IG_TRANCE_GMP_INTEGER_HPP_ONCE_

