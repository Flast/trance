// trance memory.hpp - Memory manager for GMP
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

#ifndef IG_TRANCE_GMP_MEMORY_HPP_ONCE_
#define IG_TRANCE_GMP_MEMORY_HPP_ONCE_

#include <trance/config.hpp>

#include <cstddef>
#include <iostream>

#include <boost/preprocessor/cat.hpp>

#include <boost/unordered_map.hpp>

#include <trance/gmp/config.hpp>

namespace trance
{

namespace gmp
{

namespace memory
{

struct leak_checker
{
    typedef ::std::size_t size_type;
    typedef ::boost::unordered_map< void *, size_type > memory_map_type;

    typedef void * _alloc_func_t( size_type );
    typedef void * _realloc_func_t( void *, size_type, size_type );
    typedef void   _dealloc_func_t( void *, size_type );

private:
    static leak_checker *_M_checker_chain;

    static void *
    _allocator( size_type _size ) TRANCE_NOEXCEPT
    {
        leak_checker * const _tmp = _M_checker_chain;
        _M_checker_chain = _tmp->_M_prev_chain;

        void * const _mem = _tmp->_M_alloc_func( _size );
        _tmp->_M_memory_map.insert( memory_map_type::value_type( _mem, _size ) );

        _M_checker_chain = _tmp;
        return _mem;
    }

    static void *
    _reallocator( void * const _old, size_type _old_size,
      size_type _new_size ) TRANCE_NOEXCEPT
    {
        leak_checker * const _tmp = _M_checker_chain;
        _M_checker_chain = _tmp->_M_prev_chain;

        void * const _mem = _tmp->_M_realloc_func( _old, _old_size, _new_size );
        _tmp->_M_memory_map.erase( _old );
        _tmp->_M_memory_map.insert(
          memory_map_type::value_type( _mem, _new_size )
        );

        _M_checker_chain = _tmp;
        return _mem;
    }

    static void
    _deallocator( void * const _mem, size_type _size ) TRANCE_NOEXCEPT
    {
        leak_checker * const _tmp = _M_checker_chain;
        _M_checker_chain = _tmp->_M_prev_chain;

        _tmp->_M_dealloc_func( _mem, _size );
        _tmp->_M_memory_map.erase( _mem );

        _M_checker_chain = _tmp;
    }

    leak_checker( const leak_checker & )
#if !defined( BOOST_NO_DELETED_FUNCTIONS )
      = delete
#endif
      ;

    leak_checker &
    operator=( const leak_checker & )
#if !defined( BOOST_NO_DELETED_FUNCTIONS )
      = delete
#endif
      ;

    leak_checker    *_M_prev_chain;
    ::std::ostream  *_M_ostr;
    memory_map_type _M_memory_map;

    _alloc_func_t   *_M_alloc_func;
    _realloc_func_t *_M_realloc_func;
    _dealloc_func_t *_M_dealloc_func;

public:
    leak_checker( void )
      : _M_ostr( 0 ),
        _M_prev_chain( _M_checker_chain )
    {
        _M_checker_chain = this;

        mp_get_memory_functions(
          &_M_alloc_func,
          &_M_realloc_func,
          &_M_dealloc_func
        );
        mp_set_memory_functions(
          _allocator,
          _reallocator,
          _deallocator
        );
    }

    ~leak_checker( void ) TRANCE_NOEXCEPT
    {
        _M_checker_chain = _M_prev_chain;
        if ( _M_memory_map.size() )
        {
            // Do not use std::endl to output message completly.
            *_M_ostr << "!! Trance.GMP memory leak !!\n";
        }
        _M_memory_map.clear();

        mp_set_memory_functions(
          _M_alloc_func,
          _M_realloc_func,
          _M_dealloc_func
        );
    }

    void
    _set_ostream( ::std::ostream &ostr = ::std::cerr )
    {
        _M_ostr = &ostr;
    }
};

#define TRANCE_GMP_ENABLE_LEAK_CHECK()                                      \
  namespace trance { namespace gmp { namespace memory {                     \
  leak_checker *leak_checker::_M_checker_chain = 0;                         \
  } } }                                                                     \
  typedef ::trance::gmp::memory::leak_checker TRANCE_GMP_LEAK_CHECK_ENABLED \

#define TRANCE_GMP_USE_SCOPED_LEAK_CHECK                               \
  ::trance::gmp::memory::leak_checker                                  \
    BOOST_PP_CAT( TRANCE_GMP_SCOPED_LEAK_CHECK_, __LINE__ );           \
  BOOST_PP_CAT( TRANCE_GMP_SCOPED_LEAK_CHECK_, __LINE__ )._set_ostream \

} // namespace memory

} // namespace gmp

} // namespace trance

#endif // IG_TRANCE_GMP_MEMORY_HPP_ONCE_

