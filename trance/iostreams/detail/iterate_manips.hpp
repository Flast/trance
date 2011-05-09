// trance iterate_manips.hpp - Iterate Escape Sequence Manipulator
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

#ifndef IG_TRANCE_IOSTREAMS_DETAIL_ITERATE_MANIPS_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_DETAIL_ITERATE_MANIPS_HPP_ONCE_

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#endif // IG_TRANCE_IOSTREAMS_DETAIL_ITERATE_MANIPS_HPP_ONCE_

#define TRANCE_IOSTREAMS_MANIPS_FILE  BOOST_PP_TUPLE_ELEM( 3, 0, ITERATE_MANIPS_INFO )
#define TRANCE_IOSTREAMS_MANIPS_COUNT BOOST_PP_TUPLE_ELEM( 3, 1, ITERATE_MANIPS_INFO )
#define TRANCE_IOSTREAMS_MANIPS       BOOST_PP_TUPLE_ELEM( 3, 2, ITERATE_MANIPS_INFO )

#define BOOST_PP_ITERATION_PARAMS_1 ( 3, (        \
  0,                                              \
  BOOST_PP_DEC( TRANCE_IOSTREAMS_MANIPS_COUNT ),  \
  TRANCE_IOSTREAMS_MANIPS_FILE ) )
#include BOOST_PP_ITERATE()

#undef TRANCE_IOSTREAMS_MANIPS
#undef TRANCE_IOSTREAMS_MANIPS_COUNT
#undef TRANCE_IOSTREAMS_MANIPS_FILE
#undef ITERATE_MANIPS_INFO

