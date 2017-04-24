#include <iostream>
#include <type_traits>

using namespace std;

// sample(enable-if-usage-all)
template<
  typename T, typename U = T,
  /*(1)*/enable_if_t<is_same<T, int>::value, int> = 0,
  /*(2)*/typename = enable_if_t<is_same<T, U>::value, T>
  >
/*(3)*/enable_if_t<is_integral<U>::value, int>
f(T a,
  /*(4)*/enable_if_t<is_same<U, int>::value, U> b,
  /*(5)*/enable_if_t<is_same<T, int>::value, void**> = nullptr)
{
  cout << "void f(T a, U a) when T = U = int" << endl;
  return a;
}
// end-sample

int main() {
    
// sample(enable-if-usage-all-main)
f(1, 1);  // affiche "void f(T a, U a) when T = U = int"
f(1., 1.);// error: no matching function for call to
          //        'f(double, double)'
// end-sample


}