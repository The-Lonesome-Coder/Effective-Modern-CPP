/**
 * Use decltype on auto&& parameters to std::forward them.
*/

/**
 * Generic Lambdas in C++14:
 * These lambdas are essentially templates where the `operator()` in the lambda's closure class is a template.
 * This allows for more flexibility and generalization in the use of lambdas.
*/
auto f = [](auto x){ return func(normalize(x)); };

class SomeCompilerGeneratedClassName
{
    public:
        template<typename T>
        auto operator()(T x) const
        {
            return func(normalize(x));
        }

        // other closure class functionality
};


/**
 * Perfect Forwarding in Lambdas:
 * A critical point addressed is how to perfect-forward arguments within a generic lambda to other functions.
 * The issue arises because generic lambdas do not have an explicit type parameter like typical templates.
*/
// What type to pass to std::forward ?
auto f = [](auto&& x)
{
    return func(normalize(std::forward<???>(x)));
};


/**
 * Using `decltype` for Perfect Forwarding:
 * The solution involves using `decltype` on the lambda's parameter to deduce the correct type for perfect
 * forwarding. This is necessary because generic lambdas always receive arguments as lvalues, even if an rvalue
 * is passed to them. To forward arguments correctly to another function (like `normalize` in the example), the
 * lambda needs to perfect-forward using `std::forward`.
*/

/**
 * Type Deduction with `decltype`:
 * When an lvalue is passed to the lambda, `decltype(param)` yields an lvalue reference, conforming to the
 * conventional usage with `std::forward`. Interestingly, when an rvalue is passed, `decltype(param)` yields an
 * rvalue reference. While this is unconventional (normally a non-reference type is expected), it's shown that
 * instantiating `std::forward` with an rvalue reference type yields the same result as instantiating it with a
 * non-reference type.
*/
// In namespace std
template<typename T>
T&& forward(remove_reference_t<T>& param)
{
    return static_cast<T&&>(param);
}

// Instantiation of std::forward when T is Widget
Widget&& forward(Widget& param)
{
    return static_cast<Widget&&>(param);
}

// Instantiation of std::forward when T is Widget&& (before reference-collapsing)
Widget&& && forward(Widget& param)
{
    return static_cast<Widget&& &&>(param);
}

// Instantiation of std::forward when T is Widget&& (aefore reference-collapsing)
Widget&& forward(Widget& param)
{
    return static_cast<Widget&&>(param);
}


/**
 * Final Lambda Implementation:
 * The final version of the lambda perfectly forwards a single parameter using `std::forward<decltype(param)>
 * (param)`. The text then extends this to variadic parameters, allowing the lambda to perfectly forward any
 * number of parameters to another function.
*/
auto f = [](auto&& param)
{
    return func(normalize(std::forward<decltype(param)>(param)));
};

auto f = [](auto&&... params)
{
    return func(normalize(std::forward<decltype(params)>(params) ...));
};


