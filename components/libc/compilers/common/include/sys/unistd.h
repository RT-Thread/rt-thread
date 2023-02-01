/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-16     Meco Man     add usleep
 * 2021-09-11     Meco Man     move functions from dfs_posix.h to unistd.h
 */

#ifndef __SYS_UNISTD_H__
#define __SYS_UNISTD_H__

#include <stddef.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4

unsigned alarm(unsigned __secs);
ssize_t read(int fd, void *buf, size_t len);
ssize_t write(int fd, const void *buf, size_t len);
off_t lseek(int fd, off_t offset, int whence);
int pause(void);
int fsync(int fildes);
long sysconf(int __name);
int unlink(const char *pathname);
int close(int d);
int ftruncate(int fd, off_t length);
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);
int access(const char *path, int amode);
int pipe(int fildes[2]);
int isatty(int fd);
char *ttyname(int desc);
unsigned int sleep(unsigned int seconds);
int usleep(useconds_t usec);
pid_t gettid(void);
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_UNISTD_H */
