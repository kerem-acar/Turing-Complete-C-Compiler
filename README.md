# Turing Complete C Compiler

## Overview
This is a compiler for a subset of C such that it is Turing-complete, meaning it can calculate any logically possible problem or algorithm. It was written in C and compiles to 64-bit assembly. The compiler is broken into three components: the lexer, recursive-descent parser, and the code generator.

## Usage
To use the compiler, paste the C code you want to compile into the input.c file that is in the src folder. Then, run the compile.bat script. The executable will be in the bin folder, and you can view the corresponding assembly in the result.s file within the codegen folder.

## Supported Features
- Types: int
- Unary Operators: !, -, ~, 
- Binary Operators: +, -, *, /
- Relational Operators: ==, !=, <, <=, >, >=
- Logical Operators: &&, ||
- Assignment Operators: =
- Ternary Operator: ?
- If/Else If/Else Statements
- Return Statements
- For Loops
- While Loops
- Do-While Loops
- Local Variables
- Functions: only main

## Motivation
The primary purpose of this project was to learn about compilers and gain foundational experience in compiler development. I hope this project can serve as a reference point to others starting their journey in compilers and provide a high-level understanding of how they work under the hood to those unfamiliar with them.