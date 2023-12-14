/**
 * Understand template type deduction.
 *
 *
 * During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness
 * is ignored.
 *
 * When deducing types for universal reference parameters, lvalue arguments get special treatment.
 *
 * When deducing types for by-value parameters, const and/or volatile arguments are treated as non-const and non-volatile.
 *
 * During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to
 * initialize references.
*/

/**
 * Template Type Deduction Success:
 * Despite many programmers lacking a deep understanding of how C++ template type deduction works, they successfully use
 * it, indicating its well-designed nature.
 *
 *
 * Relevance to auto Keyword:
 * The auto keyword in C++11 builds upon the principles of template type deduction. Understanding these principles is
 * crucial for effective use of auto, even though its application might seem less intuitive than with templates.
*/
template <typename T>
void f(/* Parameter Type */ parameter);

f(/* expression */);   // Deduce T and ParamType from expression


/**
 * Three Deduction Scenarios
 * There are three main scenarios for type deduction based on ParamType:
*/
/**
 * Pointer or Reference, but not Universal Reference:
 * Ignores the reference part of expr and pattern-matches expr’s type against ParamType.
*/
template <typename T>
void f(T& parameter);

int x = 27;                 // x is an int
const int cx = x;           // cx is a const int
const int& rx = x;          // rx is a reference to x as a const int

f(x);                      // T is an int, parameter's type is int&
f(cx);                     // T is a const int, parameter's type is int&
f(rx);                     // T is a const int, parameter's type is int&


// Things change a little if we change the parameter from non-const to cont
template<typename T>
void f(const T& param);     // param is now a ref-to-const

f(x);                      // T is int, param's type is const int&
f(cx);                     // T is int, param's type is const int&
f(rx);                     // T is int, param's type is const int&



// If parameter is a pointer, it would work as the first one
template<typename T>
void f(T* param);          // param is now a pointer
const int *px = &x;         // px is a ptr to x as a const int

f(&x);                     // T is int, param's type is int*
f(px);                     // T is const int, param's type is const int*


/**
 * Universal Reference:
 * If expr is an lvalue, both T and ParamType are deduced as lvalue references. If expr is an rvalue, regular rules
 * apply.
*/
template<typename T>
void f(T&& param);         // param is now a universal reference

int x = 27;                 // as before
const int cx = x;           // as before
const int& rx = x;          // as before

f(x);                      // x is lvalue, so T is int&, param's type is also int&
f(cx);                     // cx is lvalue, so T is const int&, param's type is also const int&
f(rx);                     // rx is lvalue, so T is const int&, param's type is also const int&
f(27);                     // 27 is rvalue, so T is int, param's type is therefore int&&


/**
 * Neither Pointer nor Reference:
 * If ParamType is neither, the process involves pass-by-value, where const and volatile are ignored in expr.
*/
template<typename T>
void f(T param);           // param is now passed by value

f(x);                      // T's and param's types are both int
f(cx);                     // T's and param's types are again both int
f(rx);                     // T's and param's types are still both int


/**
 * Array and Function Argument Deduction: Special rules apply when arrays or functions are arguments. Arrays decay to
 * pointers, and functions can decay into function pointers, affecting how types are deduced.
*/
// Of course, as a modern C++ developer, you’d naturally prefer a std::array to a built-in array
const char name[] { "J. P. Briggs" }; // name's type is const char[13]

template<typename T>
void f(T param);            // template with by-value parameter

f(name);                    // name is array, but T deduced as const char*

/* .................................................................................................................. */

void someFunc(int, double); // someFunc is a function; type is void(int, double)

template<typename T>
void f1(T param);           // in f1, param passed by value

template<typename T>
void f2(T& param);          // in f2, param passed by ref

f1(someFunc);               // param deduced as ptr-to-func; type is void (*)(int, double)
f2(someFunc);               // param deduced as ref-to-func; type is void (&)(int, double)