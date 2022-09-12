/*
 *	NMH's Simple C Compiler, 2012,2022
 *	setjmp.h
 */

/* should be typedef int jmp_buf[3]; */

#define _JMPBUF_SIZ	3

void	longjmp(int *env, int v);
int	setjmp(int *env);
