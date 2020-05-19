#ifndef _CEST_LIST_TESTS_HPP_
#define _CEST_LIST_TESTS_HPP_

#include "cest/list.hpp"
#include <list>
#include <tuple>
#include <cassert>

template <typename L>
constexpr auto list_test1()
{
  L l;
  l.push_front(42);
  auto x = l.front();
  auto s = l.size();
  l.push_front(43);
  return std::tuple{x, s, l.front(), l.size()};
}

template <typename L>
constexpr auto list_test2()
{
  L l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  l.push_back(5);

  int sum1 = 0;
  for (auto it = l.begin(); it != l.end(); )
  {
    sum1 += *it;
    if (*it % 2 == 0) { // delete even numbers
      it = l.erase(it);
    } else {
      ++it;
    }
  }
  
//  todo
//  int sum2 = 0;
//  using cit_t = typename L::const_iterator;
//  for (cit_t it = l.cbegin(); it != l.cend(); ++it)
//    sum2 += *it;

  return std::tuple{sum1,l.size()};
}

void list_tests()
{
  constexpr const auto tup1 = std::tuple{42,1,43,2};
  constexpr const auto tup2 = std::tuple{15,3};

#ifndef NO_STATIC_TESTS
  static_assert(list_test1<cest::list<int>>() == tup1);
  static_assert(list_test2<cest::list<int>>() == tup2);
#endif

  assert(list_test1< std::list<int>>() == tup1);
  assert(list_test1<cest::list<int>>() == tup1);
  assert(list_test2< std::list<int>>() == tup2);
  assert(list_test2<cest::list<int>>() == tup2);
}

//list<_Tp, _Alloc>::emplace_back(_Args&&... __args)
//{
//    __node_allocator& __na = base::__node_alloc();
//    __hold_pointer __hold = __allocate_node(__na);
//    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::forward<_Args>(__args)...);
//    __link_pointer __nl = __hold->__as_link();
//    __link_nodes_at_back(__nl, __nl);
//    ++base::__sz();
//#if _LIBCPP_STD_VER > 14
//    return __hold.release()->__value_;
//#else
//    __hold.release();
//#endif
//}

//template <class _Tp, class _Alloc>
//void
//list<_Tp, _Alloc>::push_back(value_type&& __x)
//{
//    __node_allocator& __na = base::__node_alloc();
//    __hold_pointer __hold = __allocate_node(__na);
//    __node_alloc_traits::construct(__na, _VSTD::addressof(__hold->__value_), _VSTD::move(__x));
//    __link_nodes_at_back(__hold.get()->__as_link(), __hold.get()->__as_link());
//    ++base::__sz();
//    __hold.release();
//}

#endif // _CEST_LIST_TESTS_HPP_
