#include <unordered_map>
#include <memory>
#include <string>
/**
 * Prefer alias declarations to typedefs.
 *
 *
 * typedefs don’t support templatization, but alias declarations do.
 *
 * Alias templates avoid the “::type” suffix and, in templates, the “typename” prefix often required to refer to typedefs.
 *
 * C++14 offers alias templates for all the C++11 type traits transformations.
*/

/**
 * Alias Declarations vs. Typedefs:
 * Alias declarations in C++11 offer a more modern and flexible alternative to typedefs. Both essentially serve the same
 * purpose: to create a synonym for a type. However, alias declarations have advantages, particularly when working with
 * templates.
*/
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;


/**
 * Alias Templates:
 * Unlike typedefs, alias declarations can be templatized, creating what's known as alias templates. This feature allows
 * for more straightforward and elegant handling of types, especially in template meta-programming.
 *
 * The example given illustrates this difference. Creating an alias for a std::list using a custom allocator is
 * straightforward with an alias template, but more complex and less intuitive with typedefs, requiring nested typedefs
 * inside structs.
 *
 *
 * Simplification in Templates:
 * With alias templates, there is no need for the typename keyword or the ::type suffix, which are required with typedefs
 * in templates. This simplification makes the code more readable and reduces potential errors.
*/
// MyAllocList<T> is synonym for std::list<T, MyAlloc<T>>
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

template<typename T>
class Widget
{
    private:
        MyAllocList<T> list;
};


/**
 * Type Transformations in C++11 and C++14:
 * The excerpt discusses type transformations using type traits in C++11, which involve nested typedefs inside templates.
 * These transformations typically end with ::type and require typename when used in templates.
 *
 * C++14 introduces alias templates for these type transformations (like std::remove_const_t, std::remove_reference_t,
 * std::add_lvalue_reference_t), which simplify the syntax and eliminate the need for ::type and typename.
*/
std::remove_const<T>::type              // Yields T from const T
std::remove_const_t<T>                  // C++14 equivalent

std::remove_reference<T>::type          // Yields T from T& and T&&
std::remove_reference_t<T>              // C++14 equivalent

std::add_lvalue_reference<T>::type      // Yields T& from T
std::add_lvalue_reference_t<T>          // C++14 equivalent


/**
 * Advantage of Alias Templates:
 * Alias templates are particularly useful for creating more readable and maintainable code. They eliminate the syntactic
 * overhead associated with traditional typedefs in template meta-programming.
 *
 * Even in environments where only C++11 is available, it's straightforward to manually create these alias templates, as
 * they don't require features beyond C++11.
*/
template <class T>
using remove_const_t = typename remove_const<T>::type;

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;