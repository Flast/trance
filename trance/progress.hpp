// trance progress.hpp - Progress Library
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

#ifndef IG_TRANCE_PROGRESS_HPP_ONCE_
#define IG_TRANCE_PROGRESS_HPP_ONCE_

#include <trance/config.hpp>

#include <iostream>
#include <string>

#include <boost/noncopyable.hpp>

namespace trance
{

class progress_display
  : private ::boost::noncopyable
{
protected:
    typedef unsigned int   count_type;
    typedef ::std::ostream stream_type;

    progress_display( count_type _expected, stream_type &_ostr ) TRANCE_NOEXCEPT
      : _M_ostr( _ostr ),
        _M_count( 0 ), _M_expected( _expected ? _expected : 1u ) {}

    stream_type &
    _ostr( void ) TRANCE_NOEXCEPT
    { return _M_ostr; }

    virtual void
    _restart_impl( void ) {}

    virtual void
    _display_tic_impl( void ) {}

private:
    stream_type &_M_ostr;
    count_type _M_count, _M_expected;

public:
    void
    restart( count_type _expected )
    {
        _M_count = 0u;
        _M_expected = _expected ? _expected : 1u;
        _restart_impl();
    }

    progress_display &
    operator+=( count_type _x )
    {
        _M_count += _x;
        _display_tic_impl();
        return *this;
    }

    inline progress_display &
    operator++( void )
    { return operator+=( 1u ); }

    inline count_type
    count( void ) const TRANCE_NOEXCEPT
    { return _M_count; }

    inline count_type
    expected_count( void ) const TRANCE_NOEXCEPT
    { return _M_expected; }
};

// same as boost::progress_display
class boost_progress_display
  : public progress_display
{
    const ::std::string _M_s1, _M_s2, _M_s3;
    count_type _M_next_tic, _M_tic;

    void
    _restart_impl( void )
    {
        _M_next_tic = _M_tic = 0;

        _ostr() << ::std::endl
          << _M_s1 << "0%   10   20   30   40   50   60   70   80   90   100%\n"
          << _M_s2 << "|----|----|----|----|----|----|----|----|----|----|"
          << ::std::endl
          << _M_s3;
    }

    void
    _display_tic_impl( void )
    {
        if ( count() < _M_next_tic )
        { return; }

        const count_type tics_needed = count() * 50.0 / expected_count();

        do
        { _ostr() << '*' << ::std::flush; }
        while ( ++_M_tic < tics_needed );

        _M_next_tic = _M_tic / 50.0 * expected_count();
        if ( count() == expected_count() )
        {
            if ( _M_tic < 51 )
            { _ostr() << '*'; }
            _ostr() << ::std::endl;
        }
    }

    using progress_display::operator+=;
    using progress_display::operator++;

public:
    // basic ctor (same as boost::progress_display's)
    explicit
    boost_progress_display(
      count_type _expected,
      stream_type &_ostr = ::std::cout,
      const ::std::string &_s1 = "",
      const ::std::string &_s2 = "",
      const ::std::string &_s3 = "" )
      : progress_display( _expected, _ostr ),
        _M_s1( _s1 ), _M_s2( _s2 ), _M_s3( _s3 )
    { restart( _expected ); }

    // name hiding
    count_type
    operator+=( count_type _x )
    {
        progress_display::operator+=( _x );
        return _x;
    }

    // name hiding
    inline count_type
    operator++( void )
    { return operator+=( 1u ); }
};

} // namespace trance

#endif // IG_TRANCE_PROGRESS_HPP_ONCE_

