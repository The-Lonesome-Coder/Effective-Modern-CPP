#include <memory>
#include <unordered_map>
/**
 * Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
 *
 *
 * Use std::weak_ptr for std::shared_ptr-like pointers that can dangle.
 *
 * Potential use cases for std::weak_ptr include caching, observer lists, and the prevention of std::shared_ptr cycles.
*/

class Widget;
class WidgetID;

/**
 * Purpose of std::weak_ptr:
 * `std::weak_ptr` is a smart pointer that acts like `std::shared_ptr` but does not participate in shared
 * ownership, meaning it doesn’t affect the object’s reference count. It addresses the problem of
 * potentially dangling pointers by tracking if the pointed-to object exists.
*/

/**
 * Creation and Relationship with std::shared_ptr:
 * `std::weak_ptr` is typically created from a `std::shared_ptr` and points to the same object without
 * increasing the reference count. If the `std::shared_ptr` is destroyed or reassigned, the
 * `std::weak_ptr` may dangle.
*/
// After spw is constructed, the pointed-to Widget's
auto spw = std::make_shared<Widget>();

// Ref count (RC) is 1. (See Item 21 for info on std::make_shared.)

// wpw points to same Widget as spw. RC remains 1
std::weak_ptr<Widget> wpw(spw);

// RC goes to 0, and the Widget is destroyed. wpw now dangles
spw = nullptr;


/**
 * Checking for Dangling Pointers:
 * `std::weak_ptr` cannot be dereferenced or checked for nullness. Instead, it provides a method to test
 * if it has expired (i.e., the object it points to has been destroyed). To safely access the object, a
 * `std::shared_ptr` is created from the `std::weak_ptr`.
*/
// If wpw doesn't point to an object ...
if (wpw.expired())
{
    /* Do something */
}

// If wpw's expired, spw1 is null
std::shared_ptr<Widget> spw1 = wpw.lock();

// Same as above, but uses auto
auto spw2 = wpw.lock();

// If wpw's expired, throw std::bad_weak_ptr
std::shared_ptr<Widget> spw3(wpw);


/**
 * Use Cases:
 * - Caching Mechanisms: `std::weak_ptr` is useful in caching scenarios where objects are created and
 *   stored for potential reuse. It allows for efficient resource management by destroying cached objects
 *   that are no longer in use.
 *
 * - Observer Pattern: In the Observer design pattern, subjects can use `std::weak_ptr` to hold pointers
 *   to observers, allowing subjects to detect if an observer has been destroyed before trying to access
 *   it.
 *
 * - Avoiding Cycles in Shared Ownership: `std::weak_ptr` helps in preventing cycles in shared ownership
 *   scenarios (e.g., in non-hierarchical data structures), where mutual `std::shared_ptr` references
 *   could lead to resource leaks.
*/
std::shared_ptr<const Widget> fastLoadWidget(WidgetID id)
{
    static std::unordered_map<WidgetID, std::weak_ptr<const Widget>> cache;

    // objPtr is std::shared_ptr to cached object (or null if object's not in cache)
    auto objPtr = cache[id].lock();

    // If not in cache
    if (!objPtr)
    {
        // Load it
        objPtr = loadWidget(id);

        // Cache it
        cache[id] = objPtr;
    }

    return objPtr;
}


/**
 * Efficiency Considerations:
 * `std::weak_ptr` has a similar efficiency profile to `std::shared_ptr`, involving atomic operations for
 * reference count manipulations. However, it manages a secondary reference count in the control block
 * that tracks the number of `std::weak_ptrs` pointing to an object.
*/