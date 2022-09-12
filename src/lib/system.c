/*
 *	NMH's Simple C Compiler, 2011,2012
 *	system()
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int system(char *cmd) {
	int	pid, rc;
	char	*argv[4];

	if ((pid = fork()) == -1) {
		return -1;
	}
	else if (pid) {
		wait(&rc);
		return cmd? rc: !rc;
	}
	else {
		argv[0] = "/bin/sh";
		argv[1] = "-c";
		argv[2] = cmd? cmd: "exit";
		argv[3] = NULL;
		execve(argv[0], argv, environ);
		exit(cmd? -1: 0);
	}
}
