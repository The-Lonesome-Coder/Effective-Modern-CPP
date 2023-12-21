#include <memory>
/**
 * Use init capture to move objects into closures.
 *
 *
 * Use C++14’s init capture to move objects into closures.
 *
 * In C++11, emulate init capture via hand-written classes or std::bind.

*/

/**
 * C++14's Solution:
 * C++14 introduces 'init capture', a flexible mechanism that allows objects to be moved into closures. This new feature
 * overcomes the limitations of C++11 by enabling the movement of objects into closures through a more generalized notion
 * of capture. Init capture allows specifying a data member's name in the closure class and an expression to initialize
 * that data member. The example provided shows moving a std::unique_ptr<Widget> into a closure.
*/
class Widget
{
    public:
        bool isValidated() const;
        bool isProcessed() const;
        bool isArchived() const;
};

auto pw = std::make_unique<Widget>();

// init data mbr in closure with std::move(pw)
auto func = [pw = std::move(pw)]
{
    return pw->isValidated() && pw->isArchived();
};

// init data mbr in closure with result of call to make_unique
auto func = [pw = std::make_unique<Widget>()]
{
    return pw->isValidated() && pw->isArchived();
};

/**
 * C++11 Workarounds:
 * For environments still using C++11, where init capture is not available, the text provides workarounds for moving
 * objects into closures. One way is to manually create a class that encapsulates the desired behavior, then instantiate
 * and use this class instead of a lambda. Another method is to use std::bind to emulate move capture. This involves
 * moving the object into a function object created by std::bind and then giving the lambda a reference to this object
 * (Item 34).
*/
// "is validated and archived"
class IsValAndArch
{
    public:
        using DataType = std::unique_ptr<Widget>;

        explicit IsValAndArch(DataType&& ptr)
            : pw(std::move(ptr)) {}

        bool operator()() const { return pw->isValidated() && pw->isArchived(); }

    private:
        DataType pw;
};

auto func = IsValAndArch(std::make_unique<Widget>());


/**
 * The key points for C++11 are:
 * Direct move construction into a closure is not possible, but moving into a bind object is.
 *
 * Emulating move capture involves moving the object into a bind object and passing it to the lambda by reference.
 *
 * The lifetime of the bind object aligns with the closure, ensuring the moved object remains valid while the closure
 * exists.
*/