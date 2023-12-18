#include <memory>
/**
 * Prefer std::make_unique and std::make_shared to direct use of new.
 *
 *
 * Compared to direct use of new, make functions eliminate source code duplication, improve exception safety, and, for
 * std::make_shared and std::allocate_shared, generate code that’s smaller and faster.
 *
 * Situations where use of make functions is inappropriate include the need to specify custom deleters and a desire to
 * pass braced initializers.
 *
 * For std::shared_ptrs, additional situations where make functions may be ill-advised include:
 * (1) classes with custom memory management
 * (2) systems with memory concerns, very large objects, and std::weak_ptrs that outlive the corresponding
 *     std::shared_ptrs.
*/

class Widget { };

/**
 * Introduction of std::make_unique and std::make_shared:
 * `std::make_shared` is part of C++11, whereas `std::make_unique` was introduced in C++14. A basic
 * version of `std::make_unique` can be easily written for C++11.
*/

/**
 * Functionality of make_unique and make_shared:
 * These functions create a smart pointer (`std::unique_ptr` or `std::shared_ptr`) and perfect-forward
 * their parameters to the constructor of the object being created.
*/
auto upw1(std::make_unique<Widget>());          // With make func
std::unique_ptr<Widget> upw2(new Widget);       // Without make func

auto spw1(std::make_shared<Widget>());          // With make func
std::shared_ptr<Widget> spw2(new Widget);       // Without make func


/**
 * Advantages of Using Make Functions:
 * - Reduced Code Duplication: Using make functions avoids repeating the type being created, adhering
 *   to the principle of avoiding code duplication.
 *
 * - Exception Safety: Make functions offer better exception safety. For instance, when passing a
 *   `std::shared_ptr` or `std::unique_ptr` to a function, using make functions prevents potential
 *   resource leaks that could occur with direct use of `new`.
*/
class ReallyBigType { };

// Create very large object via std::make_shared
auto pBigObj = std::make_shared<ReallyBigType>();

    // Create std::shared_ptrs and std::weak_ptrs to large object, use them to work with it
    // Final std::shared_ptr to object destroyed here, but std::weak_ptrs to it remain
    // During this period, memory formerly occupied by large object remains allocated
    // Final std::weak_ptr to object destroyed here; memory for control block and object is released


/**
 * Efficiency of std::make_shared:
 * Using `std::make_shared` is more efficient than directly using `new` as it can allocate memory for
 * both the object and its control block in a single allocation, reducing memory usage and improving
 * performance.
*/

/**
 * Limitations and Special Cases:
 * - Custom Deleters and Braced Initializers: The make functions do not support custom deleters or
 *   braced initializers. In such cases, direct use of `new` with smart pointer constructors is necessary.
 *
 * - Objects with Class-Specific `new` and `delete`: For classes with their own memory allocation and
 *   deallocation routines, using make functions might not be suitable.
*/

/**
 * Exception-Safety with Direct Use of `new`:
 * When direct use of `new` is required, it should be immediately passed to a smart pointer constructor
 * in a statement that does nothing else to maintain exception safety.
*/

/**
 * Performance Considerations:
 * When passing a smart pointer to a function, using `std::move` can be more efficient as it avoids
 * atomic increment of the reference count involved in copying a `std::shared_ptr`.
*/
void processWidget(std::shared_ptr<Widget> spw, int priority);
void cusDel(Widget *ptr);       // Custom deleter

std::shared_ptr<Widget> spw { new Widget, cusDel };

processWidget(std::move(spw), computePriority());   // Both efficient and exception safe