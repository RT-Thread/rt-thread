/*
+------------------------------------------------------------------------------
|        Device FileSystem
+------------------------------------------------------------------------------
| Copyright 2004, 2005  www.fayfayspace.org.
| All rights reserved.
|------------------------------------------------------------------------------
| File      : dfs_def.h, the definitions of Device FileSystem
|------------------------------------------------------------------------------
| Chang Logs:
| Date           Author       notes
| 2004-10-01     ffxz         The first version.
| 2004-10-14     ffxz         Clean up the code.
| 2005-01-22     ffxz		  Clean up the code, port to MinGW
+------------------------------------------------------------------------------
*/

#ifndef __DFS_DEF_H__
#define __DFS_DEF_H__

#include <rtthread.h>
#include <dfs_config.h>

#if defined(RT_USING_NEWLIB) || defined (RT_USING_MINILIBC)
#include <string.h>
#endif

#ifndef __D_FS__
#define __D_FS__
#endif

/* Device error codes */
#define DFS_STATUS_OK			0		/* no error */
#define DFS_STATUS_ENOENT		2		/* No such file or directory */
#define DFS_STATUS_EIO		 	5		/* I/O error */
#define DFS_STATUS_ENXIO		6		/* No such device or address */
#define DFS_STATUS_EBADF		9		/* Bad file number */
#define DFS_STATUS_EAGIAN		11		/* Try again */
#define DFS_STATUS_ENOMEM		12		/* no memory */
#define DFS_STATUS_EBUSY		16		/* Device or resource busy */
#define DFS_STATUS_EEXIST		17		/* File exists */
#define DFS_STATUS_EXDEV		18		/* Cross-device link */
#define DFS_STATUS_ENODEV		19		/* No such device */
#define DFS_STATUS_ENOTDIR		20		/* Not a directory */
#define DFS_STATUS_EISDIR		21		/* Is a directory */
#define DFS_STATUS_EINVAL		22		/* Invalid argument */
#define DFS_STATUS_ENOSPC		28		/* No space left on device */
#define DFS_STATUS_EROFS		30		/* Read-only file system */
#define DFS_STATUS_ENOSYS		38		/* Function not implemented */
#define DFS_STATUS_ENOTEMPTY	39		/* Directory not empty */
#define DFS_STATUS_EMMOUNT		128		/* Filesystem table full */

/* Operation flags */
#define DFS_O_RDONLY		0000000
#define DFS_O_WRONLY		0000001
#define DFS_O_RDWR			0000002
#define DFS_O_ACCMODE		0000003
#define DFS_O_CREAT			0000100
#define DFS_O_EXCL			0000200
#define DFS_O_TRUNC			0001000
#define DFS_O_APPEND		0002000
#define DFS_O_DIRECTORY		0200000

/* File flags */
#define DFS_F_OPEN			0x01000000
#define DFS_F_DIRECTORY		0x02000000
#define DFS_F_EOF			0x04000000
#define DFS_F_ERR			0x08000000

/* Seek flags */
#define DFS_SEEK_SET         0
#define DFS_SEEK_CUR         1
#define DFS_SEEK_END         2

/* Stat codes */
#define DFS_S_IFMT		00170000
#define DFS_S_IFSOCK	0140000
#define DFS_S_IFLNK		0120000
#define DFS_S_IFREG		0100000
#define DFS_S_IFBLK		0060000
#define DFS_S_IFDIR  	0040000
#define DFS_S_IFCHR  	0020000
#define DFS_S_IFIFO  	0010000
#define DFS_S_ISUID  	0004000
#define DFS_S_ISGID  	0002000
#define DFS_S_ISVTX  	0001000

#define DFS_S_ISLNK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFLNK)
#define DFS_S_ISREG(m)	(((m) & DFS_S_IFMT) == DFS_S_IFREG)
#define DFS_S_ISDIR(m)	(((m) & DFS_S_IFMT) == DFS_S_IFDIR)
#define DFS_S_ISCHR(m)	(((m) & DFS_S_IFMT) == DFS_S_IFCHR)
#define DFS_S_ISBLK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFBLK)
#define DFS_S_ISFIFO(m)	(((m) & DFS_S_IFMT) == DFS_S_IFIFO)
#define DFS_S_ISSOCK(m)	(((m) & DFS_S_IFMT) == DFS_S_IFSOCK)

#define DFS_S_IRWXU 	00700
#define DFS_S_IRUSR 	00400
#define DFS_S_IWUSR 	00200
#define DFS_S_IXUSR 	00100

#define DFS_S_IRWXG 	00070
#define DFS_S_IRGRP 	00040
#define DFS_S_IWGRP 	00020
#define DFS_S_IXGRP 	00010

#define DFS_S_IRWXO 	00007
#define DFS_S_IROTH 	00004
#define DFS_S_IWOTH 	00002
#define DFS_S_IXOTH 	00001

#define DEVICE_GETGEOME 		0
#define DEVICE_GETINFO			1
#define DEVICE_FORMAT 			2
#define DEVICE_CLEAN_SECTOR 	3

struct device_geometry
{
	rt_uint32_t sector_count;		/* count of sectors */
	rt_uint32_t cylinder_count;		/* count of cylinder */
	rt_uint32_t sectors_per_track;	/* number of sectors per track */
	rt_uint32_t head_count;			/* count of head */
	rt_uint32_t bytes_per_sector;	/* number of bytes per sector */
};

struct dfs_stat
{
	rt_device_t st_dev;
	rt_uint16_t st_mode;
	rt_uint32_t st_size;
	rt_time_t  	st_mtime;
	rt_uint32_t st_blksize;
};
#define stat dfs_stat

/* File types */
#define FT_REGULAR		0	/* regular file */
#define FT_SOCKET		1	/* socket file  */
#define FT_DIRECTORY	2	/* directory    */
#define FT_USER			3	/* user defined */

/* file descriptor */
struct dfs_fd
{
    char path[DFS_PATH_MAX + 1];/* Name (below mount point) */
    int type;					/* Type (regular or socket) */
    int ref_count;				/* Descriptor reference count */

    struct dfs_filesystem* fs;	/* Resident file system */

    rt_uint32_t flags;			/* Descriptor flags */
    rt_size_t 	size;			/* Size in bytes */
    rt_off_t  	pos;			/* Current file position */

    void *data;					/* Specific file system data */
};

#define DFS_DT_UNKNOWN	0x00
#define DFS_DT_REG		0x01
#define DFS_DT_DIR		0x02

struct dfs_dirent
{
	rt_uint8_t d_type;				/* The type of the file */
	rt_uint8_t d_namlen;			/* The length of the not including the terminating null file name */
	rt_uint16_t d_reclen;				/* length of this record */
	char   d_name[256];			/* The null-terminated file name */
};
#define dirent dfs_dirent

struct dfs_session
{
	rt_mailbox_t mbox;
};

#endif
