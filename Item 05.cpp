#include <functional>
#include <memory>
/**
 * Prefer auto to explicit type declarations.
 *
 *
 * auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency
 * problems, can ease the process of refactoring, and typically require less typing than variables with explicitly
 * specified types.
 *
 * auto-typed variables are subject to the pitfalls described in Items 2 and 6.
*/

/**
 * Initially, it highlights common frustrations in C++ like uninitialized variables and complex declarations (like
 * dereferencing an iterator). The author expresses the annoyance with the verbosity required in these contexts and the
 * potential for error.
*/


/**
 * The introduction of auto in C++11 is portrayed as a significant improvement. It automatically deduces the type from
 * the initializer, thus solving problems like uninitialized variables. For example, int x1 could be uninitialized, but
 * auto x2 needs an initializer, eliminating this issue. auto also simplifies declaring variables that hold dereferenced
 * iterators or closures, reducing verbosity and potential errors.
*/
int x1;                 // Potentially uninitialized
auto x2;                // Error! initializer required
auto x3 = 0;            // Fine, x's value is well-defined


/**
 * C++14 further enhances auto by allowing its use in lambda expressions. This increases the language's efficiency and
 * expressiveness.
*/
class Widget { };

// Comparison func for Widgets pointed to by std::unique_ptrs
auto derefUPLess =
[](const std::unique_ptr<Widget>& p1,  const std::unique_ptr<Widget>& p2)
{
    return *p1 < *p2;
};

// C++14 comparison function for values pointed to by anything pointer-like
auto derefLess =
[](const auto& p1, const auto& p2)
{
    return *p1 < *p2;
};


/**
 * The author compares auto with std::function. While std::function can refer to any callable object, using auto for
 * closures is more efficient in terms of memory and speed, as std::function may require additional memory allocation.
*/
// C++11 signature for std::unique_ptr<Widget> comparison function
bool someFunction(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&);

// You’d write this
std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)> func;

// We could declare the C++11 version of derefUP Less without using auto as follows
std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)> derefUPLess =
[](const std::unique_ptr<Widget>& p1, const std::unique_ptr<Widget>& p2)
{
    return *p1 < *p2;
};


/**
 * The passage also addresses the potential for subtle errors in explicit type declarations. For example, using unsigned
 * instead of std::vector<int>::size_type can lead to issues, especially when porting code between 32-bit and 64-bit
 * systems. Using auto avoids such mismatches.
*/
std::vector<int> v;
unsigned sz = v.size();         // The official return type of v.size() is actually std::vector<int>::size_type

auto sz = v.size();             // Using auto ensures sz's type is std::vector<int>::size_type


/**
 * Additionally, the author discusses the value of type inference, common in other languages, and addresses concerns
 * about readability. While auto might obscure the exact type of an object, this is often mitigated by IDEs and the
 * context provided by well-chosen variable names.
 *
 *
 * In conclusion, auto in C++ is presented as a feature that reduces errors and verbosity, simplifies code, and makes it
 * more adaptable to changes. However, the author acknowledges that explicit type declarations may still be appropriate
 * in some cases, leaving the decision to the programmer's judgment.
*/