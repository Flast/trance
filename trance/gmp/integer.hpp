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

#include <boost/operators.hpp>

#include <trance/as_const.hpp>

#include <trance/gmp/config.hpp>

namespace trance
{

namespace gmp
{

//template < typename Alloc >
class integer_type
  : private ::boost::totally_ordered< integer_type >,
    private ::boost::totally_ordered< integer_type, double >,
    // +=, -=, *=, /=, %=
    private ::boost::integer_arithmetic< integer_type >,
    private ::boost::integer_arithmetic< integer_type, double >,
    // &=, |=, ^=
    private ::boost::bitwise< integer_type >,
    private ::boost::bitwise< integer_type, signed long >
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

    void
    reset( const integer_type &op ) TRANCE_NOEXCEPT
    {
        _init();
        mpz_set( _M_internal, op._M_internal );
    }

    //void
    //reset( unsigned long op ) TRANCE_NOEXCEPT
    //{
    //    _init();
    //    mpz_set_ui( _M_internal, op );
    //}

    void
    reset( signed long op ) TRANCE_NOEXCEPT
    {
        _init();
        mpz_set_si( _M_internal, op );
    }

    //void
    //reset( double op ) TRANCE_NOEXCEPT
    //{
    //    _init();
    //    mpz_set_d( _M_internal, op );
    //}

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

    bool
    operator!( void ) const TRANCE_NOEXCEPT
    {
        return *this == 0;
    }

    // Boost.Operators, less_than_comparable requires
    friend bool
    operator<( const integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend bool
    operator<( const integer_type &, double ) TRANCE_NOEXCEPT;
    friend bool
    operator>( const integer_type &, double ) TRANCE_NOEXCEPT;

    // Boost.Operators, equality_comparable requires
    friend bool
    operator==( const integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend bool
    operator==( const integer_type &, double ) TRANCE_NOEXCEPT;

    // Boost.Operators, addable requires
    friend integer_type &
    operator+=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator+=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    // Boost.Operators, subtractable requires
    friend integer_type &
    operator-=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator-=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    // Boost.Operators, multipliable requires
    friend integer_type &
    operator*=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator*=( integer_type &, signed long ) TRANCE_NOEXCEPT;
    //friend integer_type &
    //operator*=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT;

    // Boost.Operators, dividable requires
    friend integer_type &
    operator/=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator/=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    // Boost.Operators, modable requires
    friend integer_type &
    operator%=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator%=( integer_type &, unsigned long ) TRANCE_NOEXCEPT;

    // Boost.Operators, bitwise requires
    friend integer_type &
    operator&=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator|=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;
    friend integer_type &
    operator^=( integer_type &, const integer_type & ) TRANCE_NOEXCEPT;

    template < typename _CharT, typename _Traits >
    friend ::std::basic_ostream< _CharT, _Traits > &
    operator<<( ::std::basic_ostream< _CharT, _Traits > &,
      const integer_type & );

    //template < typename _CharT, typename _Traits >
    //friend ::std::basic_istream< _CharT, _Traits > &
    //operator>>( ::std::basic_istream< _CharT, _Traits > &, integer_type & );
};

inline bool
operator<( const integer_type &_x, const integer_type &_y ) TRANCE_NOEXCEPT
{
    return mpz_cmp( _x._M_internal, _y._M_internal ) < 0;
}

inline bool
operator<( const integer_type &_x, double _y ) TRANCE_NOEXCEPT
{
    return mpz_cmp_d( _x._M_internal, _y ) < 0;
}

inline bool
operator>( const integer_type &_x, double _y ) TRANCE_NOEXCEPT
{
    return mpz_cmp_d( _x._M_internal, _y ) > 0;
}

inline bool
operator==( const integer_type &_x, const integer_type &_y ) TRANCE_NOEXCEPT
{
    return !mpz_cmp( _x._M_internal, _y._M_internal );
}

inline bool
operator==( const integer_type &_x, double _y ) TRANCE_NOEXCEPT
{
    return !mpz_cmp_d( _x._M_internal, _y );
}

inline integer_type &
operator+=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_add( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

inline integer_type &
operator+=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
{
    mpz_add_ui( rop._M_internal, rop._M_internal, op );
    return rop;
}

inline integer_type &
operator-=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_sub( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

inline integer_type &
operator-=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
{
    mpz_sub_ui( rop._M_internal, rop._M_internal, op );
    return rop;
}

inline integer_type &
operator*=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_mul( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

inline integer_type &
operator*=( integer_type &rop, signed long op ) TRANCE_NOEXCEPT
{
    mpz_mul_si( rop._M_internal, rop._M_internal, op );
    return rop;
}

//inline integer_type &
//operator*=( integer_type &rop, unsigned long op ) TRANCE_NOEXCEPT
//{
//    mpz_mul_ui( rop._M_internal, rop._M_internal, op );
//    return rop;
//}

inline integer_type &
operator/=( integer_type &_n, const integer_type &_d ) TRANCE_NOEXCEPT
{
    mpz_divexact( _n._M_internal, _n._M_internal, _d._M_internal );
    return _n;
}

inline integer_type &
operator/=( integer_type &_n, unsigned long _d ) TRANCE_NOEXCEPT
{
    mpz_divexact_ui( _n._M_internal, _n._M_internal, _d );
    return _n;
}

inline integer_type &
operator%=( integer_type &_n, const integer_type &_d ) TRANCE_NOEXCEPT
{
    mpz_mod( _n._M_internal, _n._M_internal, _d._M_internal );
    return _n;
}

inline integer_type &
operator%=( integer_type &_n, unsigned long _d ) TRANCE_NOEXCEPT
{
    mpz_mod_ui( _n._M_internal, _n._M_internal, _d );
    return _n;
}

inline integer_type &
operator&=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_and( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

inline integer_type &
operator|=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_ior( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

inline integer_type &
operator^=( integer_type &rop, const integer_type &op ) TRANCE_NOEXCEPT
{
    mpz_xor( rop._M_internal, rop._M_internal, op._M_internal );
    return rop;
}

template < typename _CharT, typename _Traits >
inline ::std::basic_ostream< _CharT, _Traits > &
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
//inline ::std::basic_istream< _CharT, _Traits > &
//operator>>( ::std::basic_istream< _CharT, _Traits > &ostr, integer_type &op )
//{
//}

} // namespace gmp

} // namespace trance

#endif // IG_TRANCE_GMP_INTEGER_HPP_ONCE_

