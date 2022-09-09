# Phase of Compilation

* Compilation: Translating a formal language *S* to formal *O* language by program *C*

## Lexical Analysis

* Transforms the source program to small units called *tokens*
* Sometimes referred to as *scanner*
* Splits program into manageable parts and categorizes them

## Parsing

* Also called as *syntax analyzer*
* Compares the token stream to syntax of the language
* When parsing succeeds, it transforms tokens to *abstract syntax tree*
* Parser also builds *symbol tables* to store names of identifiers and meta data (e.g. addresses, values, types)

## Semantic Analysis

* Look up properties of identifiers
* Perform *type checking* and *context checking*
  * Context checking: Check whether statement appears in proper context (e.g. `break` should be in loop)

## Optimization

* Not covered much in book

## Code Generator

* *Synthesizes* instruction for the target machine
* Also called as *emitter*

# Sub C

* We define subset of C for our compiler
* Only `int` and `char` datatype
* No more than 2 levels of indirection (i.e. only 1D array)
* No `typedef`, `structs`, `unions`, `goto`
* Runtime Libraries
  * *crt0*: Comprises interface to the C library of the compiler which provides interface to system calls (written in assembly)
  * *libc*: Standard C library (we use libscc)