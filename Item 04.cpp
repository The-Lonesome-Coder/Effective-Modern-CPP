#include <iostream>
#include <typeinfo>
/**
 * Know how to view deduced type.
 *
 *
 * Deduced types can often be seen using IDE editors, compiler error messages, and the Boost TypeIndex library.
 *
 * The results of some tools may be neither helpful nor accurate, so an understanding of C++’s type deduction rules
 * remains essential.
*/

/**
 * IDE Editors:
 * In Integrated Development Environments (IDEs), code editors can show the types of variables, functions, etc., when you
 * hover over them. This feature requires a compilable code state, as it relies on an internal C++ compiler. While
 * effective for simple types, this method might not be as helpful for complex types.
 *
 *
 * Compiler Diagnostics:
 * To determine deduced types during compilation, intentionally causing a compilation error can be effective. For example,
 * creating a template class with no definition and trying to instantiate it with a type will generate an error message
 * revealing the type. This method tends to work across different compilers, though the format of the error messages may
 * vary.
*/


/** Runtime Output:
 * At runtime, types can be displayed using features like typeid and std::type_info::name. However, this approach is not
 * always reliable, especially with complex types or references, due to limitations in how C++ handles type information.
 * The text suggests that the results from typeid may not always be accurate, as it tends to ignore reference and const
 * qualifiers.
*/
int x { 0 }, y { 0 };

std::cout << typeid(x).name() << '\n';      // display types for x and y
std::cout << typeid(y).name() << '\n';
