#include <memory>
/**
 * When using Pimpl Idiom, define special member functions in the implementation file.
 *
 *
 * The Pimpl Idiom decreases build times by reducing compilation dependencies between class clients and class
 * implementations.
 *
 * For std::unique_ptr pImpl pointers, declare special member functions in the class header, but implement them in the
 * implementation file. Do this even if the default function implementations are acceptable.
 *
 * The above advice applies to std::unique_ptr, but not to std::shared_ptr.
*/

/**
 * Pimpl Idiom Overview:
 * The Pimpl ("pointer to implementation") Idiom involves replacing a class's data members with a
 * pointer to an implementation class. This reduces build dependencies, as changes in the
 * implementation class don't require recompiling classes that use the primary class.
 */

/**
 * C++98 Implementation:
 * In C++98, the Pimpl Idiom used raw pointers to an incomplete type (forward declaration) for the
 * implementation, with allocation and deallocation handled in the class's constructor and destructor.
 */
class Widget
{
    public:
        Widget();
        ~Widget();

    private:
        // Declare implementation struct and pointer to it
        struct Impl;
        Impl *pImpl;
};


/**
 * Modern Implementation with Smart Pointers:
 * In modern C++, `std::unique_ptr` is used instead of raw pointers. This eliminates manual memory
 * management and the need for a custom destructor in the primary class.
 */

/**
 * Example Implementation:
 * The example demonstrates how to implement the Pimpl Idiom using `std::unique_ptr`. The
 * implementation class is defined in the source file (.cpp), while the header file (.h) contains a
 * forward declaration and a `std::unique_ptr` to the implementation.
 */

/**
 * Compiling Issues with Incomplete Types:
 * The implementation with `std::unique_ptr` can lead to compilation errors due to incomplete types.
 * To resolve this, the destructor (and move operations, if needed) of the primary class should be
 * declared in the header and defined in the source file after the implementation class is fully defined.
 */
// In "gadget.h"
class Gadget { };

// In "widget.h"
class Widget
{
public:
    Widget();
    ~Widget();

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;           // Use smart pointer instead of raw pointer
};


// In "Widget.cpp"
#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>
struct Widget::Impl
{
    std::string name;
    std::vector<double> data;

    Gadget g1, g2, g3;
};


// Per Item 21, create std::unique_ptr via std::make_unique
Widget::Widget()
    : pImpl(std::make_unique<Impl>()) { }

// ~Widget definition
Widget::~Widget() { }


/**
 * Copy and Move Operations:
 * For classes using the Pimpl Idiom, copy and move operations should be implemented explicitly. The
 * default operations provided by the compiler might not perform deep copies or correct moves of the
 * underlying implementation object.
 */
class Gadget { };

// In "widget.h"
class Widget
{
public:
    Widget();
    ~Widget();

    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs);

    Widget(Widget&& rhs);
    Widget& operator=(Widget&& rhs);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;           // Use smart pointer instead of raw pointer
};

// in "Widget.cpp"
#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>
struct Widget::Impl
{
    std::string name;
    std::vector<double> data;

    Gadget g1, g2, g3;
};

// Per Item 21, create std::unique_ptr via std::make_unique
Widget::Widget()
    : pImpl(std::make_unique<Impl>()) { }

// ~Widget definition
Widget::~Widget() = default;

Widget::Widget(Widget&& rhs) = default;

Widget& Widget::operator = (Widget&& rhs) = default;


Widget::Widget(const Widget& rhs)
    : pImpl(std::make_unique<Impl>(*rhs.pImpl)) { }


Widget& Widget::operator = (const Widget& rhs)
{
    *pImpl = *rhs.pImpl;

    return *this;
}


/**
 * Comparison with `std::shared_ptr`:
 * If `std::shared_ptr` is used instead of `std::unique_ptr`, compiler-generated move operations and
 * destructors work correctly even with incomplete types, but `std::unique_ptr` is more suitable for
 * the Pimpl Idiom due to exclusive ownership semantics.
 */
// In "widget.h"
class Widget .
{
    public:
        Widget();

        // No declarations for dtor or move operations

    private:
        struct Impl;

        // std::shared_ptr instead of std::unique_ptr
        std::shared_ptr<Impl> pImpl;
};