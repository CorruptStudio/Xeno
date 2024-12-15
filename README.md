# Xeno Overview

## Core Features:
1. **Language Capabilities**:
   - Functions, loops, conditionals, classes, interfaces, enums, and generics.
   - Support for basic data types and collections such as arrays, dictionaries, and lists.
   - Function overloading, default parameters, and named parameters.
   - Lambdas using `->` or `=>` notation.
   - Support for try-catch-finally-throw blocks.

2. **Syntax**:
   - Human-readable syntax similar to C/C++.
   - Use of curly braces for defining classes, functions, and block structures.
   - Imports structured as `import <System>` for system libraries and `import "localFile"` for local scripts.

3. **String Handling**:
   - Interpolated strings marked with `"$"` or other distinct activators.
   - Multi-line strings with triple quotes (e.g., `"""`) for better readability.
   - Raw strings with a prefix (e.g., `r"string"`) to avoid escape sequences.
   - Standard escape sequences similar to those in C/C++.

4. **Debugging**:
   - Built-in debugging calls like `log()`, `logWarn()`, `logError()`, and `logAssert()` that output to the console.
   - The ability for developers to add hooks for custom debugging functionality.

5. **Imports and Modules**:
   - Import system that supports versioning without wildcard use for strict dependency management.
   - Modules imported via `import <Module>` for global bindings and `import "LocalFile"` for user scripts.

## Developer Flexibility:
- **Game Integration**:
  - Scripts interact with the game engine through developer-created bindings.
  - Modders have control over event handling and can create listeners through their libraries.
- **Entry Points**:
  - Predefined entry points specified in the `mod.info` file, similar to how Node.js works.
- **Compilation**:
  - Currently, Xeno does not compile to bytecode but may consider runtime compilation if needed for performance.
- **Sandboxing**:
  - Scripts are run in a secure, sandboxed environment to prevent unauthorized access to the system.

## Syntax Overview Example:
```xmod
import <System>
import "localScript.xmod"

class GameMod
{
    public:
        function greet() : void
        {
            log("Hello, Xeno!");
        }

        function calculateValue(integer x) : integer
        {
            if (x < 0)
            {
                throw new Exception("x must be non-negative.");
            }
            return x * 2;
        }

    private:
        integer secretValue = 42;
}
```

## Key Design Goals:
- **Intuitive and Readable**: Syntax inspired by C/C++ for clarity, using curly braces for structure and familiar conventions for defining classes and functions.
- **Flexibility for Modders**: Features like generics, overloading, and easy-to-use data structures ensure power and extensibility.
- **Safe and Secure**: Scripts run in a controlled sandbox, with no embedded execution allowed to mitigate potential security risks.
- **Debugging Built-In**: Debug tools such as `log()`, `logWarn()`, `logError()`, and `logAssert()` are integrated by default, simplifying testing and development.
- **Modular and Versioned Imports**: A strict, versioned import system to manage dependencies safely without wildcard use.
