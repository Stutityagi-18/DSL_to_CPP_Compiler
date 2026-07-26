# DSL to C++ Compiler

A custom **Domain-Specific Language (DSL) to C++ Compiler** built using **Flex, Bison, C++, and CMake**. The compiler parses a Solidity-inspired DSL, constructs an **Abstract Syntax Tree (AST)**, and generates equivalent C++ source code.

---

## Features

- Lexical Analysis using **Flex**
- Syntax Analysis using **Bison**
- AST (Abstract Syntax Tree) Construction
- Code Generation from DSL to C++
- Supports:
  - Contracts
  - Functions
  - Parameters
  - Variable Declarations
  - Assignments
  - Arithmetic Expressions
  - Relational Expressions
  - Logical Expressions
  - Unary Operators
  - If-Else Statements
  - Return Statements
  - Data Types:
    - `uint`
    - `int`
    - `bool`
    - `address`

---

## Tech Stack

- C++
- Flex
- Bison
- CMake
- Ninja
- MSYS2 (Windows)

---

## Project Structure

```
DSL_Compiler/
│
├── examples/
│   ├── sample1.dsl
│   ├── sample1.cpp
│   ├── sample2.dsl
│   ├── sample2.cpp
│   ├── sample3.dsl
│   └── sample3.cpp
│
├── generator/
│   ├── generator.cpp
│   └── generator.h
│
├── src/
│   ├── ast.h
│   └── main.cpp
│
├── parser.y
├── scanner.l
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

## Build Instructions

### Clone Repository

```bash
git clone https://github.com/Stutityagi-18/DSL_to_CPP_Compiler.git
cd DSL_to_CPP_Compiler
```

### Create Build Directory

```bash
mkdir build
cd build
```

### Generate Build Files

```bash
cmake -G Ninja ..
```

### Build

```bash
ninja
```

---

## Running the Compiler

```bash
./dsl_to_cpp.exe ../examples/sample1.dsl
```

The compiler generates the corresponding C++ source file in the same directory as the input DSL file.

Example:

```
sample1.dsl
      ↓
sample1.cpp
```
## Compiler Workflow

```
DSL Source Code
        │
        ▼
     Flex Scanner
        │
        ▼
    Bison Parser
        │
        ▼
        AST
        │
        ▼
 Code Generator
        │
        ▼
   Generated C++
```

---
