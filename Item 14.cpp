#include <vector>
/**
 * Declare functions noexcept if they won't emit exceptions.
 *
 *
 * noexcept is part of a function’s interface, and that means that callers may depend on it.
 *
 * noexcept functions are more optimizable than non-noexcept functions.
 *
 * noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.
 *
 * Most functions are exception-neutral rather than noexcept.
*/

class Widget { };

/**
 * C++98 Exception Specifications:
 * Required specifying the types of exceptions a function could throw.
 *
 * Changing these specifications could break client code, as they might depend on the original specification.
 *
 * Maintaining consistency among function implementations, specifications, and client code was challenging, leading many
 * programmers to avoid using them.
*/
// No exceptions from f: C++98 style
int f(int x) throw();


/**
 * C++11 Changes:
 * Shifted focus to whether a function could throw exceptions at all, leading to a simpler, binary approach: functions
 * might throw exceptions or guarantee they won't (using noexcept).
 *
 * noexcept functions provide key information for clients about exception safety and efficiency.
 *
 * Declaring a function noexcept when it won't throw exceptions is essential for accurate interface specification.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Optimization Opportunities:
 * noexcept allows compilers to optimize better, as they don't need to keep the runtime stack in an unwound state if an
 * exception propagates out.
 *
 * Functions with noexcept are more optimizable than those with either throw() or no specification at all.
*/
// No exceptions from f: C++11 style
int f(int x) noexcept;


/**
 * Impact on Move Operations and std::vector:
 * In C++11, std::vector and similar functions can optimize by replacing copy operations with moves if the moves are
 * noexcept.
 *
 * The exception safety guarantee is maintained only if move operations are known not to throw exceptions.
*/
std::vector<Widget> vw;

Widget w;

vw.push_back(w);

/**
 * swap Functions:
 * swap functions's noexcept status can impact the noexcept status of higher-level data structures, making it crucial for
 * user-defined swap functions to be noexcept whenever possible.
*/
template <class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

template <class T1, class T2>
struct pair
{
    void swap(pair& p) noexcept(noexcept(swap(first, p.first)) && noexcept(swap(second, p.second)));
};


/**
 * Caution in Declaring noexcept:
 * Declaring a function noexcept should be a long-term commitment, as changing this later can break client code or lead
 * to program termination if an exception is thrown.
 *
 * Most functions are exception-neutral and should not be declared noexcept.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Implicit noexcept in C++11:
 * By default, destructors and memory deallocation functions are noexcept.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Wide vs. Narrow Contracts:
 * Functions with wide contracts (no preconditions) that don't emit exceptions should be declared noexcept.
 *
 * Functions with narrow contracts (preconditions exist) may not be suitable for noexcept if checking for precondition
 * violations involves throwing exceptions.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Compiler Assistance:
 * Compilers typically do not help in identifying inconsistencies between function implementations and their exception
 * specifications.
*/