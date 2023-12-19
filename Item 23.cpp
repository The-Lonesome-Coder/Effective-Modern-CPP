#include <string>
#include <utility>
/**
 * Understand std::move and std::forward.
 *
 *
 * std::move performs an unconditional cast to an rvalue. In and of itself, it doesn’t move anything.
 *
 * std::forward casts its argument to an rvalue only if that argument is bound to an rvalue.
 *
 * Neither std::move nor std::forward do anything at runtime.
*/

class Widget;

/**
 * std::move and std::forward Functionality:
 * Contrary to what their names might suggest, std::move and std::forward do not perform any moving or
 * forwarding operations at runtime. They do not generate executable code. Instead, these functions are
 * template functions used for casting. std::move casts its argument to an rvalue unconditionally, while
 * std::forward does so conditionally.
*/

/**
 * std::move Implementation and Behavior:
 * The std::move function is essentially a cast that turns its parameter into an rvalue reference. This
 * is achieved by applying std::remove_reference to the parameter type to ensure it's not a reference before
 * applying the rvalue reference operator (&&). Even though std::move casts an object to an rvalue, it
 * doesn’t guarantee the object is eligible to be moved, especially if the object is const.
*/
// C++14; still in namespace std
template<typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = remove_reference_t<T>&&;

    return static_cast<ReturnType>(param);
}

/**
 * In this example:
 * 1. Don’t declare objects const if you want to be able to move from them. Move requests on const objects are silently
 *    transformed into copy operations.
 *
 * 2. std::move not only doesn’t actually move anything, it doesn’t even guarantee that the object it’s casting will be
 *    eligible to be moved. The only thing you know for sure about the result of applying std::move to an object is that
 *    it’s an rvalue.
*/
class Annotation
{
    public:
        // "move" text into value; this code doesn't do what it seems to do
        explicit Annotation(const std::string text)
            : value(std::move(text)) { }

    private:
        std::string value;
};


/**
 * std::forward and Conditional Casting:
 * std::forward is used for conditional casting. It casts to an rvalue only if the original argument was
 * an rvalue. This functionality is crucial in templates dealing with universal references, where it’s
 * necessary to maintain the original value category (lvalue or rvalue) of the passed argument.
*/
void process(const Widget& lvalArg);                // Process lvalues
void process(Widget&& rvalArg);                     // Process rvalues

// Template that passes param to process
template<typename T>
void logAndProcess(T&& param)
{
    auto now = std::chrono::system_clock::now();    // Get current time

    makeLogEntry("Calling 'process'", now);

    process(std::forward<T>(param));
}

Widget w;

logAndProcess(w);                                   // Call with lvalue
logAndProcess(std::move(w));                        // Call with rvalue



/**
 * Usage Contexts and Differences:
 * std::move is simpler, requiring only the function argument, while std::forward also requires a template
 * type argument. The use of std::move suggests an unconditional cast to an rvalue, often setting up a move
 * operation. std::forward, on the other hand, retains the original lvalueness or rvalueness of an object,
 * forwarding it appropriately. These functions serve different purposes, with std::move primarily used to
 * enable move semantics and std::forward used in forwarding universal references in template functions.
*/
class Widget
{
    public:
        Widget(Widget&& rhs)
            : s(std::move(rhs.s))
        {
            ++moveCtorCalls;
        }

    private:
        static std::size_t moveCtorCalls;
        std::string s;
};

class Widget
{
    public:
        // Unconventional, undesirable implementation
        Widget(Widget&& rhs)
            : s(std::forward<std::string>(rhs.s))
        {
            ++moveCtorCalls;
        }

     private:
        static std::size_t moveCtorCalls;
        std::string s;
};


/**
 * Practical Implications:
 * It's important to understand these functions do not perform actions themselves but affect how objects are
 * treated in terms of move semantics and function argument forwarding. Misunderstanding their use can lead
 * to incorrect assumptions about object states, especially concerning move operations.
*/
