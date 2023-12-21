#include <vector>
/**
 * Familiarize yourself with perfect forwarding failure cases.
 *
 *
 * Perfect forwarding fails when template type deduction fails or when it deduces the wrong type.
 *
 * The kinds of arguments that lead to perfect forwarding failure are braced initializers, null pointers expressed as 0
 * or NULL, declaration-only integral const static data members, template and overloaded function names, and bitfields.
*/

/**
 * Item 30 of Scott Meyers' guide on C++11 delves into the intricacies and limitations of perfect forwarding, a
 * much-lauded feature of the language. Perfect forwarding aims to allow a function to pass its arguments to another
 * function while preserving their exact characteristics, including type, value category (lvalue or rvalue), and
 * const/volatile qualifiers. This is achieved using universal references and the std::forward function.
 *
 *
 * However, the term "perfect" in perfect forwarding is somewhat of an overstatement. There are specific scenarios where
 * perfect forwarding fails, which are important for C++ developers to recognize and understand.
*/
template <typename T>
void fwd(T&& param)                     // Accept any argument
{
    f(std::forward<T>(param));          // Forward it to f
}

template <typename... Ts>
void fwd(Ts&&... params)                // Accept any arguments
{
    f(std::forward<Ts>(params)...);     // Forward them to f
}

f(/* expression */);                    // If this does one thing,
fwd(/* expression */);                  // but this does something else,
                                        // fwd fails to perfectly forward expression to f

/**
 * Braced Initializers:
 * Passing a braced initializer directly to a forwarding function doesn't work because the type cannot be deduced. For
 * example, forwarding { 1, 2, 3 } to a function expecting a std::vector<int> won't compile. A workaround involves using
 * an auto variable to deduce the type as std::initializer_list and then forwarding it.
*/
void f(const std::vector<int>& v);

f( { 1, 2, 3 } );                       // Fine, "{1, 2, 3}" implicitly converted to std::vector<int>
fwd( { 1, 2, 3 } );                     // Error! doesn't compile

auto ls = { 1, 2, 3 };                  // ls's type deduced to be std::initializer_list<int>
fwd(ls);                                // Fine, perfect-forwards il to f


/**
 * 0 or NULL as Null Pointers:
 * Perfect forwarding fails with 0 or NULL as null pointers, as they get deduced as integers, not pointers. The
 * solution is to use nullptr instead.
*/


/**
 * Declaration-Only Integral Static Const Data Members:
 * For classes with integral static const data members that are declared but not defined, forwarding can fail due to
 * the need for an address for the reference. The fix is to provide a definition for these members.
*/
class Widget
{
    public:
        static const std::size_t MinVals { 28 };        // MinVals' declaration
};

std::vector<int> widgetData;
widgetData.reserve(Widget::MinVals);                    // Use of MinVals

void f(std::size_t val);

f(Widget::MinVals);                                     // Fine, treated as "f(28)"
fwd(Widget::MinVals);                                   // Error! shouldn't link

const std::size_t Widget::MinVals;                      // Definition in Widget's .cpp file


/**
 * Overloaded Function Names and Template Names:
 * When trying to forward an overloaded function or a function template, the compiler can't deduce the correct version
 * to use. The solution is to explicitly specify the version using a function pointer or static_cast.
*/
void f(int (*pf)(int));                     // pf = "processing function"
void f(int pf(int));                        // Declares same f as above

int processVal(int value);
int processVal(int value, int priority);

f(processVal);                              // Fine
fwd(processVal);                            // Error! which processVal?

// Template for processing values
template<typename T>
T workOnVal(T param)
{
    /* ... */
}

fwd(workOnVal);                                 // Error! which workOnVal instantiation?

// Solution
using ProcessFuncType = int (*)(int);
ProcessFuncType processValPtr = processVal;     // Specify needed signature for processVal

fwd(processValPtr);                             // Fine
fwd(static_cast<ProcessFuncType>(workOnVal));   // Also fine


/**
 * Bitfields:
 * Forwarding a bitfield directly is impossible because non-const references cannot bind to bitfields. The solution is
 * to make a copy of the bitfield value and forward that instead.
*/
struct IPv4Header
{
    std::uint32_t   version:        4,
                    IHL:            4,
                    DSCP:           6,
                    ECN:            2,
                    totalLength:    16;
};

void f(std::size_t sz);     // Function to call

IPv4Header h;

f(h.totalLength);           // Fine
fwd(h.totalLength);         // Error!

// Copy bitfield value; see Item 6 for info on init. form
auto length = static_cast<std::uint16_t>(h.totalLength);

fwd(length);                // Forward the copy

/**
 * Despite these limitations, perfect forwarding is often effective and simplifies code in many scenarios. However, when
 * it does fail, it's crucial to understand these failure cases and know how to work around them. Each failure case has
 * a straightforward solution, ensuring that code using perfect forwarding remains robust and portable.
*/