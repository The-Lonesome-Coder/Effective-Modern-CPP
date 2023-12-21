/**
 * Assume that move operations are not present, not cheap, and not used.
 *
 *
 * Assume that move operations are not present, not cheap, and not used.
 *
 * In code with known types or support for move semantics, there is no need for assumptions.
*/

/**
 * Move semantics, introduced in C++11, is celebrated for its ability to optimize performance by replacing costly copy
 * operations with more efficient moves. This feature is particularly evident when recompiling C++98 code with a
 * C++11-compliant compiler, often resulting in noticeably faster software. The core idea is that compilers are now
 * required, under certain conditions, to substitute copy operations with moves.
 *
 *
 * However, it's important to maintain realistic expectations about move semantics. Not all types support move semantics,
 * especially in existing code bases that haven't been updated for C++11. Even if a type doesn't support move operations,
 * C++11 may automatically generate them, but only if the class has no custom copy operations, move operations, or
 * destructors. Also, types with components that prohibit moving will not benefit from auto-generated move operations.
 *
 *
 * Even when move operations are supported, their efficiency varies. For example, all standard C++11 containers support
 * moving, but it's not always cheap. The efficiency of moving depends on the container type and its contents. For
 * instance, moving elements in a std::array is linear-time since each element must be individually moved, contrasting
 * with the notion that moving containers is as simple as copying pointers. On the other hand, std::string often employs
 * the small string optimization (SSO), where small strings are stored internally within the std::string object, making
 * moves no faster than copies.
 *
 *
 * Another consideration is that in certain situations, even if a type supports efficient move operations, compilers
 * might still opt for copy operations. This is particularly true when move operations are not declared noexcept, as
 * some container operations in the Standard Library require no-throw guarantees to maintain strong exception safety.
 *
 *
 * In summary, while C++11's move semantics can significantly improve performance by replacing copies with moves, this
 * benefit is not universal. It's contingent on the type's support for move operations, the efficiency of these
 * operations, and the context in which they are used. In scenarios where move operations are not present, not cheap, or
 * not usable, developers must remain cautious about object copying, just as in pre-C++11 code. Understanding the
 * specifics of how types are implemented and used is crucial to fully leverage the potential performance gains offered
 * by move semantics.
*/