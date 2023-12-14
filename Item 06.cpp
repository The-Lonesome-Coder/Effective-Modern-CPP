#include <vector>
/**
 * Use the explicitly typed initializer idiom when auto deduces undesired types.
 *
 *
 * “Invisible” proxy types can cause auto to deduce the “wrong” type for an initializing expression.
 *
 * The explicitly typed initializer idiom forces auto to deduce the type you want it to have.
*/

/**
 * A key example given is when using std::vector<bool>. Unlike other std::vector types, std::vector<bool> doesn't return
 * a direct reference to a bool with its operator[]. Instead, it returns a std::vector<bool>::reference object, a proxy
 * class that behaves like a bool reference. This proxy is necessary because std::vector<bool> stores its values in a
 * compact, bit-packed form, not as individual bool objects.
 *
 *
 * The problem arises when using auto with such proxy classes. The auto keyword deduces the type directly from the
 * returned proxy object, not the underlying bool value. This can lead to undefined behavior, especially if the proxy
 * object refers to a temporary vector that is destroyed immediately after its creation, leaving behind a dangling
 * pointer.
 *
 *
 * To illustrate, consider the function features(const Widget& w) returning a std::vector<bool>. When using auto to
 * capture the value of a specific feature (like auto highPriority = features(w)[5];), highPriority doesn't become a
 * bool but a std::vector<bool>::reference. If features(w) returns a temporary object, highPriority ends up holding a
 * dangling pointer, leading to undefined behavior.
*/
class Widget { };

std::vector<bool> features(const Widget& w);

Widget w;
bool highPriority = features(w)[5];             // Is w high priority?
processWidget(w, highPriority);                 // Process w in accord with its priority

auto highPriority = features(w)[5];             // Deduce highPriority's type. Is w high priority?
processWidget(w, highPriority);                 // Undefined behavior! highPriority contains dangling pointer!


/**
 * The solution proposed is the "explicitly typed initializer idiom," which involves using auto along with a cast to
 * explicitly specify the type you want to deduce. For example, you could rewrite the above as
 * auto highPriority = static_cast<bool>(features(w)[5]);, ensuring that highPriority is correctly deduced as a bool.
 *
 *
 * This idiom can be applied in other contexts too, such as when reducing precision deliberately (like converting a
 * double to a float), or when a floating-point calculation needs to be stored as an integer. The idiom makes the
 * programmer's intent clear and prevents the unintended consequences of auto's type deduction with proxy classes or
 * complex expressions.
*/
auto highPriority = static_cast<bool>(features(w)[5]);

double calcEpsilon();                           // Return tolerance value
float ep = calcEpsilon();                       // Implicitly convert double → float

auto ep = static_cast<float>(calcEpsilon());    // Idiom