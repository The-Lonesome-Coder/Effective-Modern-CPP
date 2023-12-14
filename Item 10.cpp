#include <cstdint>
#include <string>
#include <tuple>
/**
 * Prefer scoped enums to unscoped enums.
 *
 *
 * C++98-style enums are now known as unscoped enums.
 *
 * Enumerators of scoped enums are visible only within the enum. They convert to other types only with a cast.
 *
 * Both scoped and unscoped enums support specification of the underlying type. The default underlying type for scoped
 * enums is int. Unscoped enums have no default underlying type.
 *
 * Scoped enums may always be forward-declared. Unscoped enums may be forward-declared only if their declaration
 * specifies an underlying type.
*/

/**
 * Scope and Name Pollution:
 * Unscoped enums have enumerator names that belong to the scope containing the enum, leading to potential name conflicts.
 *
 * Scoped enums (enum class) keep their enumerators scoped to the enum itself, preventing name pollution and conflicts in
 * the surrounding scope.
*/
enum Color { black, white, red };           // black, white, red are in same scope as Color
auto white = false;                         // Error! white already declared in this scope

enum class Color { black, white, red };     // black, white, red are scoped to Color
auto white = false;                         // Fine
Color c = white;                            // Error! no enumerator named "white" is in this scope
Color c = Color::white;                     // Fine
auto c = Color::white;                      // Fine


/**
 * Strong Typing:
 * Unscoped enums implicitly convert to integral types, allowing for potentially nonsensical or unintended comparisons
 * and operations.
 *
 * Scoped enums do not implicitly convert to other types, thus avoiding such issues. Explicit casting is required for
 * conversions, making intentions clearer and errors less likely.
 *
 *
 * Forward Declaration:
 * Scoped enums can be forward-declared, enhancing flexibility and reducing compilation dependencies. This is not
 * possible with traditional unscoped enums in C++98.
 *
 * C++11 allows specifying the underlying type for unscoped enums, enabling forward declarations for them too.
*/
enum Status
{
    good = 0,
    failed = 1,
    incomplete = 100,
    corrupt = 200,
    indeterminate = 0xFFFFFFFF
};

enum class Status: std::uint32_t
{
    good = 0,
    failed = 1,
    incomplete = 100,
    corrupt = 200,
    audited = 500,
    indeterminate = 0xFFFFFFFF
};

/**
 * Tuple Indexing with Enums:
 * The implicit conversion of unscoped enums to std::size_t is useful when working with std::tuple, as it allows for more
 * readable indexing.
 *
 * Scoped enums require more verbose syntax or the creation of a template function (toUType) to achieve the same effect,
 * but they offer benefits like avoiding namespace pollution.
*/
enum class UserInfoFields { uiName, uiEmail, uiReputation };

using UserInfo = std::tuple<std::string, std::string, std::size_t>;

UserInfo uInfo;

auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo);


/**
 * Template Function for Enum Conversion (toUType):
 * The toUType template function converts enum values to their underlying type at compile time, allowing for their use
 * with templates like std::get for tuples.
 *
 * This function can be simplified in C++14 using std::underlying_type_t and auto return types.
*/
// C++14
template<typename E>
constexpr std::underlying_type_t<E> toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

// Or
template<typename E>
constexpr auto toUType(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

auto val = std::get<toUType(UserInfoFields::uiEmail)>(uInfo);