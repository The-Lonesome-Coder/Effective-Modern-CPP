#include <memory>
#include <mutex>
/**
 * Prefer nullptr to 0 and NULL.
 *
 *
 * Prefer nullptr to 0 and NULL.
 *
 * Avoid overloading on integral and pointer types.
*/

class Widget { };

/**
 * Literal 0 and NULL:
 * In C++, the literal 0 is primarily an integer, not a pointer. If C++ requires a pointer in a context where 0 is used,
 * it grudgingly treats 0 as a null pointer.
 *
 * NULL also typically represents an integer and might be defined as 0 or another integral type like 0L (long zero).
 * However, neither 0 nor NULL inherently has a pointer type.
 *
 * This can cause surprises in function overloading. When 0 or NULL is passed to overloaded functions that have both
 * pointer and integral parameter types, the integral overload is chosen, not the pointer one.
 *
 * There is ambiguity in NULL's behavior because its interpretation depends on its definition, which can vary between
 * implementations.
*/
void f(int);            // Three overloads of f
void f(bool);
void f(void*);

f(0);                   // Calls f(int), not f(void*)
f(NULL);                // Might not compile, but typically calls f(int). Never calls f(void*)


/**
 * Introduction of nullptr:
 * nullptr was introduced to address these ambiguities and provide a clear, unambiguous way to represent null pointers.
 *
 * nullptr's actual type is std::nullptr_t, which is defined as the type of nullptr. This type can implicitly convert to
 * all raw pointer types, effectively making nullptr act like a pointer of all types.
 *
 * Using nullptr avoids overload resolution surprises and improves code clarity, especially with auto variables or in
 * templates.
*/
f(nullptr);             // Calls f(void*) overload


/**
 * Practical Implications:
 * The use of 0 or NULL can lead to less clear code. For instance, when auto is used with 0 or NULL, it's not immediately
 * clear whether the result is a pointer or an integer.
 *
 * nullptr is particularly beneficial in templates, where passing 0 or NULL can lead to type deduction issues. For
 * example, in a template function expecting a pointer type, passing 0 or NULL results in the deduced type being an
 * integer, leading to compilation errors.
 *
 *
 * Example with lockAndCall Template Function:
 * The author presents a lockAndCall template function that demonstrates the problem with using 0 or NULL. When 0 or
 * NULL is passed to this function, template type deduction deduces them as integers, resulting in type errors when the
 * function expects pointer types.
 *
 * In contrast, passing nullptr works correctly because it is deduced as std::nullptr_t, which can be implicitly
 * converted to any pointer type.
*/
// Call these only when the appropriate mutex is locked
int f1(std::shared_ptr<Widget> spw);
double f2(std::unique_ptr<Widget> upw);
bool f3(Widget* pw);

// Mutexes for f1, f2, and f3

std::mutex f1m, f2m, f3m;
using MuxGuard = std::lock_guard<std::mutex>;

{
    MuxGuard g(f1m);                // Lock mutex for f1
    auto result = f1(0);            // Pass 0 as null ptr to f1 unlock mutex
}

{
    MuxGuard g(f2m);                // Lock mutex for f2
    auto result = f2(NULL);         // Pass NULL as null ptr to f2 unlock mutex
}

{
    MuxGuard g(f3m);                // Lock mutex for f3
    auto result = f3(nullptr);      // Pass nullptr as null ptr to f3 unlock mutex
}

// C++14
template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr) -> decltype(func(ptr))
{
    MuxGuard g(mutex);

    return func(ptr);
}
