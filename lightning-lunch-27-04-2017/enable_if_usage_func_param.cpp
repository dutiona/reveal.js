#include <iostream>
#include <type_traits>

using namespace std;

// sample(enable-if-usage-function-parameter-type1)
template<typename T>
void f(T a,
       enable_if_t<is_integral<T>::value, T> b)
{
  cout << "integral type !" << endl;
}
// end-sample

// sample(enable-if-usage-function-parameter-type2)
template<typename T>
void f(T a,
       enable_if_t<!is_integral<T>::value, T> b)
{
  cout << "not integral type !" << endl;
}
// end-sample

// sample(enable-if-usage-function-parameter-type3)
template<typename T>
void f(enable_if_t<is_integral<T>::value, T> a) {
  cout << "integral type !" << endl;
}
// end-sample

// sample(enable-if-usage-function-parameter-type4)
template<typename T>
void f(enable_if_t<!is_integral<T>::value, T> a) {
  cout << "not integral type !" << endl;
}
// end-sample

// sample(enable-if-usage-function-parameter-type5)
template<typename T>
void f(T a,
       enable_if_t<is_integral<T>::value, void**> = nullptr)
{
  cout << "integral type !" << endl;
}
// end-sample

// sample(enable-if-usage-function-parameter-type6)
template<typename T>
void f(T a,
       enable_if_t<!is_integral<T>::value, void**> = nullptr)
{
  cout << "not integral type !" << endl;
}
// end-sample

int main() {

// sample(enable-if-usage-function-parameter-main1)
f(0, 0);    // affiche "integral type !"
f("t", "t");// affiche "not integral type!"
// end-sample

// sample(enable-if-usage-function-parameter-main2)
f(0);  //error: no matching function for call to 'f(int)'
f("t");//error: no matching function for call to 'f(const char [2])'
f<int>(0);                // affiche "integral type !"
f<const char(&)[2]>("t"); // affiche "not integral type!"
// end-sample

// sample(enable-if-usage-function-parameter-main3)
f(0);  // affiche "integral type !"
f("t");// affiche "not integral type!"
// end-sample

}