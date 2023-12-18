#include <memory>
#include <vector>
/**
 * Use std::shared_ptr for shared-ownership resource management.
 *
 *
 * std::shared_ptrs offer convenience approaching that of garbage collection for the shared lifetime management of
 * arbitrary resources.
 *
 * Compared to std::unique_ptr, std::shared_ptr objects are typically twice as big, incur overhead for control blocks,
 * and require atomic reference count manipulations.
 *
 * Default resource destruction is via delete, but custom deleters are supported. The type of the deleter has no effect
 * on the type of the std::shared_ptr.
 *
 * Avoid creating std::shared_ptrs from variables of raw pointer type.
*/

class Widget;

/**
 * Garbage Collection vs. Deterministic Destruction:
 * C++ programmers prefer the predictability and control of destructors over the non-determinism of garbage collection.
 * `std::shared_ptr` merges these concepts by managing the lifetime of objects automatically with deterministic
 * destruction timing.
 */

/**
 * Shared Ownership:
 * An object accessed via `std::shared_ptr` has its lifetime managed through shared ownership by all `std::shared_ptrs`
 * that point to it. The object is destroyed when the last `std::shared_ptr` referencing it is gone.
*/

/**
 * Reference Counting Mechanism:
 * `std::shared_ptr` manages object lifetime using a reference count. Constructors increment this count, destructors
 * decrement it, and assignment operators do both. A reference count of zero triggers the destruction of the object.
*/

/**
 * Performance Considerations:
 * `std::shared_ptr` is larger than raw pointers (twice the size) due to storing the object pointer and the reference
 * count. Reference count updates require atomic operations for thread safety, which can be slower than non-atomic
 * operations.
*/

/**
 * Move Semantics:
 * Moving a `std::shared_ptr` is faster than copying, as it doesn't require reference count modification.
*/

/**
 * Custom Deleters:
 * `std::shared_ptr` supports custom deleters, but unlike `std::unique_ptr`, the deleter type doesn't affect the
 * `std::shared_ptr`'s type, offering greater flexibility.
*/
// Custom deleter (as in Item 18)
auto loggingDel = [](Widget *pw)
{
    makeLogEntry(pw);

    delete pw;
};

// Deleter type is part of ptr type
std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel);

// Deleter type is not part of ptr type
std::shared_ptr<Widget> spw(new Widget, loggingDel);


/**
 * Control Blocks:
 * The reference count and custom deleter are part of a control block, which also includes other data. Control blocks
 * are dynamically allocated and ensure proper object destruction.
*/

/**
 * Creation Rules:
 * Rules govern control block creation to prevent multiple control blocks for the same object, which would lead to
 * undefined behavior.
*/

/**
 * Avoiding Raw Pointer Issues:
 * Directly passing raw pointers to `std::shared_ptr` constructors should be avoided to prevent multiple control blocks.
 * Using `std::make_shared` is preferred.
*/
auto pw = new Widget; // pw is raw ptr

// Create control block for *pw
std::shared_ptr<Widget> spw1(pw, loggingDel);

// Create 2nd control block for *pw!
std::shared_ptr<Widget> spw2(pw, loggingDel);


/**
 * enable_shared_from_this:
 * This utility allows safe creation of `std::shared_ptr` from `this` pointers within class member functions, avoiding
 * multiple control block issues.
*/
class Widget: public std::enable_shared_from_this<Widget>
{
    public:
        void process();

    private:
        std::vector<std::shared_ptr<Widget>> processedWidgets;
};

void Widget::process()
{
    // Process the Widget

    // Add std::shared_ptr to current object to processedWidgets
    processedWidgets.emplace_back(shared_from_this());
}


/**
 * Factory Functions for Safe Initialization:
 * To ensure safe initialization with `std::shared_ptr`, classes often use factory functions that return `std::shared_ptr`
 * instances.
*/
class Widget: public std::enable_shared_from_this<Widget>
{
    public:
    // Factory function that perfect-forwards args to a private ctor
    template<typename... Ts>
    static std::shared_ptr<Widget> create(Ts&&... params);

    void process(); // as before

    private:
        std::vector<std::shared_ptr<Widget>> processedWidgets;

        // Constructors
};


/**
 * Costs and Trade-offs:
 * While `std::shared_ptr` introduces some overhead (control blocks, atomic operations), it provides automatic lifetime
 * management for shared ownership, which is often more efficient and safer than manual management.
*/

/**
 * Limitations:
 * `std::shared_ptr` is not designed for arrays and lacks array-specific operations like `operator[]`. Using it for
 * arrays is generally discouraged in favor of standard container classes.
*/


