#include <utility>
/**
 * Understand decltype.
 *
 *
 * decltype almost always yields the type of a variable or expression without any modifications.
 *
 * For lvalue expressions of type T other than names, decltype always reports a type of T&.
 *
 * C++14 supports decltype(auto), which, like auto, deduces a type from its initializer, but it performs the type
 * deduction using the decltype rules.
*/

/**
 * Basic Functionality of decltype:
 * decltype identifies the type of a variable or expression.
 * It generally returns the expected type. For instance, decltype(i) for const int i is const int.
 * For more complex expressions, its behavior can be non-intuitive, sometimes leading to surprises.
 *
 *
 * Typical Cases:
 * decltype simply echoes the type of the variable or expression.
*/
// Examples
class Widget { };

const int i = 0;                // decltype(i) is const int
bool f(const Widget& w);        // decltype(w) is const Widget&
struct Point { int x, y; };     // decltype(Point::x) is int


/** Advanced Usage:
 * In C++11 and later, decltype is commonly used in templates, particularly when a function's return type depends on its
 * parameter types.
 *
 * For example, if a function template performs an indexing operation on a container, the return type should match the
 * type returned by the container's indexing operation. decltype simplifies expressing this.

 * The passage illustrates this with a function template authAndAccess, which uses decltype to deduce the return type
 * from the container's operator[].
*/
// C++11
template<typename Container, typename Index>
auto authAndAccess(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i])
{
    authenticateUser();

    return std::forward<Container>(c)[i];
}


/**
 * C++14 Enhancements:
 * C++14 introduces decltype(auto), allowing for the deduction of a type using decltype rules. This is useful when the
 * exact type to return is not straightforward.
 *
 * The passage details modifying authAndAccess to work with C++14, using decltype(auto) for more accurate type deduction.
*/
// C++14
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
    authenticateUser();

    return std::forward<Container>(c)[i];
}


/**
 * Special Cases and Surprises:
 * Applying decltype to a name yields its declared type. However, for more complex lvalue expressions, decltype always
 * reports the type as an lvalue reference (T&).
 *
 * This can lead to unexpected results, such as decltype((x)) being int& instead of int.
 *
 * In C++14, using decltype(auto) needs careful attention, as minor changes in expressions can significantly alter the
 * deduced type.
*/
decltype(auto) f1()
{
    int x = 0;

    return x;                   // decltype(x) is int, so f1 returns int
}

decltype(auto) f2()
{
    int x = 0;

    return (x);                // decltype((x)) is int&, so f2 returns int&
}