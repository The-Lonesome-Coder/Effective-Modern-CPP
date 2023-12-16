/**
 * Understand special member function generation.
 *
 *
 * The special member functions are those compilers may generate on their own: default constructor, destructor, copy
 * operations, and move operations.
 *
 * Move operations are generated only for classes lacking explicitly declared move operations, copy operations, and a
 * destructor.
 *
 * The copy constructor is generated only for classes lacking an explicitly declared copy constructor, and it’s deleted
 * if a move operation is declared. The copy assignment operator is generated only for classes lacking an explicitly
 * declared copy assignment operator, and it’s deleted if a move operation is declared. Generation of the copy operations
 * in classes with an explicitly declared destructor is deprecated.
 *
 * Member function templates never suppress generation of special member functions.
*/

/**
 * C++98 Special Member Functions:
 * Four special member functions: default constructor, destructor, copy constructor, and copy assignment operator.
 *
 * Generated only if needed and not explicitly declared.
 *
 * Default constructor is generated only if no constructors are declared.
 *
 * Generated functions are public and inline.
 *
 * Destructor becomes virtual if it's in a derived class with a virtual destructor.
*/


/**
 * C++11 Changes:
 * Introduction of two new special member functions: move constructor and move assignment operator.
 *
 * Move operations perform "member-wise moves" on the class's non-static data members and base classes.
 *
 * Move-enabled types are moved; others are copied.
 *
 * Move operations are not generated if any copy operations or a destructor are declared.
 *
 * Declaring either a move constructor or move assignment operator prevents the automatic generation of the other.
*/
class Widget
{
    public:
        Widget(Widget&& rhs);                   // Move constructor
        Widget& operator=(Widget&& rhs);        // Move assignment operator
};


/**
 * Interdependence of Copy and Move Operations:
 * In C++11, declaring a copy operation (constructor or assignment) suppresses generation of move operations.
 *
 * Declaring a move operation disables the copy operations (they are deleted).
 *
 * C++11 doesn't generate move operations for classes with a user-declared destructor.
*/


/**
 * Rule of Three in C++11:
 * If a class declares a copy constructor, copy assignment operator, or destructor, it should declare all three.
 *
 * This is because resource management in one copy operation likely requires similar handling in the other and in the
 * destructor.
 *
 * In C++11, a user-declared destructor prevents generation of move operations.
*/
class Widget
{
    public:
        // User-declared dtor
        ~Widget();

        // Default copy ctor
        Widget(const Widget&) = default;                    // Behavior is OK

        // Default copy assign
        Widget& operator=(const Widget&) = default;         // Behavior is OK
};


/**
 * Explicitly Defaulting Functions:
 * C++11 allows explicitly defaulting functions using = default.
 *
 * Useful for classes needing a virtual destructor but otherwise default behavior for copy/move operations.
 *
 * Prevents subtle bugs and makes intentions clearer.
 *
 * ---------------------------------------------------------------------------------------------------------------------
 *
 * Default Constructor and Destructor in C++11:
 * Rules for the default constructor and destructor remain mostly unchanged from C++98.
 *
 * The destructor is noexcept by default.
*/
class Base
{
    public:
        virtual ~Base() = default;              // Make dtor virtual

        Base(Base&&) = default;                 // Support moving
        Base& operator=(Base&&) = default;

        Base(const Base&) = default;            // Support copying
        Base& operator=(const Base&) = default;
};


/**
 * Member Function Templates and Special Member Functions:
 * The presence of member function templates doesn't prevent the generation of special member functions.
 *
 * This can have important consequences, as demonstrated in a later item.
*/
class Widget
{
    template<typename T>                        // Construct Widget from anything
    Widget(const T& rhs);

    template<typename T>                        // Assign Widget from anything
    Widget& operator=(const T& rhs);
};