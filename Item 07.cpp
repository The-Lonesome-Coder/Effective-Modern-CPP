#include <atomic>
#include <vector>
#include <utility>
/**
 * Distinguishing between () and {} when creating objects.
 *
 *
 * Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it’s
 * immune to C++’s most vexing parse.
 *
 * During constructor overload resolution, braced initializers are matched to std::initializer_list parameters if at all
 * possible, even if other constructors offer seemingly better matches.
 *
 * An example of where the choice between parentheses and braces can make a significant difference is creating a
 * std::vector<numeric type> with two arguments.
 *
 * Choosing between parentheses and braces for object creation inside templates can be challenging.
*/

class Widget { };

/**
 * Parentheses (()):
 * Traditional C++ initialization, e.g., int x(0);.
 * Can be misleading for new C++ programmers as it resembles assignment.
 * Differentiates initialization from assignment, important for user-defined types.
 *
 *
 * Equals Sign (=):
 * Another traditional initialization method, e.g., int y = 0;.
 * Also can be misleading, resembling an assignment.
 *
 *
 * Braces ({}):
 * Introduced as part of C++11's uniform (or braced) initialization, e.g., int z{0};.
 * Can be used in almost all contexts.
 * Prevents implicit narrowing conversions among built-in types.
 * Immune to C++'s most vexing parse (a specific parsing ambiguity).
 *
 *
 * Equals Sign and Braces Combined (={}):
 * Similar to braced initialization, e.g., int z = {0};.
 * Generally treated the same as braces-only syntax.
 *
*/
int x(0);                   // Initializer is in parentheses
int y = 0;                  // Initializer follows "="
int z { 0 };                // Initializer is in braces
int z = { 0 };              // Initializer uses "=" and braces

Widget w1;                  // Call default constructor
Widget w2 = w1;             // Not an assignment; calls copy ctor
w1 = w2;                    // An assignment; calls copy operator=


/**
 * Braced initialization is particularly useful for initializing containers with specific values
 * (e.g., std::vector<int> v{1, 3, 5};) and for default initialization values in class members. However, it can behave
 * unexpectedly due to its interaction with std::initializer_list and constructor overload resolution. When a constructor
 * with std::initializer_list is available, braced initialization tends to favor it, even if it's not the most intuitive
 * match.
 *
 * An interesting case arises with empty braces {}. While they signify default construction for an object, if the object
 * supports std::initializer_list, empty braces {} can be interpreted as an empty std::initializer_list, leading to
 * potential ambiguity.
 *
 * The author suggests that while braced initialization offers several advantages, its sometimes unpredictable behavior,
 * especially with std::initializer_list, requires careful consideration. This is particularly true for class authors who
 * need to be mindful of how std::initializer_list constructors can affect clients using braced initialization.
 *
 * The choice between parentheses and braces often comes down to personal or project preference. Each has its merits:
 * braces prevent narrowing conversions and avoid the most vexing parse, while parentheses align with traditional C++
 * syntax and sidestep some of the complexities introduced by std::initializer_list.
*/
std::vector<int> v { 1, 3, 5 };      // v's initial content is 1, 3, 5

class Widget
{
    public:
        Widget(); // default ctor
        Widget(std::initializer_list<int> il);  // std::initializer_list ctor no implicit conversion funcs
};

Widget w1;                          // Calls default ctor
Widget w2 { };                      // Also calls default ctor
Widget w3();                        // Most vexing parse! Declares a function!
Widget w4( { } );                   // Calls std::initializer_list ctor with empty list
Widget w5{ { } };                   // Same as above

// Use non-std::initializer_list ctor: create 10-element std::vector, all elements have value of 20
std::vector<int> v1(10, 20);

// Use std::initializer_list ctor: create 2-element std::vector, element values are 10 and 20
std::vector<int> v2 { 10, 20 };


/**
 * For template authors, this choice can be challenging, as it's not always clear which method should be used. Functions
 * like std::make_unique and std::make_shared solve this by internally using parentheses and documenting this choice.
*/
template<typename T, typename ... Ts>
void doSomeWork(Ts&& ... params)
{
    T localObject(std::forward<Ts>(params)...);             // Using parens
    T localObject { std::forward<Ts>(params)... };          // Using braces
}