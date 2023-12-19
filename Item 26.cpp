#include <chrono>
#include <set>
#include <string>
#include <utility>
/**
 * Avoid overloading on universal references.
 *
 *
 * Overloading on universal references almost always leads to the universal reference overload being called more
 * frequently than expected.
 *
 * Perfect-forwarding constructors are especially problematic, because they’re typically better matches than copy
 * constructors for non-const lvalues, and they can hijack derived class calls to base class copy and move constructors.
*/

/**
 * Function Example with Universal References:
 * The function `logAndAdd` is used to log the current time and add a name to a global data structure.
 * This function can be optimized by using a universal reference as the parameter and forwarding it to
 * `emplace`, which is more efficient, especially for rvalue and string literal arguments.
*/
std::multiset<std::string> names;

template <typename T>
void logAndAdd(T&& name)
{
    auto now = std::chrono::system_clock::now();

    // make log entry
    log(now, "logAndAdd");

    // Add name to global data structure; see Item 42 for info on emplace
    names.emplace(std::forward<T>(name));
}

std::string petName("Darla");
logAndAdd(petName);                         // Pass lvalue std::string, copy lvalue into multiset
logAndAdd(std::string("Persephone"));       // Pass rvalue std::string, move rvalue instead of copying it
logAndAdd("Patty Dog");                     // Create std::string in multiset instead of copying a temporary std::string



/**
 * Overloading Issues with Universal References:
 * When overloading functions that use universal references, unexpected issues can arise. For instance,
 * if `logAndAdd` is overloaded to accept an integer index, passing a short (instead of an int) to
 * `logAndAdd` results in an error due to the universal reference overload being a better match than the
 * integer overload.
*/

/**
 * Universal References and Greedy Matching:
 * Functions taking universal references tend to "vacuum up" arguments due to exact type matching. This
 * can lead to unexpected behaviors and compilation failures, especially when combined with overloading.
*/
std::string nameFromIdx(int idx);

// New overload
void logAndAdd(int idx)
{
    auto now = std::chrono::system_clock::now();

    log(now, "logAndAdd");

    names.emplace(nameFromIdx(idx));
}


/**
 * Perfect Forwarding Constructor and Its Pitfalls:
 * Implementing a perfect forwarding constructor in a class like `Person` can lead to complications. This
 * constructor can interfere with the expected behavior of copy and move constructors, leading to
 * surprising results and potential compilation failures.
*/
class Person
{
    public:
    template<typename T>
    explicit Person(T&& n)                  // Perfect forwarding ctor;
        : name(std::forward<T>(n)) {}

    explicit Person(int idx)                // int ctor
        : name(nameFromIdx(idx)) {}

    Person(const Person& rhs);              // Copy ctor (compiler-generated)

    Person(Person&& rhs);                   // Move ctor (compiler-generated)

    private:
        std::string name;
};


/**
 * Impact on Derived Classes:
 * In the case of inheritance, derived class copy and move constructors may unexpectedly call the base
 * class’s perfect-forwarding constructor instead of the intended copy or move constructors. This can
 * result in compilation errors.
*/
class SpecialPerson: public Person
{
    public:
        // Copy ctor; calls base class forwarding ctor!
        SpecialPerson(const SpecialPerson& rhs)
            : Person(rhs) { }

        // Move ctor; calls base class forwarding ctor!
        SpecialPerson(SpecialPerson&& rhs)
            : Person(std::move(rhs)) { }
};


/**
 * Avoiding Overloading on Universal References:
 * Due to the complexities and potential pitfalls, it is generally advised to avoid overloading functions
 * on universal references. If different handling for certain types is required, alternative solutions should
 * be sought.
*/
