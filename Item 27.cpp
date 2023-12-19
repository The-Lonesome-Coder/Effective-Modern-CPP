#include <string>
/**
 * Familiarize yourself with alternatives to overloading on universal references.
 *
 *
 * Alternatives to the combination of universal references and overloading include the use of distinct function names,
 * passing parameters by lvalue-reference-to-const, passing parameters by value, and using tag dispatch.
 *
 * Constraining templates via std::enable_if permits the use of universal references and overloading together, but it
 * controls the conditions under which compilers may use the universal reference overloads.
 *
 * Universal reference parameters often have efficiency advantages, but they typically have usability disadvantages.
*/

/**
 * Problems with Overloading Universal References:
 * Overloading on universal references can cause various issues, as discussed in Item 26. These issues arise
 * in both free-standing and member functions, including constructors.
*/

#include <concepts>
/**
 * Avoiding Overloading:
 * A straightforward way to avoid these problems is to use different function names instead of overloading.
 * This approach is simple but not always applicable, especially for constructors where names are fixed.
*/

/**
 * Alternative Approaches:
 *  - Pass by const T&: Reverting to passing by lvalue-reference-to-const is a viable alternative, although
 *    it may be less efficient than desired.
 *
 *  - Pass by Value: Another option is to pass by value, especially when a copy of the object will be made
 *    anyway. This approach can often offer a balance between efficiency and complexity.
*/

/**
 * Tag Dispatch:
 * For cases where perfect forwarding is essential, tag dispatch can be used. This approach involves
 * passing an additional parameter (a tag) to help with overload resolution, ensuring that the correct
 * function is chosen based on whether the argument is integral or not.
*/
std::string nameFromIdx(int idx);

void logAndAddImpl(int idx, std::true_type) // Integral argument: look up name and call logAndAdd with it
{
    logAndAdd(nameFromIdx(idx));
}


/**
 * Constraining Universal References:
 * Using std::enable_if allows for selectively enabling or disabling templates based on certain conditions.
 * For instance, in the Person class example, the perfect-forwarding constructor can be disabled for
 * arguments of type Person or derived from Person, ensuring that the copy or move constructor is used in
 * these cases.
*/
// C++14
class Person
{
    public:
        template<typename T,
                    std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value &&
                                     !std::is_integral<std::remove_reference_t<T>>::value>
                >
        explicit Person(T&& n)                      // ctor for std::strings and args convertible to std::strings
            : name(std::forward<T>(n)) { }

        explicit Person(int idx)                    // ctor for integral args
            : name(nameFromIdx(idx)) { }

    private:
        std::string name;
};


// C++20 is easier
template <class T>
concept Constraint = !std::derived_from<T, Person> && !std::integral<T>;

class Person
{
    public:
        template<typename T>
            requires Constraint<T>
        explicit Person(T&&n)
            : name(std::forward<T>(n)) { }

        explicit Person(int idx)
            : name(nameFromIdx(idx)) { }

    private:
        std::string name;
};


/**
 * Static Asserts:
 * To enhance error clarity and enforce constraints, static_assert with std::is_constructible can be used
 * in the constructor's body to ensure that the arguments passed can indeed be used to construct the
 * desired type.
*/
