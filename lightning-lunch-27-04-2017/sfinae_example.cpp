// Example program
#include <iostream>
#include <string>

using namespace std;

// sample(SFINAE-functions)
template<typename T>
void f(T& a) { cout << "void f(T& a)" << endl; }

void f(int a) { cout << "void f(int a)" << endl;}

void f(double a) { cout << "void f(double a)" << endl; }
// end-sample

int main() {
    // sample(SFINAE-main)
    struct S {};
    S s;
    f(s);   // void f(T& a)
    f(1.);  // void f(double a)
    f(5);   // void f(int a)
    f(S{}); // compilation error
    return 0;
    // end-sample
}
