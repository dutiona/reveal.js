#include <iostream>

using namesapce std;

// sample(Hello-World)
#include <iostream>
#include <type_traits>

/////////// Default value

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



/////////// Typename

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

template<bool>
struct static_if {
    template<class Ret, class If, class Else, class ... Args>
    static Ret call(If&&, Else&&, Args&& ...);
};

template<>
struct static_if<true> {
    template<class Ret, class If, class Else, class ... Args>
    static decltype(auto) call(If&& if_f, Else&&, Args&& ... args)
        -> std::enable_if_t<!std::is_same<Ret, void>::value, Ret>
    {
        return if_f(std::forward<Args>(args)...);
    }

    template<class Ret, class If, class Else, class ... Args>
    static decltype(auto) call(If&& if_f, Else&&, Args&& ... args)
        -> std::enable_if_t<std::is_same<Ret, void>::value>
    {
        if_f(std::forward<Args>(args)...);
    }
};

template<>
struct static_if<false> {
    template<class Ret, class If, class Else, class ... Args>
    static decltype(auto) call(If&&, Else&& else_f, Args&& ... args)
        -> std::enable_if_t<!std::is_same<Ret, void>::value, Ret>
    {
        return else_f(std::forward<Args>(args)...);
    }

    template<class Ret, class If, class Else, class ... Args>
    static decltype(auto) call(If&&, Else&& else_f, Args&& ... args)
        -> std::enable_if_t<std::is_same<Ret, void>::value>
    {
        else_f(std::forward<Args>(args)...);
    }
};


struct A {};

int main()
{
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
    
    return 0;
}

// end-sample