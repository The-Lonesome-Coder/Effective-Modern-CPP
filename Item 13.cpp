#include <vector>
/**
 * Prefer const_iterators to iterators.
*/

/**
 * Concept of const_iterators:
 * They are similar to pointers-to-const and are used when there is no need to modify the value they point to. The
 * standard practice recommends using const_iterators whenever modification is not required.
*/


/**
 * C++98 Limitations:
 * Creating const_iterators was challenging.
 *
 * Limited functionality once created.
 *
 * Example given: searching and inserting in a std::vector<int>. In C++98, using const_iterators was cumbersome,
 * requiring casts and not supporting direct insertion.
 *
 * No direct way to convert a const_iterator to an iterator, making some operations difficult or impossible.
*/
// Typedefs
typedef std::vector<int>::iterator IterT;
typedef std::vector<int>::const_iterator ConstIterT;

std::vector<int> values;

// Cast
ConstIterT ci = std::find(static_cast<ConstIterT>(values.begin()),
                          static_cast<ConstIterT>(values.end()),
                          1983);

// May not compile
values.insert(static_cast<IterT>(ci), 1998);


/**
 * C++11 Improvements:
 * const_iterators became easier to obtain and use.
 *
 * cbegin and cend functions introduced to produce const_iterators for non-const containers.
 *
 * STL functions like insert and erase started accepting const_iterators.
 *
 * This made the use of const_iterators more practical and aligned with the principle of using const whenever possible.
*/
std::vector<int> values;

auto it = std::find(values.cbegin(),values.cend(), 1983);

values.insert(it, 1998);


/**
 * C++14 Enhancements:
 * Added non-member functions like cbegin, cend, rbegin, rend, crbegin, and crend, which were missing in C++11.
 *
 * This further facilitated the use of const_iterators in generic library code, making them more versatile and applicable
 * to a wider range of scenarios, including third-party libraries and built-in arrays.
*/
// In container, find first occurrence of targetVal, then insert insertVal there
template<typename C, typename V>
void findAndInsert(C& container, const V& targetVal, const V& insertVal)
{
    using std::cbegin;
    using std::cend;

    // Non-member cbegin & non-member cend
    auto it = std::find(cbegin(container), cend(container), targetVal);

    container.insert(it, insertVal);
}


/**
 * General Advice:
 * The text encourages the use of const_iterators in C++11 and beyond, where their practicality is significantly improved.
 *
 * The improvements in C++11 and C++14 make adhering to the best practice of using const wherever meaningful, feasible,
 * and practical when working with iterators.
*/
template <class C>
auto cbegin(const C& container) -> decltype(std::begin(container))
{
    return std::begin(container);
}