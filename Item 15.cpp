#include <array>
/**
 * Use constexpr whenever possible.
*/

/**
 * Concept of constexpr:
 * constexpr indicates that a value is constant and known during compilation.
 *
 * It applies differently to objects and functions.
*/

/**
 * constexpr Objects:
 * They are constant and their values are determined at compile time.
 *
 * Can be used in contexts where C++ requires integral constant expressions, like array sizes, template arguments, etc.
 *
 * All constexpr objects are const, but not all const objects are constexpr.
*/
constexpr auto arraySize2 = 10;         // Fine, 10 is a compile-time constant
std::array<int, arraySize2> data2;      // Fine, arraySize2 is constexpr


/**
 * constexpr Functions:
 * Produce compile-time constants when called with compile-time constants.
 *
 * Act like normal functions and compute results at runtime when called with runtime values.
 *
 * Can be used in a wider range of contexts compared to non-constexpr functions.
 *
 * -------------------------------------------------------------------------------------------------------------
 *
 * Usage Examples:
 * Demonstrated with a function pow to compute power during compile-time for std::array size specification.
 *
 * Usage in a Point class where constructors and member functions are constexpr.
 *
 * -------------------------------------------------------------------------------------------------------------
 *
 * C++11 vs. C++14 Differences:
 * C++11 constexpr functions are limited to a single return statement.
 *
 * C++14 relaxes these restrictions, allowing loops and multiple statements.
 *
 * In C++14, constexpr functions can modify objects and have void return types.
*/
// pow's a constexpr func that never throws
constexpr int pow(int base, int exp) noexcept
{
    auto result = 1;

    for (int i = 0; i < exp; ++i)
    {
        result *= base;
    }

    return result;
}

constexpr auto num = 5;

std::array<int, pow(3, num)> results;   // Results has 3^num elements


class Point
{
    public:
        constexpr Point(double xVal = 0, double yVal = 0) noexcept
            : x(xVal), y(yVal) {}

        constexpr double xValue() const noexcept { return x; }
        constexpr double yValue() const noexcept { return y; }

        constexpr void setX(double newX) noexcept { x = newX; }     // C++14
        constexpr void setY(double newY) noexcept { y = newY; }     // C++14

    private:
        double x, y;
};


constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
{
    // Call constexpr member funcs
    return { (p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2 };
}

constexpr Point p1(9.4, 27.7);          // Fine, "runs" constexpr ctor during compilation
constexpr Point p2(28.8, 5.3);          // Also fine

// Init constexpr object w/result of constexpr function
constexpr auto mid = midpoint(p1, p2);

// Return reflection of p with respect to the origin (C++14)
constexpr Point reflection(const Point& p) noexcept
{
    Point result;                       // Create non-const Point

    result.setX(-p.xValue());           // Set its x and y values
    result.setY(-p.yValue());

    return result;                      // Return copy of it
}

constexpr Point p1(9.4, 27.7);          // As above
constexpr Point p2(28.8, 5.3);

constexpr auto mid = midpoint(p1, p2);

constexpr auto reflectedMid = reflection(mid);     // ReflectedMid's value is (-19.1 -16.5) and known during compilation


/**
 * Implications:
 * constexpr allows computations traditionally done at runtime to be moved to compile time.
 *
 * This can lead to performance improvements, though it might increase compilation time.
*/

/** Interface and Long-Term Commitment:
 * constexpr is part of an object's or function's interface.
 *
 * Declaring something constexpr implies a commitment to maintaining its constant expression status, as changing it later
 * can break client code.
*/