// sample(prototype)
template< bool B, class T = void >
struct enable_if;
// end-sample

// sample(implem)
template<bool B, class T = void>
struct enable_if {};

// Utilisation du SFINAE pour spécialisation à true
template<class T>
struct enable_if<true, T> { using type = T; };

// Laisse le compilateur échouer la compilation lors d'un accès :
// enable_if<false, T>::type car type ne sera pas défini

// end-sample