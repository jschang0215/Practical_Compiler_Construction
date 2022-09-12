#
#	NMH's Simple C Compiler, 2011,2012
#	C runtime module
#	Version using system LIBC's system call layer
#

#	FreeBSD voodoo magic

	.section .note.ABI-tag,"a",@note
	.align	4
abitag: .long	8, 4, 1
	.string	"FreeBSD"
	.long	802000
	.data
	.p2align 2

	.data
	.globl	Cenviron
	.globl	environ		# unused, but needed by LIBC
	.globl	__progname	# unused, but needed by LIBC
environ:
__progname:
Cenviron:
	.long	0

	.text
	.globl	_start
_start:	leal	4(%esp),%esi	# argv
	movl	0(%esp),%ecx	# argc
	movl	%ecx,%eax	# environ = &argv[argc+1]
	incl	%eax
	shll	$2,%eax
	addl	%esi,%eax
	movl	%eax,Cenviron
	pushl	%ecx
	pushl	%esi
	pushl	$2		# __argc
	call	C_init
	call	Cmain
	addl	$12,%esp
	pushl	%eax
	pushl	$1
x:	call	Cexit
	xorl	%ebx,%ebx
	divl	%ebx
	jmp	x

# internal switch(expr) routine
# %esi = switch table, %eax = expr

	.globl	switch
switch:	pushl	%esi
	movl	%edx,%esi
	movl	%eax,%ebx
	cld
	lodsl
	movl	%eax,%ecx
next:	lodsl
	movl	%eax,%edx
	lodsl
	cmpl	%edx,%ebx
	jnz	no
	popl	%esi
	jmp	*%eax
no:	loop	next
	lodsl
	popl	%esi
	jmp	*%eax

# int setjmp(jmp_buf env);

	.globl	Csetjmp
Csetjmp:
	movl	8(%esp),%edx
	movl	%esp,(%edx)
	addl	$4,(%edx)
	movl	%ebp,4(%edx)
	movl	(%esp),%eax
	movl	%eax,8(%edx)
	xorl	%eax,%eax
	ret

# void longjmp(jmp_buf env, int v);

	.globl	Clongjmp
Clongjmp:
	movl	8(%esp),%eax	# v
	orl	%eax,%eax
	jne	vok
	incl	%eax
vok:	movl	12(%esp),%edx	# env
	movl	(%edx),%esp
	movl	4(%edx),%ebp
	movl	8(%edx),%edx
	jmp	*%edx

# int _exit(int rc);

	.globl	C_exit
C_exit:	pushl	8(%esp)
	call	_exit
	addl	$4,%esp
	ret

# int sbrk(int size);

	.globl	Csbrk
Csbrk:	pushl	8(%esp)
	call	sbrk
	addl	$4,%esp
	ret

# int write(int fd, char *buf, int len);

	.globl	Cwrite
Cwrite:
	pushl	8(%esp)
	pushl	16(%esp)
	pushl	24(%esp)
	call	write
	addl	$12,%esp
	ret

# int read(int fd, char *buf, int len);

	.globl	Cread
Cread:	pushl	8(%esp)
	pushl	16(%esp)
	pushl	24(%esp)
	call	read
	addl	$12,%esp
	ret

# int lseek(int fd, int pos, int how);

	.globl	Clseek
Clseek:
	pushl	8(%esp)
	movl	16(%esp),%eax
	cdq
	pushl	%edx		# off_t, high word
	pushl	%eax		# off_t, low word
	pushl	28(%esp)
	call	lseek
	addl	$16,%esp
	ret

# int creat(char *path, int perm);

	.globl	Ccreat
Ccreat:
	pushl	8(%esp)
	pushl	16(%esp)
	call	creat
	addl	$8,%esp
	ret

# int open(char *path, int flags);

	.globl	Copen
Copen:	pushl	8(%esp)
	pushl	16(%esp)
	call	open
	addl	$8,%esp
	ret

# int close(int fd);

	.globl	Cclose
Cclose:
	pushl	8(%esp)
	call	close
	addl	$4,%esp
	ret

# int unlink(char *path);

	.globl	Cunlink
Cunlink:
	pushl	8(%esp)
	call	unlink
	addl	$4,%esp
	ret

# int rename(char *old, char *new);

	.globl	Crename
Crename:
	pushl	8(%esp)
	pushl	16(%esp)
	call	rename
	addl	$8,%esp
	ret

# int fork(void);

	.globl	Cfork
Cfork:	call	fork
	ret

# int wait(int *rc);

	.globl	Cwait
Cwait:	pushl	8(%esp)
	call	wait
	addl	$4,%esp
	ret

# int execve(char *path, char *argv[], char *envp[]);

	.globl	Cexecve
Cexecve:
	pushl	8(%esp)
	pushl	16(%esp)
	pushl	24(%esp)
	call	execve
	addl	$12,%esp
	ret

# int _time(void);

	.globl	C_time
C_time:	push	$0
	call	time
	addl	$4,%esp
	ret

# int raise(int sig);

	.globl	Craise
Craise:
	call	getpid
	push	8(%esp)
	push	%eax
	call	kill
	addl	$8,%esp
	ret

# int signal(int sig, int (*fn)());

	.globl	Csignal
Csignal:
	pushl	8(%esp)
	pushl	16(%esp)
	call	signal
	addl	$8,%esp
	ret
