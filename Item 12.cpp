#include <vector>
/**
 * Declare overriding functions override.
 *
 *
 * Declare overriding functions override.
 *
 * Member function reference qualifiers make it possible to treat lvalue and rvalue objects (*this) differently.
*/

/**
 * Virtual Function Overriding:
 * Overriding is a crucial aspect of C++ OOP, allowing derived class functions to be invoked through a base class
 * interface.
 *
 * Specific rules must be followed for a derived class function to override a base class function correctly, including
 * matching names, parameter types, constness, return types, exception specifications, and, in C++11, reference
 * qualifiers.
 *
 *
 * Common Errors in Overriding:
 * Small deviations in function signatures between base and derived classes can result in failed overrides, leading to
 * subtle bugs. For instance, changes in parameter types, constness, or reference qualifiers can cause a derived class
 * function to not override its base class counterpart.
 *
 *
 * Use of the override Keyword:
 * C++11 introduces the override keyword, which explicitly indicates that a derived class function is intended to
 * override a base class function.
 *
 * Declaring a function with override leads to compile-time errors if the function does not correctly override a base
 * class function, helping developers catch mistakes early.
*/
class Base
{
    public:
        virtual void mf1() const;
        virtual void mf2(int x);
        virtual void mf3() &;
        virtual void mf4() const;
};

class Derived: public Base
{
    public:
        virtual void mf1() const override;
        virtual void mf2(int x) override;
        virtual void mf3() & override;
        virtual void mf4() const override;
};


/**
 * Reference-Qualified Member Functions:
 * C++11 allows member functions to have reference qualifiers, enabling them to behave differently when the object they
 * are called on is an lvalue or an rvalue.
 *
 * This feature is useful for optimizing operations such as moving data from temporary objects.
 *
 *
 * Practical Example:
 * The author provides an example involving a Widget class with a data member function. Overloading this function with
 * reference qualifiers allows efficient handling of data both when Widget instances are lvalues and rvalues.
*/
class Widget
{
    public:
        using DataType = std::vector<double>;

        DataType& data() & { return values; }                   // For lvalue Widgets, return lvalue

        DataType data() && { return std::move(values); }        // For rvalue Widgets, return rvalue

        Widget makeWidget();

    private:
        DataType values;
};

Widget w;

auto vals1 = w.data();              // Calls lvalue overload for Widget::data, copy-constructs vals1
auto vals2 = makeWidget().data();   // Calls rvalue overload for Widget::data, move-constructs vals2



/**
 * Legacy Code and Contextual Keywords:
 * override and final are contextual keywords in C++11, meaning they are only reserved in specific contexts. This allows
 * existing code using these as identifiers to remain valid.
*/
