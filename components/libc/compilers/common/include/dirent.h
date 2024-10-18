/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __DIRENT_H__
#define __DIRENT_H__

#include <rtdef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
* dirent.h - format of directory entries
 * Ref: http://www.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
 */

/* File types */
#define FT_REGULAR      0   /* regular file */
#define FT_SOCKET       1   /* socket file  */
#define FT_DIRECTORY    2   /* directory    */
#define FT_USER         3   /* user defined */
#define FT_DEVICE       4   /* device */
#define FT_SYMLINK      5   /* symbol link */
#define FT_NONLOCK      6   /* non lock */

#define DT_UNKNOWN      0x00
#define DT_FIFO         0x01
#define DT_CHR          0x02
#define DT_DIR          0x04
#define DT_BLK          0x06
#define DT_REG          0x08
#define DT_LNK          0x0a
#define DT_SOCK         0x0c
#define DT_SYMLINK      DT_LNK

#ifndef HAVE_DIR_STRUCTURE
#define HAVE_DIR_STRUCTURE
typedef struct
{
    int fd;                         /* directory file */
    char buf[512];
    int num;
    int cur;
}DIR;
#endif

#ifndef HAVE_DIRENT_STRUCTURE
#define HAVE_DIRENT_STRUCTURE

#define DIRENT_NAME_MAX    256

struct dirent
{
    rt_uint8_t  d_type;             /* The type of the file */
    rt_uint8_t  d_namlen;           /* The length of the not including the terminating null file name */
    rt_uint16_t d_reclen;           /* length of this record */
    char d_name[DIRENT_NAME_MAX];   /* The null-terminated file name */
};
#endif

#ifdef RT_USING_MUSLLIBC
typedef uint64_t ino_t;
#endif
struct libc_dirent {
    ino_t d_ino;
    off_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[DIRENT_NAME_MAX];
};

int            closedir(DIR *);
DIR           *opendir(const char *);
struct dirent *readdir(DIR *);
int            readdir_r(DIR *, struct dirent *, struct dirent **);
void           rewinddir(DIR *);
void           seekdir(DIR *, long);
long           telldir(DIR *);

#ifdef __cplusplus
}
#endif

#endif
