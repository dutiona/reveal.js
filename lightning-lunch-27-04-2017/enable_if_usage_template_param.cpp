#include <iostream>
#include <type_traits>
#include <functional>

using namespace std;

// sample(enable-if-usage-default-template-macro)
#define REQUIRES(COND) \
    std::enable_if_t<(COND), int> = 0
// end-sample

// sample(enable-if-usage-default-template-value1)
template<
  typename ... Args,
  enable_if_t<sizeof...(Args) == 0, int> = 0
  >
void f(Args&& ... args) {
  cout << "Empty pack !" << endl;
}
// end-sample

// sample(enable-if-usage-default-template-value2)
template<
  typename ... Args,
  enable_if_t<sizeof...(Args) == 1, int> = 0
  >
void f(Args&& ... args) {
  cout << "Optimized for pack size == 1 !" << endl;
}
// end-sample


// sample(enable-if-usage-default-template-value3-bug)
template<
  typename ... Args,
  enable_if_t<greater_equal<size_t>{}(sizeof...(Args), 1), int> = 0
  >
void f(Args&& ... args) {
  cout << "Generic data processing !" << endl;
}
// end-sample


// sample(enable-if-usage-default-template-value3)
template<
  typename ... Args,
  enable_if_t<greater<size_t>{}(sizeof...(Args), 1), int> = 0
  >
void f(Args&& ... args) {
  cout << "Generic data processing !" << endl;
}
// end-sample


int main() {
    
// sample(enable-if-usage-default-template-value-main-bug)
f();    // affiche "Empty pack!"
f(0);   // error: call of overloaded 'f(int)' is ambiguous
// end-sample

// sample(enable-if-usage-default-template-value-main)
f();             // Empty pack !
f(0);            // Optimized for pack size == 1 !
f("test", 2.);   // Generic data processing !
f(1, "test", 3.);// Generic data processing !
// end-sample

}