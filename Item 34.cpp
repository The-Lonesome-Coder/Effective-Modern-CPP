#include <chrono>
#include <functional>
/**
 * Prefer lambdas to std::bind.
 *
 *
 * Lambdas are more readable, more expressive, and may be more efficient than using std::bind.
 *
 * In C++11 only, std::bind may be useful for implementing move capture or for binding objects with templatized function
 * call operators.
*/

class Widget;

/**
 * Background of std::bind:
 * `std::bind` is the successor to C++98’s `std::bind1st` and `std::bind2nd`, formally becoming part of the
 * Standard Library in 2005 with TR1.
 *
 * It's seen significant use over the years, but with the advent of C++11 and C++14, lambdas have largely surpassed
 * `std::bind` in utility.
*/

/**
 * Advantages of Lambdas over std::bind:
 * Readability:
 * Lambdas tend to be more readable and intuitive compared to the usage of `std::bind`.
 *
 * Explicitness:
 * With lambdas, the capture of variables (by value or reference) and the passing of parameters are explicit, unlike in
 * `std::bind`.
 *
 * Overloads and Inlining:
 * Lambdas handle function overloads more gracefully and are more likely to be inlined by compilers, potentially leading
 * to performance benefits.
*/

/**
 * Issues with std::bind:
 * Complexity in Usage:
 * `std::bind` often leads to more complex and less readable code, especially when dealing with overloads or deferred
 * evaluation.
 *
 * Implicit Behavior:
 * It’s not always clear how `std::bind` stores its arguments (by value or reference) and how it passes them to the
 * function it binds to.
*/

/**
 * Lambdas in C++14:
 * C++14 further strengthens the case for lambdas with features like auto parameters in lambda expressions,
 * making them more versatile and powerful.
*/

/**
 * Edge Cases for std::bind:
 * In C++11, `std::bind` may still be used for move capture and creating polymorphic function objects, but
 * these are rare and specific cases.
 *
 * With C++14, even these edge cases can be handled more elegantly with lambdas.
*/

/**
 * Conclusion:
 * While `std::bind` was a significant improvement in its time, the introduction and evolution of lambda
 * expressions in C++11 and C++14 have made `std::bind` almost obsolete. Lambdas offer greater readability,
 * explicitness, and flexibility, making them the preferred choice in modern C++ programming.
*/
using Time = std::chrono::steady_clock::time_point;
enum class Sound { Beep, Siren, Whistle };

using Duration = std::chrono::steady_clock::duration;
void setAlarm(Time t, Sound s, Duration d);

auto setSoundL = [](Sound s)
{
    using namespace std::chrono;
    using namespace std::literals;                  // For C++14 suffixes

    setAlarm(steady_clock::now() + 1h, s, 30s);
};

using namespace std::chrono;
using namespace std::literals;
using namespace std::placeholders;                  // Needed for use of "_1"

// "B" for "bind"; this is incorrect
auto setSoundB = std::bind(setAlarm, steady_clock::now() + 1h, _1, 30s);

// Correct
auto setSoundB = std::bind(setAlarm, std::bind(std::plus<steady_clock::time_point>(), steady_clock::now(), 1h), _1, 30s);

/* ---------------------------------------------------------------------------------------------------------------- */

// When setAlarm is overloaded, a new issue arises
enum class Volume { Normal, Loud, LoudPlusPlus };

void setAlarm(Time t, Sound s, Duration d, Volume v);

auto setSoundL = [](Sound s)
{
    using namespace std::chrono;

    // Fine, calls 3-arg version of setAlarm
    setAlarm(steady_clock::now() + 1h, s, 30s);
};

// Error -  which setAlarm?
auto setSoundB = std::bind(setAlarm, std::bind(std::plus<>(), steady_clock::now(), 1h), _1, 30s);

// To get the std::bind call to compile
using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);

// Now okay
auto setSoundB = std::bind(static_cast<SetAlarm3ParamType>(setAlarm), std::bind(std::plus<>(), steady_clock::now(), 1h), _1, 30s);

/* ---------------------------------------------------------------------------------------------------------------- */

// Compression level
enum class CompLevel { Low, Normal, High };

// Make compressed copy of w
Widget compress(const Widget& w, CompLevel lev);

Widget w;

using namespace std::placeholders;

auto compressRateB = std::bind(compress, w, _1);

// w is captured by value; lev is passed by value
auto compressRateL = [w](CompLevel lev)
{
    return compress(w, lev);
};

/* ---------------------------------------------------------------------------------------------------------------- */

// std::bind always copies its arguments, but callers can achieve the effect of having an argument stored by reference
// by applying std::ref to it. The result of:

auto compressRateB = std::bind(compress, std::ref(w), _1);

// is that compressRateB acts as if it holds a reference to w, rather than a copy.