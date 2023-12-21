#include <memory>
#include <regex>
#include <string>
#include <vector>
/**
 * Consider emplacement instead of insertion.
 *
 *
 * In principle, emplacement functions should sometimes be more efficient than their insertion counterparts, and they
 * should never be less efficient.
 *
 * In practice, they’re most likely to be faster when
 * (1) the value being added is constructed into the container, not assigned;
 * (2) the argument type(s) passed differ from the type held by the container; and
 * (3) the container won’t reject the value being added due to it being a duplicate.
 *
 * Emplacement functions may perform type conversions that would be rejected by insertion functions.
*/

/**
 * Insertion vs. Emplacement:
 * While logically one might pass an object of the same type as the container (e.g., `std::string` for a
 * `std::vector<std::string>`), often different types are passed (like a string literal).
 *
 * Insertion functions (like `push_back`) create a temporary object for type mismatches, leading to inefficiency.
 * Emplacement functions (like `emplace_back`) construct the object directly in the container, avoiding temporaries.
*/
// Container of std::string
std::vector<std::string> vs;

// Create temp. std::string and pass it to push_back
vs.push_back(std::string("xyzzy"));

// Construct std::string inside vs directly from "xyzzy"
vs.emplace_back("xyzzy");


/**
 * Understanding Emplacement Functions:
 * Emplacement functions use perfect forwarding and can be more efficient than insertion functions as they
 * construct objects in place.
 *
 * They're advantageous when argument types differ from the container's type, and when adding values where no object
 * exists yet, especially in node-based containers.
*/

/**
 * Performance Considerations:
 * In scenarios where a value is assigned to an existing position in a container, emplacement may not offer
 * significant advantages, as both insertion and emplacement might use assignment.
 *
 * Additionally, in containers disallowing duplicates, emplacement functions might not always be more efficient.
*/

/**
 * Resource Management and Exception Safety:
 * With resource-managing objects (like `std::shared_ptr` or `std::unique_ptr`), using emplacement can
 * lead to resource leaks during exceptions, as the creation of the resource-managing object is deferred.
 *
 * It's generally safer to create these objects before passing them to the container.
*/
// Create Widget and have spw manage it
std::shared_ptr<Widget> spw(new Widget, killWidget);

ptrs.push_back(std::move(spw)); // add spw as rvalue

ptrs.emplace_back(std::move(spw));


/**
 * Interaction with Explicit Constructors:
 * Emplacement functions can use explicit constructors, leading to unexpected behavior. For example, passing
 * a null pointer to `emplace_back` in a container of `std::regex` compiles, but `push_back` would not.
 *
 * This behavior highlights the need for careful argument checking with emplacement functions.
*/
std::vector<std::regex> regexes;

// Add nullptr to container of reg?
regexes.emplace_back(nullptr);

std::regex r = nullptr;             // Error! won't compile
regexes.push_back(nullptr);         // Error! won't compile

regexes.emplace_back(nullptr);      // Compiles. Direct init permits use of explicit std::regex ctor taking a pointer


/**
 * Summary:
 * Emplacement functions in C++ offer a more efficient way to construct objects inside containers but require
 * careful consideration of types, container characteristics, and exception safety concerns. They are
 * particularly beneficial for in-place construction and when argument types differ from the container's type.
 * However, in some cases, insertion functions might be safer or more appropriate.
*/
