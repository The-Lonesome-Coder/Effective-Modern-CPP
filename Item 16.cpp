#include <atomic>
#include <mutex>
#include <vector>
/**
 * Make const member functions thread safe.
*/

/**
 * Polynomial Class Example:
 * A class Polynomial has a const member function roots to compute roots, which are cached to avoid recomputation.
 *
 * The caching involves modifying members rootVals and rootsAreValid, which are declared mutable to allow modification
 * within a const function.
*/
class Polynomial
{
    public:
        using RootsType = std::vector<double>;

        RootsType roots() const
        {
            // If cache not valid compute roots, store them in rootVals
            if (!rootsAreValid)
            {
                /* ... */
                rootsAreValid = true;
            }

            return rootVals;
        }

    private:
        // See Item 7 for info on initializers
        mutable bool rootsAreValid { false };
        mutable RootsType rootVals { };
};


/**
 * Thread Safety Issue:
 * If two threads simultaneously call the roots function, it leads to a data race due to concurrent read and write
 * operations, resulting in undefined behavior.
 *
 * Although roots is a const function (implying it's a read operation), it's not inherently thread-safe due to internal
 * state modifications.
*/
Polynomial p;

auto rootsOfP = p.roots();                  // Thread 1
auto valsGivingZero = p.roots();            // Thread 2


/**
 * Solving Thread Safety with Mutex:
 * A mutex (std::mutex) is introduced to synchronize access to the shared state in the Polynomial class.
 *
 * The mutex is declared mutable to allow locking and unlocking within the const member function.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Impact on Object Copyability:
 * Introducing a mutex (a move-only type) to a class makes the class move-only and not copyable.
*/
class Polynomial
{
    public:
        using RootsType = std::vector<double>;

        RootsType roots() const
        {
            std::lock_guard<std::mutex> g(m);       // Lock mutex

            // If cache not valid compute roots, store them in rootVals
            if (!rootsAreValid)
            {
                /* ... */
                rootsAreValid = true;
            }

            return rootVals;
        }                                           // Unlock mutex

    private:
        mutable std::mutex m;

        // See Item 7 for info on initializers
        mutable bool rootsAreValid { false };
        mutable RootsType rootVals { };
};


/**
 * Alternative: std::atomic for Simple Counters:
 * For simpler cases like counting function calls, std::atomic variables can be more efficient than mutexes.
 *
 * However, std::atomic variables are also move-only, affecting the copyability of the class.
*/
// 2D point
class Point
{
    public:
        // See Item 14 for noexcept atomic increment
        double distanceFromOrigin() const noexcept
        {
            ++callCount;

            return std::sqrt((x * x) + (y * y));
        }

    private:
        mutable std::atomic<unsigned> callCount { 0 };
        double x, y;
};


/**
 * Caution with std::atomic:
 * Using std::atomic for complex synchronization, like caching in the Widget class example, can lead to incorrect
 * behavior if not used carefully.
 *
 * For synchronizing multiple related variables or memory locations, a mutex is a more appropriate choice.
*/
int expensiveComputation1();
int expensiveComputation2();

class Widget
{
    public:

        int magicValue() const
        {
            if (cacheValid)
            {
                return cachedValue;
            }
            else
            {
                auto val1 = expensiveComputation1();
                auto val2 = expensiveComputation2();
                cachedValue = val1 + val2;              // Uh oh, part 1
                cacheValid = true;                      // Uh oh, part 2

                return cachedValue;
            }
        }

    private:
        mutable std::atomic<bool> cacheValid{ false };
        mutable std::atomic<int> cachedValue;
};


/**
 * General Advice:
 * For single variables or memory locations, std::atomic may suffice.
 *
 * For multiple interdependent variables, use a mutex for thread safety.
 *
 * It's important to ensure const member functions are thread-safe, especially in multi-threaded environments.
*/
class Widget
{
    public:
        int magicValue() const
        {
            std::lock_guard<std::mutex> guard(m);          // lock mutdx
            if (cacheValid)
            {
                return cachedValue;
            }
            else
            {
                auto val1 = expensiveComputation1();
                auto val2 = expensiveComputation2();
                cachedValue = val1 + val2;
                cacheValid = true;

                return cachedValue;
            }
        }                                              // unlock mutex

    private:
        mutable std::mutex m;

        mutable int cachedValue;                       // no longer atomic
        mutable bool cacheValid{ false };              // no longer atomic
};
