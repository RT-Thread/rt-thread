/*
 * File      : dfs_posix.h
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-05-27     Yi.qiu       The first version.
 * 2010-07-18     Bernard      add stat and statfs structure definitions. 
 * 2011-05-16     Yi.qiu       Change parameter name of rename, "new" is C++ key word.
 */
 
#ifndef __DFS_POSIX_H__
#define __DFS_POSIX_H__

#include <dfs_file.h>
#include <dfs_def.h>

#ifndef RT_USING_NEWLIB
#define O_RDONLY    DFS_O_RDONLY
#define O_WRONLY    DFS_O_WRONLY
#define O_RDWR      DFS_O_RDWR
#define O_ACCMODE   DFS_O_ACCMODE
#define O_CREAT     DFS_O_CREAT
#define O_EXCL      DFS_O_EXCL
#define O_TRUNC     DFS_O_TRUNC
#define O_APPEND    DFS_O_APPEND
#define O_BINARY    DFS_O_BINARY
#define O_DIRECTORY DFS_O_DIRECTORY

#define S_IFMT      DFS_S_IFMT
#define S_IFSOCK    DFS_S_IFSOCK
#define S_IFLNK     DFS_S_IFLNK 
#define S_IFREG     DFS_S_IFREG 
#define S_IFBLK     DFS_S_IFBLK 
#define S_IFDIR     DFS_S_IFDIR 
#define S_IFCHR     DFS_S_IFCHR 
#define S_IFIFO     DFS_S_IFIFO 
#define S_ISUID     DFS_S_ISUID 
#define S_ISGID     DFS_S_ISGID 
#define S_ISVTX     DFS_S_ISVTX 

#define S_ISLNK(m)  (((m) & DFS_S_IFMT) == DFS_S_IFLNK)
#define S_ISREG(m)  (((m) & DFS_S_IFMT) == DFS_S_IFREG)
#define S_ISDIR(m)  (((m) & DFS_S_IFMT) == DFS_S_IFDIR)
#define S_ISCHR(m)  (((m) & DFS_S_IFMT) == DFS_S_IFCHR)
#define S_ISBLK(m)  (((m) & DFS_S_IFMT) == DFS_S_IFBLK)
#define S_ISFIFO(m) (((m) & DFS_S_IFMT) == DFS_S_IFIFO)
#define S_ISSOCK(m) (((m) & DFS_S_IFMT) == DFS_S_IFSOCK)

#define S_IRWXU     DFS_S_IRWXU
#define S_IRUSR     DFS_S_IRUSR
#define S_IWUSR     DFS_S_IWUSR
#define S_IXUSR     DFS_S_IXUSR

#define S_IRWXG     DFS_S_IRWXG
#define S_IRGRP     DFS_S_IRGRP
#define S_IWGRP     DFS_S_IWGRP
#define S_IXGRP     DFS_S_IXGRP

#define S_IRWXO     DFS_S_IRWXO
#define S_IROTH     DFS_S_IROTH
#define S_IWOTH     DFS_S_IWOTH
#define S_IXOTH     DFS_S_IXOTH

#if defined(__CC_ARM)
#include <stdio.h>
#elif defined(_MSC_VER)
#include <stdio.h>
#else
#define SEEK_SET    DFS_SEEK_SET
#define SEEK_CUR    DFS_SEEK_CUR
#define SEEK_END    DFS_SEEK_END
#endif

typedef struct 
{
    int fd;     /* directory file */
    char buf[512];
    int num;
    int cur;
} DIR;

/* directory api*/
int mkdir(const char *path, mode_t mode);
DIR *opendir(const char *name);
struct dirent *readdir(DIR *d);
long telldir(DIR *d);
void seekdir(DIR *d, off_t offset);
void rewinddir(DIR *d);
int closedir(DIR* d);

#else
/* use newlib header file */
#include <sys/stat.h>
#endif

/* file api*/
int open(const char *file, int flags, int mode);
int close(int d);
int read(int fd, void *buf, size_t len);
int write(int fd, const void *buf, size_t len);
off_t lseek(int fd, off_t offset, int whence);
int rename(const char *from, const char *to);
int unlink(const char *pathname);
int stat(const char *file, struct stat *buf);
int fstat(int fildes, struct stat *buf);
int statfs(const char *path, struct statfs *buf);

/* directory api*/
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);

#endif

