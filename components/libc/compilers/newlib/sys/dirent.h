/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RTT_DIRENT_H__
#define __RTT_DIRENT_H__

#include <rtthread.h>

/*
* dirent.h - format of directory entries
 * Ref: http://www.opengroup.org/onlinepubs/009695399/basedefs/dirent.h.html
 */

/* File types */
#define FT_REGULAR		0	/* regular file */
#define FT_SOCKET		1	/* socket file  */
#define FT_DIRECTORY	2	/* directory    */
#define FT_USER			3	/* user defined */

#define DT_UNKNOWN		0x00
#define DT_REG			0x01
#define DT_DIR			0x02

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAVE_DIR_STRUCTURE
typedef struct 
{
	int fd;							/* directory file */
	char buf[512];
	int num;
	int cur;
} DIR;
#endif

#ifndef HAVE_DIRENT_STRUCTURE
struct dirent
{
	rt_uint8_t  d_type;				/* The type of the file */
	rt_uint8_t  d_namlen;			/* The length of the not including the terminating null file name */
	rt_uint16_t d_reclen;			/* length of this record */
	char d_name[256];				/* The null-terminated file name */
};
#endif

int            closedir(DIR *);
DIR           *opendir(const char *);
struct dirent *readdir(DIR *);
int            readdir_r(DIR *, struct dirent *, struct dirent **);
void           rewinddir(DIR *);
void           seekdir(DIR *, long int);
long           telldir(DIR *);

#ifdef __cplusplus
}
#endif

#endif
