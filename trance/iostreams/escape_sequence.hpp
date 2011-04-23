// trance escape_sequence.hpp - Generic Escape Sequence Manipulator
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

#ifndef IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_
#define IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_

#include <trance/config.hpp>

#include <iosfwd>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iterate.hpp>

namespace trance
{

namespace iostreams
{

#define STRING_MANIPS_COUNT 1
#define STRING_MANIPS   \
  (                     \
    ( reset, "[0m" ), \
())                     \

#define BOOST_PP_ITERATION_PARAMS_1 \
  ( 3, ( 0, BOOST_PP_DEC( STRING_MANIPS_COUNT ), <trance/iostreams/detail/manip_string.hpp> ) )
#include BOOST_PP_ITERATE()
#undef STRING_MANIPS
#undef STRING_MANIPS_COUNT

#define STRING_MANIPS_COUNT 8
#define STRING_MANIPS           \
  (                             \
    ( black     , "[0;30m" ), \
    ( red       , "[0;31m" ), \
    ( green     , "[0;32m" ), \
    ( brown     , "[0;33m" ), \
    ( blue      , "[0;34m" ), \
    ( purple    , "[0;35m" ), \
    ( cyan      , "[0;36m" ), \
    ( light_gray, "[0;37m" ), \
())                             \

#define BOOST_PP_ITERATION_PARAMS_1 \
  ( 3, ( 0, BOOST_PP_DEC( STRING_MANIPS_COUNT ), <trance/iostreams/detail/manip_string.hpp> ) )
#include BOOST_PP_ITERATE()
#undef STRING_MANIPS
#undef STRING_MANIPS_COUNT

#define STRING_MANIPS_COUNT 8
#define STRING_MANIPS           \
  (                             \
    ( dark_gray   , "[1;30m" ), \
    ( light_red   , "[1;31m" ), \
    ( light_green , "[1;32m" ), \
    ( yellow      , "[1;33m" ), \
    ( light_blue  , "[1;34m" ), \
    ( light_purple, "[1;35m" ), \
    ( light_cyan  , "[1;36m" ), \
    ( white       , "[1;37m" ), \
())                             \

#define BOOST_PP_ITERATION_PARAMS_1 \
  ( 3, ( 0, BOOST_PP_DEC( STRING_MANIPS_COUNT ), <trance/iostreams/detail/manip_string.hpp> ) )
#include BOOST_PP_ITERATE()
#undef STRING_MANIPS
#undef STRING_MANIPS_COUNT

} // namespace iostreams

} // namespace trance


#endif // IG_TRANCE_IOSTREAMS_ESCAPE_SEQUENCE_HPP_ONCE_

