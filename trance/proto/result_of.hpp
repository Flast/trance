#ifndef IG_TRANCE_PROTO_RESULT_OF_HPP_ONCE_
#define IG_TRANCE_PROTO_RESULT_OF_HPP_ONCE_

#include <trance/config.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/proto/eval.hpp>
#include <boost/proto/traits.hpp>

namespace trance
{

namespace proto
{

template <
  typename Expr, typename Context
, bool = ::boost::proto::is_expr< Expr >::value
>
struct result_of
  : public ::boost::mpl::identity< Expr > {};

template < typename Expr, typename Context >
struct result_of< Expr, Context, true >
{
    template < typename Arity, bool = Arity::value == 0 >
    struct _delay_result_of
      : public result_of<
          typename ::boost::proto::result_of::eval< Expr, Context >::type
        , Context
        > {};

    // for Terminate
    template < typename Arity >
    struct _delay_result_of< Arity, true >
      : public ::boost::proto::result_of::value< Expr > {};

    typedef typename _delay_result_of<
      ::boost::proto::arity_of< Expr >
    >::type type;
};

template < typename Expr, typename Context >
struct left_result_of
  : public result_of<
      typename ::boost::proto::result_of::left<
        Expr
      >::type
    , Context
    > {};

template < typename Expr, typename Context >
struct right_result_of
  : public result_of<
      typename ::boost::proto::result_of::right<
        Expr
      >::type
    , Context
    > {};

} // namespace proto

} // namespace trance

#endif // IG_TRANCE_PROTO_RESULT_OF_HPP_ONCE_

