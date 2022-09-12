# Lexical Analysis

## Theory

* Token consists of individual objects (e.g. ++, continue) and classes of objects (e.g. `INTLIT`, `STRLIT`)
* *Scanner* finds next token in input stream, isolate it, and return integer value representing that token
  1. Skip over *noise characters* (e.g. whitespace, line separators)
  2. Examine non-noise character
     - *Token classes* are identified by first characters (e.g. `"` token matches string class and `scanstr()` is called)
     - *Unambiguous token* is returned (e.g. parentheses, comma)
     - *Ambiguous token* is scanned by *longest match scanning*
       - Scan each character from the front (e.g. `>>=` is scanned as `>`, `>>`, `>>=`)

## Scanner Code

* `scan.c` Contains scanner
* `next()` Extracts next character from input stream
  1. Clear *put-back queue* and return that character
  2. *Macro expansion*, returns next character from `Macp[]` until `Mp` is nonzero
  3. Fetch character from current input file
* `hexchar()` Return value of hexadecimal literals
  * cf. `chrpos("0123456789abcdef", tolower(c))` returns value of `c`
* `scanch()` Extracts next character of a string or character literals
  * Decodes escape sequence when character is backslash
    * `\"` is decoded to `""|256` to distinguish end of input while preserving its 8-bit char value
    * Octal number is the byte of corresponding numerical value
* `scanint(int c)` Scans decimal, octal, and hexadecimal integers and returns their value
  * Textual representation is stored in `Text[]`
  * Determine radix by the prefix
  * Sign recognition will be done in *parser*
* `scanstr(char *buf)` Scans string literal
  * `Value` is length of the string
* `scanident(int c, char *buf, int lim)` Scans identifier
  * Return length of identifier

* `skip()` Skips over white space and comments
  * Detects end of comment by using a single-element queue `p` to check current and previous input characters
  * Invokes *preprocessor* when it finds `#` character after newline
    * Preprocessor commands are parsed and processed before `skip()` returns
* `keyword(char *s)` Checks whether `s` is SubC keyword
* `macro(char *name)` Checks whether `name` exists and refers to a macro
  * Start expanding macro when `name` is macro
* `scanpp()` Implements the *scanner*
  - Check *reject queue* and when queue is not empty, clears it
  - *Character literals* are classified as `INTLIT` since SubC handles char as int
* `scan()` Principal interface of SubC scanner
* `scanraw()` Does not expeand macros and ignores `#ifdef` context
* `reject()` Puts current token and its attributes to *reject queue*