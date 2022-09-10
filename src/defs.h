/*
 *	NMH's Simple C Compiler, 2011,2012,2022
 *	Definitions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* define this on 64-bit systems */
#define W64

/* define when linking against host's LIBC */
/* #define HOSTLIB */

#define PREFIX		'C' // Character prepended to all symbols
#define LPREFIX		'L' // Prefix for labels

#ifndef SCCDIR
 #define SCCDIR		"."
#endif

#define ASCMD		"as -32 -o %s %s" // Command to assemble output of compiler

#ifdef W64
 #define LDCMD		"ld -m elf_i386_fbsd -o %s %s/lib/crt0.o" // Invoke system linker
 #define SYSLIBC	"/usr/lib32/libc.a"
#else
 #define LDCMD		"ld -o %s %s/lib/crt0.o"
 #define SYSLIBC	"/usr/lib/libc.a"
#endif

#define SCCLIBC		"%s/lib/libscc.a"

#ifndef HOSTLIB
 #undef SYSLIBC
 #define SYSLIBC	""
#endif

#define INTSIZE		4 		// Bytes of int
#define PTRSIZE		INTSIZE // SubC compiler handle pointer size equal to int size
#define CHARSIZE	1 		// Bytes of char

#define TEXTLEN		512		// Maximum lenght of each token
#define NAMELEN		16		// Maximum length of relevant characters

#define MAXFILES	32		// Maximum number of C files passed to C compiler

#define MAXIFDEF	16		// Maximum number of Nested #ifdefs
#define MAXNMAC		32		// Maximum number of macro
#define MAXCASE		256		// Maximum number of cases per switch
#define MAXBREAK	16		// Maximum number of nested break/continue
#define MAXLOCINIT	32		// Maximum number of initializer
#define MAXFNARGS	32		// Maximum number of function arguments

#define NSYMBOLS	1024	// Maximum number of global symbols
#define POOLSIZE	8192	// Maximum number of identifiers

/* types */
#define TVARIABLE	1 		// Metatype for variable
#define TARRAY		2 		// Metatype for array
#define TFUNCTION	3 		// Metatype for function
#define TCONSTANT	4 		// Metatype for constants
#define TMACRO		5 		// Metatype for macros

/* primitive types */
#define PCHAR	1 			// Metatype for char
#define PINT	2 			// Metatype for int 
#define CHARPTR	3 			// Metatype for char*
#define INTPTR	4 			// Metatype for int*
#define CHARPP	5 			// Metatype for char**
#define INTPP	6 			// Metatype for int**
#define PVOID	7 			// Metatype for void
#define VOIDPTR	8 			// Metatype for void*
#define VOIDPP	9 			// Metatype for void**
#define FUNPTR	10 			// Metatype for int(*)()

/* storage classes */
#define CPUBLIC	1 			// Metatype for global indentifiers
#define CEXTERN	2 			// Metatype for extern
#define CSTATIC	3 			// Metatype for static identifiers in global context
#define CLSTATC	4 			// Metatype for static identifiers in local contextr
#define CAUTO	5 			// Metatype for automatically allocated

/* lvalue structure */
#define LVSYM	0
#define LVPRIM	1
#define LV		2

/* debug options */
#define D_LSYM	1
#define D_GSYM	2
#define D_STAT	4

enum {
	/* !!! The order of the following symbols must match
	   !!! the order of corresponding symbols in prec.h */
	SLASH, STAR, MOD, PLUS, MINUS, LSHIFT, RSHIFT,
	GREATER, GTEQ, LESS, LTEQ, EQUAL, NOTEQ, AMPER,
	CARET, PIPE, LOGAND, LOGOR,

	__ARGC, ASAND, ASXOR, ASLSHIFT, ASMINUS, ASMOD, ASOR,
	ASPLUS, ASRSHIFT, ASDIV, ASMUL, ASSIGN, BREAK, CASE,
	CHAR, COLON, COMMA, CONTINUE, DECR, DEFAULT, DO, ELLIPSIS,
	ELSE, ENUM, EXTERN, FOR, IDENT, IF, INCR, INT, INTLIT,
	LBRACE, LBRACK, LPAREN, NOT, QMARK, RBRACE, RBRACK,
	RETURN, RPAREN, SEMI, SIZEOF, STATIC, STRLIT, SWITCH,
	TILDE, VOID, WHILE, XEOF, XMARK,

	P_INCLUDE, P_DEFINE, P_ENDIF, P_ELSE, P_ELSENOT, P_IFDEF,
	P_IFNDEF, P_UNDEF
};
