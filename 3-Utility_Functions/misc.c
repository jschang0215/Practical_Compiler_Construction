/*
 *	NMH's Simple C Compiler, 2011,2012
 *	Miscellanea
 */

#include "defs.h"
#include "data.h"
#include "decl.h"

// Returns offset of the first occurrence of c in s (-1 when does not occur)
int chrpos(char *s, int c)
{
	char *p;
	p = strchr(s, c); // strchr returns pointer to the first occurence of c in s
	return p ? p - s : -1;
}

// Copies name of identifier fro, s to name
void copyname(char *name, char *s)
{
	strncpy(name, s, NAMELEN); // Maximum NAMELEN of characters to be copied
	name[NAMELEN] = 0;
}

// Creates new file name with name of fie where the suffix of the file is changed to sfx
// e.g. foo.c -> foo.o
char *newfilename(char *file, int sfx)
{
	char *ofile;
	ofile = strdup(file); // srdup returns pointer to new string with duplicate of string s
	ofile[strlen(ofile) - 1] = sfx;
	return ofile;
}

// Matches token t, textual description of token expected is stored to what
void match(int t, char *what)
{
	if (Token == t)
		Token = scan();
	else
		error("%s expected", what);
}

// Match tokens
void lparen(void)
{
	match(LPAREN, "'('");
}

void rparen(void)
{
	match(RPAREN, "')'");
}

void lbrace(void)
{
	match(LBRACE, "'{'");
}

void rbrack(void)
{
	match(RBRACK, "']'");
}

void semi(void)
{
	match(SEMI, "';'");
}

void colon(void)
{
	match(COLON, "':'");
}

void ident(void)
{
	match(IDENT, "identifier");
}

// Check for premature EOF inside curly braces
int eofcheck(void)
{
	if (XEOF == Token)
	{
		error("missing '}'", NULL);
		return 1;
	}
	return 0;
}

// Check if p is int type
int inttype(int p)
{
	return PINT == p || PCHAR == p;
}
