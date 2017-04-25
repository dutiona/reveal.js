// sample(Hello-World)
#include <iostream>
#include <type_traits>

/////////// Default template value
// Use-case : emulate concepts
// With default value (recommended)

template<class T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
void g() {
    std::cout << "typename = std::is_integral<T>" << std::endl;
}


template<class T, std::enable_if_t<!std::is_integral<T>::value, int> = 0>
void g() {
    std::cout << "typename = !std::is_integral<T>" << std::endl;
}

// Variadic

template<class T, class ... Args, std::enable_if_t<std::is_integral<T>::value, int> = 0>
void h(Args&& ... args) {
    std::cout << "typename = std::is_integral<T>" << std::endl;
}

template<class T, class ... Args, std::enable_if_t<!std::is_integral<T>::value, int> = 0>
void h(Args&& ... args) {
    std::cout << "typename = !std::is_integral<T>" << std::endl;
}

// LIMIT : specialisation
// default template arguments may not be used in partial specializations
// template parameters not deducible in partial specialization:



//////////////
// Template specialisation example
template<bool Cond, class T>
struct S {
  static void k();  
};

template<class T>
struct S<true, T> {
    static void k() {
        std::cout << "<true>" << std::endl;
    }
};

template<class T>
struct S<false, T> {
    static void k();
};

template<class T>
void S<false, T>::k() {
    std::cout << "<false>" << std::endl;
}
//////////////////////



/////////// template Typename
// Use-case emulate concepts
template<class T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
void f() {
    std::cout << "typename = std::is_integral<T>" << std::endl;
}

// Limit : same overload
/*
template<class T, typename = std::enable_if_t<!std::is_integral<T>::value, T>>
void f() {
    std::cout << "typename = !std::is_integral<T>" << std::endl;
}
*/

// Variadic
template<class T, class ... Args, typename = std::enable_if_t<!std::is_integral<T>::value, T>>
void hh(Args&& ... args) {
    std::cout << "typename = !std::is_integral<T>" << std::endl;
}

// Specialisation
template<bool Cond, class T, typename = std::enable_if_t<std::is_same<T, char>::value, T>>
struct Z {
  static void k();  
};

template<class T, class U>
struct Z<true, T, U> {
    
    static void k() {
        std::cout << "k<true>" << std::endl;
    }
    
};

template<class T, class U>
struct Z<false, T, U> {
    
    static void k() {
        std::cout << "k<false>" << std::endl;
    }
    
};

//////////////////////
// Enable_if as return type
// use-case : make overload differing by return type
// works with variadic and specialisations
template<bool>
struct static_if {
    template<class Ret, class If, class Else, class ... Args>
    static Ret call(If&&, Else&&, Args&& ...);
};

template<>
struct static_if<true> {
    template<class Ret, class If, class Else, class ... Args>
    static std::enable_if_t<!std::is_same<Ret, void>::value, Ret> call(If&& if_f, Else&&, Args&& ... args)
    {
        return if_f(std::forward<Args>(args)...);
    }

    template<class Ret, class If, class Else, class ... Args>
    static std::enable_if_t<std::is_same<Ret, void>::value> call(If&& if_f, Else&&, Args&& ... args)
    {
        if_f(std::forward<Args>(args)...);
    }
};

template<>
struct static_if<false> {
    template<class Ret, class If, class Else, class ... Args>
    static std::enable_if_t<!std::is_same<Ret, void>::value, Ret> call(If&&, Else&& else_f, Args&& ... args)
    {
        return else_f(std::forward<Args>(args)...);
    }

    template<class Ret, class If, class Else, class ... Args>
    static std::enable_if_t<std::is_same<Ret, void>::value> call(If&&, Else&& else_f, Args&& ... args)
    {
        else_f(std::forward<Args>(args)...);
    }
};

// LIMITATION : ctors and conversion operator function


////////////////////////////////////
// Enable_if as a function parameter

// use case : relaxed tag dispatching
// works with specialisation

template<class T>
void add(T a, std::enable_if_t<std::is_same<T, int>::value, int> b) {
    std::cout << "add<int>" << std::endl;
}

template<class T>
void add(T a, double b, std::enable_if_t<std::is_same<T, double>::value, void**> = nullptr) {
    std::cout << "add<double>" << std::endl;
}

// Specialisation
template<bool Cond>
struct W {
  template<class T>
  static void k(T a);  
};

template<>
struct W<true> {
    
    template<class T>
    static void k(T a, std::enable_if_t<std::is_same<T, double>::value, void**> = nullptr) {
        std::cout << "W<true>::k(double)" << std::endl;
    }
    
    template<class T>
    static void k(T a, std::enable_if_t<std::is_same<T, float>::value, void**> = nullptr) {
        std::cout << "W<true>::k(float)" << std::endl;
    }
    
};

template<>
struct W<false> {
    
    template<class T>
    static void w(T a, std::enable_if_t<std::is_same<T, int>::value, void**> = nullptr) {
        std::cout << "W<false>::k(int)" << std::endl;
    }
    
};

template<bool Cond>
struct Z {
  template<class T>
  static void k(T a);  
};

template<>
struct Z<true> {
    
    template<class T>
    static void k(T a, std::enable_if_t<std::is_same<T, double>::value, T> b) {
        std::cout << "W<true>::k(double)" << std::endl;
    }
    
    template<class T>
    static void k(T a, std::enable_if_t<std::is_same<T, float>::value, T> b) {
        std::cout << "W<true>::k(float)" << std::endl;
    }
    
};

template<>
struct Z<false> {
    
    template<class T>
    static void w(T a, std::enable_if_t<std::is_same<T, int>::value, T> b) {
        std::cout << "W<false>::k(int)" << std::endl;
    }
    
};

// LIMITATION : don't handle variadic







/*
template<class T>
constexpr bool can_be_decay = !std::is_same<std::decay_t<T>, T>::value;

static_assert(can_be_decay<char(&)[1]>, "");
static_assert(!can_be_decay<char*>, "");
*/
struct A {};

int main()
{
    //std::enable_if_t<std::is_integral<int>::value, int> a;
    
    f<int>();
    //f<A>();
    
    g<int>();
    g<A>();
    
    h<int>("a", 'h', 1., 45.f, 15);
    h<A>("a", 'h', 1., 45.f, 15);
    hh<A>("a", 'h', 1., 45.f, 15);
    
    S<true, int>::k();
    S<true, char>::k();
    S<false, double>::k();
    
    Z<true, char>::k();
    Z<false, char>::k();
    
    add(0, 0);
    add(0., 0.);
    //add(0.f, 0.f);
    
    W<true>::k(0.);
    W<true>::k(0.f);
    W<false>::w(0);
    Z<true>::k(0., 1.);
    Z<true>::k(0.f, 1.f);
    Z<false>::w(0, 1);
    
    return 0;
}

// end-sample