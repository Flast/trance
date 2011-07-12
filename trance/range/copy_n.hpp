// trance copy_n.hpp - Extended copy algorithm.
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

#ifndef IG_TRANCE_RANGE_COPY_N_HPP_ONCE_
#define IG_TRANCE_RANGE_COPY_N_HPP_ONCE_

#include <boost/range/concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <trance/algorithm/copy_n.hpp>

namespace trance
{

namespace range
{

template < typename SinglePassRange, typename Size, typename OutputIterator >
inline OutputIterator
copy_n( const SinglePassRange &range, Size _n, OutputIterator _result )
{
    using namespace boost;
    BOOST_RANGE_CONCEPT_ASSERT(( SinglePassRangeConcept< const SinglePassRange > ));

    return ::trance::copy_n( boost::begin( range ), boost::end( range ), _n, _result );
}

} // namespace range

using range::copy_n;

} // namespace trance

#endif // IG_TRANCE_RANGE_COPY_N_HPP_ONCE_

