#include <iostream>
#include <type_traits>
#include <functional>

using namespace std;

// sample(static-if-prototype)
template<bool>
struct static_if {
  template<class Ret, class If, class Else, class ... Args>
  static Ret call(If&&, Else&&, Args&& ...);
};
// end-sample

// sample(static-if-true-problem-part)
template<>
struct static_if<true> {
  template<class Ret, class If, class Else, class ... Args>
  Ret call(If&& if_f, Else&&, Args&& ... args)
  {
    return if_f(forward<Args>(args)...);
  }
};
// end-sample

// sample(static-if-false-problem-part)
template<>
struct static_if<true> {
  template<class Ret, class If, class Else, class ... Args>
  static Ret call(If&&, Else&& else_f, Args&& ... args)
  {
    return else_f(forward<Args>(args)...);
  }
};
// end-sample

// sample(static-if-true-part)
template<>
struct static_if<true> {
  template<class Ret, class If, class Else, class ... Args>
  static auto call(If&& if_f, Else&&, Args&& ... args)
    -> enable_if_t<!is_same<Ret, void>::value, Ret>
  {
    return if_f(forward<Args>(args)...);
  }

  template<class Ret, class If, class Else, class ... Args>
  static auto call(If&& if_f, Else&&, Args&& ... args)
    -> enable_if_t<is_same<Ret, void>::value>
  {
    if_f(forward<Args>(args)...);
  }
};
// end-sample

// sample(static-if-false-part)
template<>
struct static_if<false> {
  template<class Ret, class If, class Else, class ... Args>
  static auto call(If&&, Else&& else_f, Args&& ... args)
    -> enable_if_t<!is_same<Ret, void>::value, Ret>
  {
    return else_f(forward<Args>(args)...);
  }

  template<class Ret, class If, class Else, class ... Args>
  static auto call(If&&, Else&& else_f, Args&& ... args)
    -> enable_if_t<is_same<Ret, void>::value>
  {
    else_f(forward<Args>(args)...);
  }
};
// end-sample

int main() {
// sample(static-if-main)
constexpr bool condition = true;
auto ret = static_if<condition>::call<double>(
    [](int a, double b) { return b * a; },  // if lambda
    [](int a, double b) { 0.; },            // else lambda
    15, 42.                                 // arguments
);
cout << ret << endl; // affiche 630
// end-sample
}