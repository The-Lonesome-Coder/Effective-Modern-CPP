/**
 * Understand reference collapsing.
 *
 *
 * Reference collapsing occurs in four contexts: template instantiation, auto type generation, creation and use of
 * typedefs and alias declarations, and decltype.
 *
 * When compilers generate a reference to a reference in a reference collapsing context, the result becomes a single
 * reference. If either of the original references is an lvalue reference, the result is an lvalue reference. Otherwise
 * it’s an rvalue reference.
 *
 * Universal references are rvalue references in contexts where type deduction distinguishes lvalues from rvalues and
 * where reference collapsing occurs.
*/

/**
 * Reference Collapsing in Universal References:
 * Universal references in C++ template functions encode whether an argument is an lvalue or an rvalue.
 * For example, in a template function `template<typename T> void func(T&& param);`, the type `T` is
 * deduced based on whether the argument is an lvalue or an rvalue. If an lvalue is passed, `T` is
 * deduced as an lvalue reference, and if an rvalue is passed, `T` is deduced as a non-reference.
*/

/**
 * Illegal References to References:
 * C++ does not allow direct declarations of references to references (e.g., `auto& & rx = x;`), but they
 * can be produced during template instantiation. When an lvalue is passed to a function template taking
 * a universal reference, the deduced type leads to a reference-to-reference situation, which is handled
 * by reference collapsing.
*/
int x;
auto& & rx = x;      // Error! can't declare reference to reference


/**
 * Reference Collapsing Rules:
 * The rule for reference collapsing is straightforward: if either reference is an lvalue reference, the
 * result is an lvalue reference; otherwise, the result is an rvalue reference. This rule is applied during
 * template instantiation and is integral to the functioning of `std::forward`.
 * - T& & becomes T&.
 * - T& && becomes T&.
 * - T&& & becomes T&.
 * - T&& && becomes T&&.
*/


/**
 * std::forward and Reference Collapsing:
 * The `std::forward` function in C++ templates leverages reference collapsing. It casts a universal
 * reference (an lvalue) to an rvalue if and only if the type `T` encodes that the argument was initially
 * an rvalue. This mechanism underpins the behavior of perfect forwarding in template functions.
*/
template<typename T>
void f(T&& fParam)
{
    // do some work

    someFunc(std::forward<T>(fParam));      // Forward fParam to someFunc
}


/**
 * Four Contexts of Reference Collapsing:
 * Reference collapsing occurs in four specific contexts:
 *  1. Template instantiation.
 *  2. Type generation for `auto` variables.
 *  3. Creation or evaluation of typedefs and alias declarations.
 *  4. Uses of `decltype`.
*/
