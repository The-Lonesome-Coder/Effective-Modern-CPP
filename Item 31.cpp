#include <functional>
#include <vector>
/**
 * Avoid default capture modes.
 *
 *
 * Default by-reference capture can lead to dangling references.
 *
 * Default by-value capture is susceptible to dangling pointers (especially this), and it misleadingly suggests that
 * lambdas are self-contained.
*/

/**
 * By-Reference Capture:
 * This mode can lead to dangling references. When a lambda captures a local variable or parameter by reference, and the
 * lambda's lifetime exceeds that of the captured entity, the reference becomes invalid or "dangles". The example given
 * is a lambda added to a FilterContainer, capturing a local variable divisor. When divisor goes out of scope, the lambda
 * still references it, leading to undefined behavior.
*/
using FilterContainer = std::vector<std::function<bool(int)>>;

FilterContainer filters;

void addDivisorFilter()
{
    auto calc1 = computeSomeValue1();
    auto calc2 = computeSomeValue2();
    auto divisor = computeDivisor(calc1, calc2);

    // Danger! ref to divisor will dangle!
    filters.emplace_back( [&](int value) { return value % divisor == 0; } );
}

// One way to solve our problem with divisor
// Divisor can't dangle
filters.emplace_back( [=](int value) { return value % divisor == 0; } );


/**
 * By-Value Capture:
 * While this might seem safer, it's not immune to similar problems. Capturing by value copies the captured entities into
 * the lambda, but this can be misleading. For instance, capturing a pointer by value only copies the pointer, not the
 * pointed-to object. If the object is deleted elsewhere, the lambda ends up with a dangling pointer.
*/
class Widget
{
    public:
        void addFilter() const;     // Add an entry to filters

    private:
        int divisor;                // Used in Widget's filter
};

void Widget::addFilter() const
{
    // What’s being captured is the Widget’s this pointer, not divisor
    // (The implicit capture of *this when the capture default is = is deprecated.(since C++20))
    filters.emplace_back( [=](int value) { return value % divisor == 0; } );
}


/**
 * The text also discusses a specific case with class member variables. Since lambdas in member functions can't directly
 * capture member variables, they implicitly capture the this pointer. This can lead to issues if the object the lambda
 * belongs to is destroyed while the lambda is still in use, creating a dangling pointer scenario.
 *
 *
 * The author argues for explicit capture lists in lambdas for clarity and safety. In C++14, generalized lambda capture
 * allows copying a data member into the lambda, reducing risks associated with this pointer capture.
 *
 *
 * The text concludes by highlighting the limitations of default by-value capture. It can give a false impression of
 * lambdas being self-contained, which isn't always true. Lambdas can access static and global variables which they don't
 * capture, leading to unexpected behaviors if these variables change.
 *
 *
 * In summary, the text cautions against the pitfalls of default capture modes in C++ lambdas and advocates for explicit
 * capture lists to improve code safety and clarity.
*/