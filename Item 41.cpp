#include <string>
#include <vector>
/**
 * Consider pass by value for copyable parameters that are cheap to move and always copied.
 *
 *
 * For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly as efficient as pass by
 * reference, it’s easier to implement, and it can generate less object code.
 *
 * Copying parameters via construction may be significantly more expensive than copying them via assignment.
 *
 * Pass by value is subject to the slicing problem, so it’s typically inappropriate for base class parameter types.
*/

/**
 * Copy and Move Semantics in Class Methods:
 * In methods like `addName`, where parameters are intended to be copied, using separate methods for lvalue and
 * rvalue references is effective but leads to code duplication. Each version handles the parameter differently,
 * either copying or moving it into a container.
*/
class Widget
{
    public:
        // Take lvalue; copy it
        void addName(const std::string& newName)
        {
            names.push_back(newName);
        }

        // Take rvalue; move it
        void addName(std::string&& newName)
        {
            names.push_back(std::move(newName));
        }

    private:
        std::vector<std::string> names;
};


/**
 * Universal Reference Approach:
 * A template-based method using a universal reference (`T&&`) reduces code duplication but adds complexity.
 * This method can accommodate both lvalues and rvalues, executing the appropriate copy or move operations.
*/
class Widget
{
    public:
        // Take lvalues and rvalues; copy lvalues, move rvalues;
        template<typename T>
        void addName(T&& newName)
        {
            names.push_back(std::forward<T>(newName));
        };

    private:
        std::vector<std::string> names;
};


/**
 * Pass-by-Value Alternative:
 * Passing the parameter by value and then moving it within the function is a simpler approach. It requires
 * only one function definition and leverages C++11's move semantics for efficiency. However, it incurs an
 * extra move operation for both lvalue and rvalue arguments.
*/
class Widget
{
    public:
        // Take lvalue or rvalue; move it
        void addName(std::string newName)
        {
            names.push_back(std::move(newName));
        }

    private:
        std::vector<std::string> names;
};


/**
 * Efficiency Considerations:
 * For lvalue arguments, pass-by-value results in a copy followed by a move, while for rvalue arguments, it
 * results in two move operations. This method is generally efficient for types that are cheap to move, such
 * as `std::string` or `std::vector`, but may not be ideal for types where moving is expensive or not
 * implemented.
*/

/**
 * Limitations and Caveats:
 * Pass-by-value is advisable only for copyable parameters that are always copied and cheap to move. In
 * scenarios using assignment-based copying, additional costs like unnecessary memory allocations may arise.
 * Additionally, pass-by-value is susceptible to the slicing problem with base and derived class objects.
*/

/**
 * Comparing Approaches:
 * The text compares three methods for the `addName` function in a `Widget` class: overloading for lvalue and
 * rvalue, using universal references, and pass-by-value. Each has trade-offs in terms of efficiency, code
 * complexity, and potential error handling.
*/

/**
 * Conclusion:
 * While pass-by-value in C++11 can be efficient for functions that always copy their parameters and where
 * the parameters are cheap to move, it's important to consider the specific use case and object characteristics.
 * The traditional advice of avoiding pass-by-value for user-defined types still holds, but C++11's move
 * semantics offer new options and considerations.
*/
