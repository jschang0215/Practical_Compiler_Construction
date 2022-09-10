/*
 *	NMH's Simple C Compiler, 2011,2012
 *	Global variables
 */

#ifndef extern_
 #define extern_ extern
#endif

extern_ FILE	*Infile;                // Current input file
extern_ FILE	*Outfile;               // Output file which object code to be writter
extern_ int	Token;                      // Token most recently scanned by scanner
extern_ char	Text[TEXTLEN+1];        // Textual form of Toekn
extern_ int	Value;                      // Value of Toekn

// Error handling
extern_ int	Line;                       // Current input line number
extern_ int	Errors;                     // Error counter
extern_ int	Syntoken;                   // Next scanner synchronization token

extern_ int	Putback;                    // Character that is putback to input stream
extern_ int	Rejected;                   // Toekns putback to charaters
extern_ int	Rejval;                     // Value of Toekns putback to charaters
extern_ char	Rejtext[TEXTLEN+1];     // Text of Toekns putback to charaters
extern_ char	*File;                  // Current input filename
extern_ char	*Basefile;              // Name of principal file being compiled

// Stack structures for implementing macro expansion
extern_ char	*Macp[MAXNMAC];         // Pointer to macro text
extern_ int	Macc[MAXNMAC];              // First character in macro input stream
extern_ int	Mp;                         // Stack pointer
extern_ int	Expandmac;                  // Set to 0 to turn off macro expansion

extern_ int	Ifdefstk[MAXIFDEF], Isp;    // Stack structures for #ifdef stacks
extern_ int	Inclev;                     // Number of nested #includes
extern_ int	Textseg;

// symbol tabel structure
extern_ char	*Names[NSYMBOLS];
extern_ char	Prims[NSYMBOLS];
extern_ char	Types[NSYMBOLS];
extern_ char	Stcls[NSYMBOLS];
extern_ int	Sizes[NSYMBOLS];
extern_ int	Vals[NSYMBOLS];
extern_ char	*Mtext[NSYMBOLS];
extern_ int	Globs;
extern_ int	Locs;

extern_ int	Thisfn;                     // Pints to symbol table entry of the function

// Name list
extern_ char	Nlist[POOLSIZE];        // Store identifier name
extern_ int	Nbot;                       // Point free space between segments
extern_ int	Ntop;                       // Points to the name of most recently inserted symbol

extern_ int	Breakstk[MAXBREAK], Bsp;    // Stack structures for break stacks
extern_ int	Contstk[MAXBREAK], Csp;     // Stack structures for continue stacks
extern_ int	Retlab;

// Intialize local variables
extern_ int	LIaddr[MAXLOCINIT];
extern_ int	LIval[MAXLOCINIT];
extern_ int	Nli;                        // Number of local initializers

// Files used to store names of source files for linker
extern_ char	*Files[MAXFILES];
extern_ int	Nf;

extern_ int	O_verbose;
extern_ int	O_componly;
extern_ int	O_asmonly;
extern_ int	O_testonly;
extern_ char	*O_outfile;
extern_ int	O_debug;
