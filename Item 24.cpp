#include <utility>
#include <vector>
/**
 * Distinguish universal references from rvalue references.
 *
 *
 * If a function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the
 * parameter or object is a universal reference.
 *
 * If the form of the type declaration isn’t precisely type&&, or if type deduction does not occur, type&& denotes an
 * rvalue reference.
 *
 * Universal references correspond to rvalue references if they’re initialized with rvalues. They correspond to lvalue
 * references if they’re initialized with lvalues.
*/

class Widget;

/**
 * Dual Nature of "T&&":
 * In C++, "T&&" can have two meanings: it can be an rvalue reference or a universal reference. While
 * rvalue references bind only to rvalues, universal references can bind to rvalues as well as lvalues, and
 * they have the capacity to bind to objects with various qualifiers like const, non-const, volatile, etc.
*/

void f(Widget&& param);             // rvalue reference
Widget&& var1 = Widget();           // rvalue reference
auto&& var2 = var1;                 // Universal reference

template<typename T>
void f(std::vector<T>&& param);     // rvalue reference

template<typename T>
void f(T&& param);                  // Universal reference


/**
 * Universal References in Contexts:
 * Universal references occur in two main contexts: as parameters in function templates and in auto
 * declarations. These contexts involve type deduction, which is a necessary condition for a reference to
 * be considered universal. An example of a universal reference in a function template is `void f(T&& param);`.
*/

/**
 * Understanding the Difference:
 * The distinction between an rvalue reference and a universal reference depends on the presence of type
 * deduction. If "T&&" appears without type deduction, it's an rvalue reference. However, with type
 * deduction (as in function templates and auto declarations), "T&&" becomes a universal reference.
*/
auto&& var2 = var1;                 // var2 is a universal reference

template<typename T>
void f(T&& param);                  // Universal reference


/**
 * Initializer's Role:
 * The initializer for a universal reference determines its nature (rvalue or lvalue reference). For
 * instance, in a function template, if an lvalue is passed to a universal reference, it behaves as an lvalue
 * reference; if an rvalue is passed, it behaves as an rvalue reference.
*/
Widget w;

template<typename T>
void f(T&& param);                  // param is a universal reference

f(w);                               // lvalue passed to f; param's type is Widget& (i.e., an lvalue reference)
f(std::move(w));                    // rvalue passed to f; param's type is Widget&& (i.e., an rvalue reference)


/**
 * Constraints in Reference Declaration:
 * To be classified as a universal reference, the reference declaration must be exactly “T&&”. Any
 * deviation from this form, like the presence of a const qualifier or a specific type like `std::vector<T>&&`,
 * results in an rvalue reference instead of a universal reference.
*/
template<typename T>
void f(std::vector<T>&& param);     // param is an rvalue reference


/**
 * Application in Templates and Lambda Expressions:
 * Universal references are notably used in function templates and can also appear in C++14 lambda
 * expressions with `auto&&` parameters. These references allow functions and lambdas to accept a wide
 * range of argument types.
*/
template<typename MyTemplateType>
void someFunc(MyTemplateType&& param);      // param is a universal reference

// C++14
auto timeFuncInvocation = [](auto&& func, auto&&... params)
{
    // Start timer

    // Invoke func on params
    std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)... );

    // Stop timer and record elapsed time;
};


/**
 * Concept of Abstraction and Reference Collapsing:
 * The entire concept of universal references is an abstraction built over the more complex underlying
 * truth of reference collapsing. Understanding this abstraction is essential for reading and writing C++ code
 * effectively, particularly in templates, and it simplifies the more intricate details of reference collapsing.
*/