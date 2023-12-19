#include <memory>
#include <utility>
#include <string>
/**
 * Use std::move on rvalue references, std::forward on universal references.
 *
 *
 * Apply std::move to rvalue references and std::forward to universal references the last time each is used.
 *
 * Do the same thing for rvalue references and universal references being returned from functions that return by value.
 *
 * Never apply std::move or std::forward to local objects if they would otherwise be eligible for the return value
 * optimization.
*/

/**
 * Rvalue References for Moving Objects:
 * Rvalue references in C++ are used specifically for objects that are candidates for moving. When you
 * have an rvalue reference parameter, it's certain that the object it’s bound to can be moved. Therefore,
 * it's appropriate to use std::move to cast these parameters to rvalues when passing them to other
 * functions, enabling the efficient use of move semantics.
*/

/**
 * Universal References and Conditional Casting:
 * Universal references might be bound to objects eligible for moving, but they should only be cast to
 * rvalues using std::forward if they were initialized with rvalues. This conditional casting is necessary
 * because universal references can bind to both lvalues and rvalues.
*/
class SomeDataStructure;

class Widget
{
    public:
        Widget(Widget&& rhs)                    // rhs is rvalue reference
            : name(std::move(rhs.name)), p(std::move(rhs.p)) { }

        template<typename T>
        void setName(T&& newName)               // newName is universal reference
        {
            name = std::forward<T>(newName);
        }

    private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p;
};


/**
 * Incorrect Use of std::move and std::forward:
 * Using std::move on universal references can lead to unintended side effects, such as modifying
 * lvalues. Similarly, using std::forward with rvalue references is considered verbose, error-prone, and
 * non-idiomatic.
*/
class Widget
{
    public:
        // Universal reference compiles, but is bad, bad, bad!
        template<typename T>
        void setName(T&& newName)
        {
            name = std::move(newName);
        }

    private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p;
};

std::string getWidgetName();        // Factory function
Widget w;

// n is local variable moves n into w! n's value now unknown
auto n = getWidgetName();
w.setName(n);


/**
 * Handling Multiple Uses of References in a Function:
 * In cases where a reference (either rvalue or universal) is used multiple times within a function,
 * std::move or std::forward should only be applied to the final use of the reference to ensure it is not
 * prematurely moved from.
*/
template<typename T>
void setSignText(T&& text)                              // text is universal reference
{
    sign.setText(text);                                 // Use text, but don't modify it

    auto now = std::chrono::system_clock::now();        // Get current time

    signHistory.add(now, std::forward<T>(text));        // conditionally cast text to rvalue
}

/**
 * Returning References from Functions:
 * When returning a reference from a function, it's recommended to apply std::move or std::forward to
 * rvalue and universal references, respectively. This practice ensures efficient transfer of resources,
 * especially when dealing with types that support move semantics.
*/

/**
 * Misconception about Local Variables and Return Value Optimization (RVO):
 * A common misconception is that applying std::move to local variables being returned can optimize
 * performance. However, this approach actually prevents compilers from using Return Value Optimization
 * (RVO), a compiler optimization that eliminates unnecessary copying and moving of objects.
*/

/**
 * Implicit RVO in C++ Standards:
 * The C++ Standard mandates that if RVO is permissible but not applied, the object being returned should
 * be treated as an rvalue. This means that explicitly using std::move on a local object being returned is
 * redundant and can potentially hinder compiler optimizations.
*/
