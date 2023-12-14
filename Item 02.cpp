#include <initializer_list>
#include <vector>
/**
 * Understand auto type deduction.
 *
 *
 * auto type deduction is usually the same as template type deduction, but auto type deduction assumes that a braced
 * initializer represents a std::initializer_list, and template type deduction doesn’t.
 *
 * auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.
*/

/**
 * Similarity with Template Type Deduction:
 * Auto type deduction is almost identical to template type deduction, with a direct mapping between the two. The
 * process is explained through examples where auto is used in variable declarations, showing a conceptual equivalence
 * to template parameters.
*/


/**
 * Three Cases of Type Deduction:
 * Just like template type deduction, auto type deduction falls into three cases based on the type specifier:
 * Case 1: Type specifier is a pointer or reference, but not a universal reference.
 * Case 2: Type specifier is a universal reference.
 * Case 3: Type specifier is neither a pointer nor a reference.
*/
auto x = 27;                // Case 3 (x is neither ptr nor reference)
const auto cx = x;          // Case 3 (cx isn't either)
const auto& rx = x;         // Case 1 (rx is a non-universal ref.)

auto&& uref1 = x;           // x is int and lvalue, so uref1's type is int&
auto&& uref2 = cx;          // cx is const int and lvalue, so uref2's type is const int&
auto&& uref3 = 27;          // 27 is int and rvalue, so uref3's type is int&&


/**
 * Special Rule for Braced Initializers:
 * A significant difference between auto and template type deduction is how braced initializers are treated. In auto type
 * deduction, a braced initializer deduces to a std::initializer_list, while in template type deduction, it typically
 * fails.
 *
 *
 * Examples Illustrating Differences:
 * The text provides examples showing how different declarations using auto can lead to different types, especially
 * highlighting the unique behavior with braced initializers.
*/
auto x1 = 27;               // Type is int, value is 27
auto x2(27);                // Same as 1
auto x3 = { 27 };           // Type is std::initializer_list<int>, value is { 27 }
auto x4{ 27 };              // Same as 1

auto x = { 11, 23, 9 };     // x's type is std::initializer_list<int>

template<typename T>        // Template with parameter declaration equivalent to x's declaration
void f1(T param);

f1( { 11, 23, 9 } );           // Error! can't deduce type for T


template<typename T>
void f2(std::initializer_list<T> initList);

f2( { 11, 23, 9 } );           // T deduced as int, and initList's type is std::initializer_list<int>


/**
 * Contextual Differences:
 * The discussion includes context such as C++14 allowing auto in function return types and lambda parameter declarations.
 * However, in these cases, template type deduction, not auto type deduction, is applied.
*/
auto createInitList()
{
 return { 1, 2, 3 }; // error: can't deduce type for { 1, 2, 3 }
}


std::vector<int> v;

auto reset = [&v](const auto& newValue) { v = newValue; }; // C++14

reset({ 1, 2, 3 }); // error! can't deduce type for { 1, 2, 3 }


/**
 * Practical Implications:
 * It emphasizes the importance of understanding these nuances, especially when using uniform initialization (braces) to
 * avoid unintended std::initializer_list declarations.
 *
 *
 * Continuation in C++14:
 * In C++14, the behavior of auto in function return types and lambda parameters is governed by template type deduction
 * rules, leading to certain restrictions and behaviors different from standard auto type deduction.
*/