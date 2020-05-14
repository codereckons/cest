#ifndef _CEST_ALGORITHM_TESTS_HPP_
#define _CEST_ALGORITHM_TESTS_HPP_

#include "cest/vector.hpp"
#include "cest/set.hpp"
#include <vector>
#include <set>
#include <array>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <cassert>

template <typename V, typename S>
constexpr auto algorithm_test1() {
  using namespace std;
  using arr_t = array<int,5>;
  arr_t a{1,2,3,4,5};
  arr_t b{3,4,5,6,7};
  arr_t res;

  auto end = set_intersection(a.begin(),a.end(),b.begin(),b.end(),res.begin());
  auto sum = accumulate(res.begin(), end, 0);

  V v1, v2, vres;
  copy(a.begin(),a.end(),back_inserter(v1)); // std::copy works constexpr
  copy(b.begin(),b.end(),back_inserter(v2)); // ""
  auto vend = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),
                               back_inserter(vres));
  auto vsum = accumulate(vres.begin(), vres.end(), 0);

  S s1, s2, sres;
  copy(a.begin(),a.end(),inserter(s1,s1.end()));
  copy(b.begin(),b.end(),inserter(s2,s2.end()));
  auto send = set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),
                               inserter(sres,sres.end()));
  auto ssum = accumulate(sres.begin(), sres.end(), 0);

  return tuple{sum,vsum,ssum};
}

template <typename V, typename S>
constexpr auto algorithm_test2() {
  using namespace std;
  using arr_t = array<int,5>;
  arr_t a{1,2,3,4,5};

  auto e = *find(a.begin(), a.end(), 4);                //     found
  bool b =  find(a.begin(), a.end(), 42) == a.end();    // not found

  V v;
  copy(a.begin(),a.end(),back_inserter(v));
  auto ve = *find(v.begin(), v.end(), 4);               //     found
  bool vb =  find(v.begin(), v.end(), 42) == v.end();   // not found

  char sz[] = "abcdefg";
  auto sze = *find(begin(sz), end(sz), 'c');            //     found
  auto szb =  find(begin(sz), end(sz), '&') == end(sz); // not found

  return tuple{e,b,ve,vb,sze,szb};
}

template <
  template <typename...> typename S,
  template <typename...> typename V
>
void rt_algorithm_tests(auto tup1, auto tup2) {
  assert((algorithm_test1<S<int>,V<int>>()) == tup1);
  assert((algorithm_test2<S<int>,V<int>>()) == tup2);
}

void algorithm_tests()
{
  constexpr const auto tup1 = std::tuple{12,12,12}; // 3+4+5 == 12
  constexpr const auto tup2 = std::tuple{4,true,4,true,'c',true};

#ifndef NO_STATIC_TESTS
  static_assert((algorithm_test1<cest::vector<int>,cest::set<int>>()) == tup1);
#endif
  
//  rt_algorithm_tests<std::vector,std::set>(tup1, tup2);
  rt_algorithm_tests<cest::vector,cest::set>(tup1, tup2);
}

#endif // _CEST_ALGORITHM_TESTS_HPP_
