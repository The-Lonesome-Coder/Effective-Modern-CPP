#include <ios>
#include <string>
/**
 * Prefer deleted functions to private undefined ones.
 *
 *
 * Prefer deleted functions to private undefined ones.
 *
 * Any function may be deleted, including non-member functions and template instantiations.
*/

/**
 * C++98 Approach:
 * In C++98, to prevent the use of certain functions (like copy constructors and copy assignment operators), they were
 * declared private and not defined. This method stops external code from calling these functions and causes linking
 * errors if they are used internally.
 *
 * An example provided is the basic_ios class from the C++ Standard Library, which has its copy constructor and copy
 * assignment operator declared as private to prevent copying of stream objects.
 *
 *
 * C++11 Approach – Deleted Functions:
 * C++11 introduces a better approach with deleted functions (= delete). This explicitly marks functions as unusable.
 *
 * Deleted functions provide a clearer intention and are checked during compilation rather than link-time, preventing
 * usage even in member and friend functions.
 *
 * By convention, deleted functions are declared public, improving error messages when clients attempt to use them.
 *
 *
 * Advantages of Deleted Functions:
 * Deleted functions can be used to prevent implicit conversions that might be nonsensical or unintended. For example,
 * overloading isLucky for different types and deleting certain overloads can stop conversions from undesired types.
 *
 * Deleted functions can also be used in templates to disable certain instantiations, like disabling processPointer for
 * void* or char*.
 *
 *
 * Limitations of C++98 Approach:
 * The C++98 method of using private undeclared functions is limited because it doesn’t work outside classes and has
 * restrictions inside classes. For instance, it's not possible to give a member function template specialization a
 * different access level from the main template.
 *
 *
 * Deleted Functions in Class Templates:
 * Deleted functions do not suffer from the same limitations as the C++98 approach and can be declared outside the class
 * at namespace scope, still being part of the class.
*/
template <class charT, class traits = std::char_traits<charT>>
class basic_ios : public ios_base
{
    private:
        basic_ios(const basic_ios& );                   // Not defined
        basic_ios& operator = (const basic_ios&);       // Not defined
};

template <class charT, class traits = std::char_traits<charT>>
class basic_ios : public ios_base
{
    public:
        basic_ios(const basic_ios& ) = delete;
        basic_ios& operator = (const basic_ios&) = delete;
};


bool isLucky(int number);

bool isLucky(int number);               // Original function
bool isLucky(char) = delete;            // Reject char
bool isLucky(bool) = delete;            // Reject bool
bool isLucky(double) = delete;          // Reject double and float


template<typename T>
void processPointer(T* ptr);

template<>
void processPointer<void>(void*) = delete;

template<>
void processPointer<const void>(const void*) = delete;

template<>
void processPointer<char>(char*) = delete;

template<>
void processPointer<const char>(const char*) = delete;
