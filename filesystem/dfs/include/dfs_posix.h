/*
+------------------------------------------------------------------------------
| Project   : Device Filesystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_posix.h, the filesystem related defines of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       Notes
| 2009-05-27     Yi.qiu         The first version.
+------------------------------------------------------------------------------
*/
#ifndef __DFS_POSIX_H__
#define __DFS_POSIX_H__

#include <dfs_raw.h>

#define O_RDONLY	DFS_O_RDONLY
#define O_WRONLY 	DFS_O_WRONLY
#define O_RDWR		DFS_O_RDWR
#define O_ACCMODE	DFS_O_ACCMODE
#define O_CREAT		DFS_O_CREAT
#define O_EXCL		DFS_O_EXCL
#define O_TRUNC		DFS_O_TRUNC
#define O_APPEND	DFS_O_APPEND
#define O_DIRECTORY DFS_O_DIRECTORY

#define S_IFMT 		DFS_S_IFMT
#define S_IFSOCK		DFS_S_IFSOCK
#define S_IFLNK		DFS_S_IFLNK	
#define S_IFREG		DFS_S_IFREG	
#define S_IFBLK		DFS_S_IFBLK	
#define S_IFDIR		DFS_S_IFDIR 
#define S_IFCHR		DFS_S_IFCHR 
#define S_IFIFO		DFS_S_IFIFO 
#define S_ISUID		DFS_S_ISUID 
#define S_ISGID		DFS_S_ISGID 
#define S_ISVTX		DFS_S_ISVTX 

#define S_ISLNK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFLNK)
#define S_ISREG(m)	(((m) & DFS_S_IFMT) == DFS_S_IFREG)
#define S_ISDIR(m)	(((m) & DFS_S_IFMT) == DFS_S_IFDIR)
#define S_ISCHR(m)	(((m) & DFS_S_IFMT) == DFS_S_IFCHR)
#define S_ISBLK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFBLK)
#define S_ISFIFO(m)	(((m) & DFS_S_IFMT) == DFS_S_IFIFO)
#define S_ISSOCK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFSOCK)

#define S_IRWXU		DFS_S_IRWXU
#define S_IRUSR		DFS_S_IRUSR
#define S_IWUSR		DFS_S_IWUSR
#define S_IXUSR		DFS_S_IXUSR

#define S_IRWXG		DFS_S_IRWXG
#define S_IRGRP		DFS_S_IRGRP
#define S_IWGRP		DFS_S_IWGRP
#define S_IXGRP		DFS_S_IXGRP

#define S_IRWXO		DFS_S_IRWXO
#define S_IROTH		DFS_S_IROTH
#define S_IWOTH		DFS_S_IWOTH
#define S_IXOTH		DFS_S_IXOTH

#define SEEK_SET	DFS_SEEK_SET
#define SEEK_CUR	DFS_SEEK_CUR
#define SEEK_END	DFS_SEEK_END

typedef struct 
{
	int fd;		/* directory file */
	char buf[512];
	int num;
	int cur;
	rt_sem_t *sem;
} DIR;

/* file api*/
int open(const char *file, int flags, int mode);
int close(int d);
int read(int fd, char *buf, int len);
int write(int fd, char *buf, int len);
int lseek(int fd, int offset, int dir);
int rename(const char* old, const char* new );
int unlink(const char *pathname);
int stat(const char *file, struct dfs_stat *buf);

/* directory api*/
int mkdir (const char *path, rt_uint16_t mode);
int rmdir(const char *path);
DIR* opendir(const char* name);
struct dfs_dirent* readdir(DIR *d);
rt_off_t telldir(DIR *d);
void seekdir(DIR *d, rt_off_t offset);
void rewinddir(DIR *d);
int closedir(DIR* d);
int chdir(const char *path);
char* getcwd(char *buf, rt_size_t size);

#endif
