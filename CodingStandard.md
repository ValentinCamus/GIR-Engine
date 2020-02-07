# Conding Standard

Code conventions are important to programmers for a number of reasons:
* 80% of the lifetime cost of a piece of software goes to maintenance.

* Code conventions improve the readability of the software.

* Allows to understand new code more quickly and thoroughly.

## Class Organization

Classes should be organized with the reader in mind rather than the writer. Since most readers will be using the public interface of the class, that should be declared first, followed by the class's private implementation.

* Prefer to use private variables with getter and setter instead of public variables.

* Getters and setters should have a consistent name with the variable.

* Use `explicit` for all one-arguments constructors.

* If the class has virtual methods then the destructor is virtual (do not abuse function overloading).

* Use  `override`  when overriding a virtual method.

* Declare : public functions (constructors first), private functions, public variables, private variables.

Example:
```cpp
/// @MyClass: [Description]
class MyClass : public Base, public Interface
{
public:
	/// Default constructor.
	/// @param value: ...
	MyClass(float value = 0.0f) : m_value(value) {}
	
	/// Destructor.
	~MyClass() override;
	
	/// ...
	void DoSomething();
	
	/// @getter: m_value.
	inline float GetValue() const { return m_value; }
	
	/// @setter: m_value.
	inline void SetValue(float value) { m_value = value; }
	
private:
	/// ...
	void DoSomethingElse();

private:
	/// ...
	float m_value;
}
```

## Struct Organization

Structs should  only contain variables and the constructors /destructors.

Example:
```cpp
struct MyStruct
{
	bool isValid = true;
	float value0 = 0.0f;
	unsigned value1 = 10;
    int value2 = -1;
}
```

## Naming Conventions

* Class: FortranCase.
* Variable: camelCase.
* Function: FortranCase.
* Namespace: FortranCase.
* File name: FortranCase (execpt third party librairies).
* Class's variables are prefixed by 'm_'.
* Global variables are prefixed by 'g_'.
* Enums are prefixed by 'E'.

Variable, method, and class names should be clear, unambiguous, and descriptive. The greater the scope of the name, the greater the importance of a good, descriptive name. Avoid over-abbreviation.

All functions that return a bool should ask a true/false question, such as `IsVisible()` or `ShouldClearBuffer()`.

Though not required, we encourage you to prefix function parameter names with "out" if they are passed by reference, and the function is expected to write to that value. This makes it obvious that the value passed in this argument will be replaced by the function.

### Const Correctness

Const is documentation as much as it is a compiler directive, so all code should strive to be const-correct.

This includes:

-   Passing function arguments by const pointer or reference if those arguments are not intended to be modified by the function,
    
-   Flagging methods as const if they do not modify the object,
    
-   and using const iteration over containers if the loop isn't intended to modify the container.

## The 'auto' Keyword

You shouldn't use `auto` in C++ code, although a few exceptions are listed below. Always be explicit about the type you're initializing. This means that the type must be plainly visible to the reader.

When is it acceptable to use  `auto`?

-   When you need to bind a lambda to a variable, as lambda types are not expressible in code.
    
-   For iterator variables, but only where the iterator's type is verbose and would impair readability.
    
-   In template code, where the type of an expression cannot easily be discerned. This is an advanced case.

If you're sure you are using `auto` in an acceptable way, always remember to correctly use const, & or * just like you would with the type name. With `auto`, this will coerce the inferred type to be what you want.

## Strongly - Typed Enums

Enum classes should always be used as a replacement for old-style namespaced enums. For example:

```cpp
// Old enum
namespace EThing
{
    enum Type
    {
        Thing1,
        Thing2
    };
}

// New enum
enum class EThing : uint8
{
    Thing1,
    Thing2
}
```

## Code Formatting

### Braces

Braces should be put on a new line.  For example:

```cpp
namespace NamespaceName
{
	class MyClass
	{
	public:
		inline void DoSomething()
		{
			if (condition)
			{
				// ...
			}
			else
			{
				// ...
			}
		}
	}
}
```

Avoid ifs / for / while one-liners, 

### Tabs and Indenting

Here are the standards for indenting your code.

-   Indent code by execution block.
    
-   Use tabs, not spaces, for whitespace at the beginning of a line. Set your tab size to 4 characters.

### Switch Statements

Except for empty cases (multiple cases having identical code), switch case statements should explicitly label that a case falls through to the next case. Either include a break, or include a falls-through comment in each case. Other code control-transfer commands (return, continue, and so on) are fine as well.

Always have a default case, and include a break just in case someone adds a new case after the default.

```cpp
switch (condition)
{
    case 1:
        ...
        // falls through

    case 2:
        ...
        break;
    case 3:
        ...
        return;
    case 4:
    case 5:
        ...
        break;
    default:
        break;
}
```

## General Style Issues

* All headers should protect against multiple includes with the `#pragma once` directive. 

* Split up large functions into logical sub-functions. One area of compilers' optimizations is the elimination of common subexpressions. The bigger your functions are, the more work the compiler has to do to identity them. This leads to greatly inflated build times.
  
* Don't use too many inline functions, because they force rebuilds even in files which don't use them. Inline functions should only be used for trivial accessors and when profiling shows there is a benefit to doing so.

* Pointers and references should only have one space, which is to the right of the pointer or reference. This makes it easy to quickly use **Find in Files** for all pointers or references to a certain type.

* Use prefix increments (`++i` and not `i++`).

* Line length should be kept at 80 (soft limit) and not exceed 120 (hard limit).