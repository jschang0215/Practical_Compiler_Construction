/*
 *	NMH's Simple C Compiler, 2011,2012,2022
 *	unistd.h
 */

int	 close(int fd);
int	 creat(char *path, int mode);
int	 execve(char *path, char *argv[], char *envp[]);
void	 exit(int rc);
int	 fork(void);
int	 lseek(int fd, int pos, int how);
int	 open(char *path, int flags);
int	 read(int fd, void *buf, int len);
int	 rename(char *old, char *new);
void	*sbrk(int size);
int	 _time(void);
int	 unlink(char *path);
int	 wait(int *rc);
int	 write(int fd, void *buf, int len);
