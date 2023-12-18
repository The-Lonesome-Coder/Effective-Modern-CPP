#include <memory>
/**
 * Use std::unique_ptr for exclusive-ownership resource management.
 *
 *
 * std::unique_ptr is a small, fast, move-only smart pointer for managing resources with exclusive-ownership semantics.
 *
 * By default, resource destruction takes place via delete, but custom deleters can be specified. Stateful deleters and
 * function pointers as deleters increase the size of std::unique_ptr objects.
 *
 * Converting a std::unique_ptr to a std::shared_ptr is easy.
*/

/**
 * Default Choice for Smart Pointers:
 * std::unique_ptr should be the go-to smart pointer due to its size and performance similarities with raw pointers. It's
 * suitable for situations demanding efficient memory and processing usage.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Exclusive Ownership Semantics:
 * A std::unique_ptr exclusively owns the object it points to. Transferring a std::unique_ptr moves ownership and sets
 * the source pointer to null. Copying is not permitted to avoid dual ownership of the same resource.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Move-Only Type:
 * std::unique_ptr is a move-only type. Upon destruction, it deletes the object it points to, typically using delete.
*/

class Investment { };
class Stock: public Investment { };
class Bond: public Investment { };
class RealEstate: public Investment { };

/*
 * Factory Function Return Type:
 * A common use case for std::unique_ptr is as a return type for factory functions in class hierarchies. It ensures that
 * the caller gains exclusive ownership of the returned object, which gets automatically destroyed when the
 * std::unique_ptr goes out of scope.
*/
// Return std::unique_ptr to an object created from the given args
template<typename... Ts>
std::unique_ptr<Investment> makeInvestment(Ts&&... params);

// pInvestment is of type std::unique_ptr<Investment>
Investment arguments;
auto pInvestment = makeInvestment( arguments );


/**
 * Custom Deleters:
 * std::unique_ptr can be configured with custom deleters for special cleanup needs. These custom deleters can be lambda
 * expressions or function objects.
*/
// Custom deleter (a lambda expression)
auto delInvmt = [](Investment* pInvestment)
{
    makeLogEntry(pInvestment);
    delete pInvestment;
};


/**
 * Handling Derived Class Objects:
 * When deleting derived class objects through a base class pointer (Investment* in the example), it’s crucial for the
 * base class (Investment) to have a virtual destructor.
*/
// Revised
template<typename... Ts>
auto makeInvestment(Ts&&... params)
{
    // ptr to be returned, this is now inside make-Investment
    auto delInvmt = [](Investment* pInvestment)
    {
        makeLogEntry(pInvestment);

        delete pInvestment;
    };

    pInv(nullptr, delInvmt);

    if ( /* a Stock object should be created */ )
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( /* a Bond object should be created */ )
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( /* a RealEstate object should be created */ )
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}


/**
 * Size Implications with Custom Deleters:
 * The size of a std::unique_ptr can increase with custom deleters, especially if the deleter is a function pointer or
 * has extensive state. Stateless lambda expressions as deleters do not increase the size.
*/
// Custom deleter as stateless lambda
auto delInvmt1 = [](Investment* pInvestment)
{
    makeLogEntry(pInvestment);

    delete pInvestment;
};

// Return type has size of Investment*
template<typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt1)> makeInvestment(Ts&&... args);

// custom deleter as function
void delInvmt2(Investment* pInvestment)
{
    makeLogEntry(pInvestment);

    delete pInvestment;
}

// Return type has size of Investment* plus at least size of function pointer!
template<typename... Ts>
std::unique_ptr<Investment, void (*)(Investment*)> makeInvestment(Ts&&... params);


/**
 * Pimpl Idiom and Array Support:
 * std::unique_ptr is also used in the Pimpl Idiom and comes in two forms: one for individual objects and one for arrays.
 * The API differs based on the form used.
*/


/**
 * Conversion to std::shared_ptr:
 * std::unique_ptr can easily and efficiently convert to std::shared_ptr, allowing flexibility in ownership semantics
 * based on the user's needs.
*/
// Converts std::unique_ptr to std::shared_ptr
std::shared_ptr<Investment> sp = makeInvestment( arguments );
