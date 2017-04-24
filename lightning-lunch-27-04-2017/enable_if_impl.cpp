// sample(prototype)
template<bool B, typename T = void>
struct enable_if;
// end-sample

// sample(implem)
template<bool B, typename T = void>
struct enable_if {};

// Utilisation du SFINAE pour spécialisation à true
template<typename T>
struct enable_if<true, T> { using type = T; };

// Laisse le compilateur échouer la compilation lors d'un accès :
// enable_if<false, T>::type car type ne sera pas défini

template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type; // C++14
// end-sample