// trance ref.hpp - Reference wrapper class and utilties
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

#ifndef IG_TRANCE_REF_HPP_ONCE_
#define IG_TRANCE_REF_HPP_ONCE_

#include <trance/config.hpp>

#if BOOST_VERSION < 102500
#   error "Boost.Ref support after 1.25.0."
#endif

#include <boost/ref.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace trance
{

using boost::reference_wrapper;
using boost::ref;
using boost::cref;
using boost::is_reference_wrapper;
using boost::unwrap_reference;
#if 104000 <= BOOST_VERSION
using boost::unrwrap_ref;
#endif

namespace result_of
{

template < typename T >
struct ref
{
    typedef boost::reference_wrapper<
      typename boost::remove_reference<
        typename boost::unwrap_reference< T >::type
      >::type
    > type;
};

template < typename T >
struct cref
{
    typedef boost::reference_wrapper<
      const typename boost::remove_reference<
        typename boost::unwrap_reference< T >::type
      >::type
    > type;
};

#if 104000 <= BOOST_VERSION
template < typename T >
struct unwrap_ref
{
    typedef typename boost::unwrap_reference< T >::type & type;
};
#endif

} // namespace result_of

} // namespace trance

#endif // IG_TRANCE_REF_HPP_ONCE_

