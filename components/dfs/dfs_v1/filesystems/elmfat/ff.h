/*----------------------------------------------------------------------------/
/  FatFs - Generic FAT Filesystem module  R0.16                               /
/-----------------------------------------------------------------------------/
/
/ Copyright (C) 2025, ChaN, all right reserved.
/
/ FatFs module is an open source software. Redistribution and use of FatFs in
/ source and binary forms, with or without modification, are permitted provided
/ that the following condition is met:

/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/
/----------------------------------------------------------------------------*/


#ifndef FF_DEFINED
#define FF_DEFINED	80386	/* Revision ID */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(FFCONF_DEF)
#include "ffconf.h"		/* FatFs configuration options */
#endif
#if FF_DEFINED != FFCONF_DEF
#error Wrong configuration file (ffconf.h).
#endif


/* Integer types used for FatFs API */

#if defined(_WIN32)		/* Windows VC++ (for development only) */
#define FF_INTDEF 2
#include <windows.h>
typedef unsigned __int64 QWORD;
#include <float.h>
#define isnan(v) _isnan(v)
#define isinf(v) (!_finite(v))

#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__cplusplus)	/* C99 or later */
#define FF_INTDEF 2
#include <stdint.h>
typedef unsigned int	UINT;	/* int must be 16-bit or 32-bit */
typedef unsigned char	BYTE;	/* char must be 8-bit */
typedef uint16_t		WORD;	/* 16-bit unsigned */
typedef uint32_t		DWORD;	/* 32-bit unsigned */
typedef uint64_t		QWORD;	/* 64-bit unsigned */
typedef WORD			WCHAR;	/* UTF-16 code unit */

#else  	/* Earlier than C99 */
#define FF_INTDEF 1
typedef unsigned int	UINT;	/* int must be 16-bit or 32-bit */
typedef unsigned char	BYTE;	/* char must be 8-bit */
typedef unsigned short	WORD;	/* short must be 16-bit */
typedef unsigned long	DWORD;	/* long must be 32-bit */
typedef WORD			WCHAR;	/* UTF-16 code unit */
#endif


/* Type of file size and LBA variables */

#if FF_FS_EXFAT
#if FF_INTDEF != 2
#error exFAT feature wants C99 or later
#endif
typedef QWORD FSIZE_t;
#if FF_LBA64
typedef QWORD LBA_t;
#else
typedef DWORD LBA_t;
#endif
#else
#if FF_LBA64
#error exFAT needs to be enabled when enable 64-bit LBA
#endif
typedef DWORD FSIZE_t;
typedef DWORD LBA_t;
#endif



/* Type of path name strings on FatFs API (TCHAR) */

#if FF_USE_LFN && FF_LFN_UNICODE == 1 	/* Unicode in UTF-16 encoding */
typedef WCHAR TCHAR;
#define _T(x) L ## x
#define _TEXT(x) L ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 2	/* Unicode in UTF-8 encoding */
typedef char TCHAR;
#define _T(x) u8 ## x
#define _TEXT(x) u8 ## x
#elif FF_USE_LFN && FF_LFN_UNICODE == 3	/* Unicode in UTF-32 encoding */
typedef DWORD TCHAR;
#define _T(x) U ## x
#define _TEXT(x) U ## x
#elif FF_USE_LFN && (FF_LFN_UNICODE < 0 || FF_LFN_UNICODE > 3)
#error Wrong FF_LFN_UNICODE setting
#else									/* ANSI/OEM code in SBCS/DBCS */
typedef char TCHAR;
#define _T(x) x
#define _TEXT(x) x
#endif



/* Definitions of volume management */

#if FF_MULTI_PARTITION		/* Multiple partition configuration */
typedef struct {
	BYTE pd;	/* Associated physical drive */
	BYTE pt;	/* Associated partition (0:Auto detect, 1-4:Forced partition) */
} PARTITION;
extern PARTITION VolToPart[];	/* Volume to partition mapping table */
#endif

#if FF_STR_VOLUME_ID
#ifndef FF_VOLUME_STRS
extern const char* VolumeStr[FF_VOLUMES];	/* User defined volume ID table */
#endif
#endif


/* Current working directory structure (FFXCWDS) */

#if FF_FS_EXFAT && FF_FS_RPATH
#if FF_PATH_DEPTH < 1
#error FF_PATH_DEPTH must not be zero
#endif
typedef struct {
	DWORD	d_scl;		/* Directory start cluster (0:root dir) */
	DWORD	d_size;		/* Size of directory (b7-b0: cluster chain status) (invalid if d_scl == 0) */
	DWORD	nxt_ofs;	/* Offset of entry of next dir in this directory (invalid if last link) */
} FFXCWDL;
typedef struct {
	UINT	depth;		/* Current directory depth (0:root dir) */
	FFXCWDL	tbl[FF_PATH_DEPTH + 1];	/* Directory chain of current working directory path */
} FFXCWDS;
#endif


/* Filesystem object structure (FATFS) */

typedef struct {
	BYTE	fs_type;	/* Filesystem type (0:not mounted) */
	BYTE	pdrv;		/* Physical drive that holds this volume */
	BYTE	ldrv;		/* Logical drive number (used only when FF_FS_REENTRANT) */
	BYTE	n_fats;		/* Number of FATs (1 or 2) */
	BYTE	wflag;		/* win[] status (b0:dirty) */
	BYTE	fsi_flag;	/* Allocation information control (b7:disabled, b0:dirty) */
	WORD	id;			/* Volume mount ID */
	WORD	n_rootdir;	/* Number of root directory entries (FAT12/16) */
	WORD	csize;		/* Cluster size [sectors] */
#if FF_MAX_SS != FF_MIN_SS
	WORD	ssize;		/* Sector size (512, 1024, 2048 or 4096) */
#endif
#if FF_USE_LFN
	WCHAR*	lfnbuf;		/* Pointer to LFN working buffer */
#endif
#if !FF_FS_READONLY
	DWORD	last_clst;	/* Last allocated cluster (invalid if >=n_fatent) */
	DWORD	free_clst;	/* Number of free clusters (invalid if >=fs->n_fatent-2) */
#endif
#if FF_FS_RPATH
	DWORD	cdir;		/* Current directory start cluster (0:root) */
#endif
	DWORD	n_fatent;	/* Number of FAT entries (number of clusters + 2) */
	DWORD	fsize;		/* Number of sectors per FAT */
	LBA_t	winsect;	/* Current sector appearing in the win[] */
	LBA_t	volbase;	/* Volume base sector */
	LBA_t	fatbase;	/* FAT base sector */
	LBA_t	dirbase;	/* Root directory base sector (FAT12/16) or cluster (FAT32/exFAT) */
	LBA_t	database;	/* Data base sector */
#if FF_FS_EXFAT
	LBA_t	bitbase;	/* Allocation bitmap base sector */
	BYTE*	dirbuf;		/* Pointer to directory entry block buffer */
#if FF_FS_RPATH
	FFXCWDS	xcwds;		/* Crrent working directory structure */
	FFXCWDS	xcwds2;		/* Working buffer to follow the path */
#endif
#endif
	BYTE	win[FF_MAX_SS];	/* Disk access window for directory, FAT (and file data in tiny cfg) */
} FATFS;



/* Object ID and allocation information (FFOBJID) */

typedef struct {
	FATFS*	fs;			/* Pointer to the volume holding this object */
	WORD	id;			/* Volume mount ID when this object was opened */
	BYTE	attr;		/* Object attribute */
	BYTE	stat;		/* Object chain status (exFAT: b1-0: =0:not contiguous, =2:contiguous, =3:fragmented in this session, b2:sub-directory stretched) */
	DWORD	sclust;		/* Object data cluster (0:no data or root directory) */
	FSIZE_t	objsize;	/* Object size (valid when sclust != 0) */
#if FF_FS_EXFAT
	DWORD	n_cont;		/* Size of first fragment - 1 (valid when stat == 3) */
	DWORD	n_frag;		/* Size of last fragment needs to be written to FAT (valid when not zero) */
	DWORD	c_scl;		/* Cluster of directory holding this object (valid when sclust != 0) */
	DWORD	c_size;		/* Size of directory holding this object (b7-b0: allocation status, valid when c_scl != 0) */
	DWORD	c_ofs;		/* Offset of entry in the holding directory */
#endif
#if FF_FS_LOCK
	UINT	lockid;		/* File lock ID origin from 1 (index of file semaphore table Files[]) */
#endif
} FFOBJID;



/* File object structure (FIL) */

typedef struct {
	FFOBJID	obj;		/* Object identifier (must be the 1st member to detect invalid object pointer) */
	BYTE	flag;		/* File status flags */
	BYTE	err;		/* Abort flag (error code) */
	FSIZE_t	fptr;		/* File read/write pointer (0 on open) */
	DWORD	clust;		/* Current cluster of fptr (invalid when fptr is 0) */
	LBA_t	sect;		/* Sector number appearing in buf[] (0:invalid) */
#if !FF_FS_READONLY
	LBA_t	dir_sect;	/* Sector number containing the directory entry (not used in exFAT) */
	BYTE*	dir_ptr;	/* Pointer to the directory entry in the win[] (not used in exFAT) */
#endif
#if FF_USE_FASTSEEK
	DWORD*	cltbl;		/* Pointer to the cluster link map table (nulled on open; set by application) */
#endif
#if !FF_FS_TINY
	BYTE	buf[FF_MAX_SS];	/* File private data read/write window */
#endif
} FIL;



/* Directory object structure (DIR) */

typedef struct {
	FFOBJID	obj;		/* Object identifier (must be the 1st member to detect invalid object pointer) */
	DWORD	dptr;		/* Current read/write offset */
	DWORD	clust;		/* Current cluster */
	LBA_t	sect;		/* Current sector (0:no more item to read) */
	BYTE*	dir;		/* Pointer to the directory item in the win[] in filesystem object */
	BYTE	fn[12];		/* SFN (in/out) {body[0-7],ext[8-10],status[11]} */
#if FF_USE_LFN
	DWORD	blk_ofs;	/* Offset of current entry block being processed (0xFFFFFFFF:invalid) */
#endif
#if FF_USE_FIND
	const TCHAR *pat;	/* Pointer to the name matching pattern */
#endif
} DIR;



/* File/directory information structure (FILINFO) */

typedef struct {
	FSIZE_t	fsize;			/* File size (invalid for directory) */
	WORD	fdate;			/* Date of file modification or directory creation */
	WORD	ftime;			/* Time of file modification or directory creation */
#if FF_FS_CRTIME
	WORD	crdate;			/* Date of object createion */
	WORD	crtime;			/* Time of object createion */
#endif
	BYTE	fattrib;		/* Object attribute */
#if FF_USE_LFN
	TCHAR	altname[FF_SFN_BUF + 1];/* Alternative object name */
	TCHAR	fname[FF_LFN_BUF + 1];	/* Primary object name */
#else
	TCHAR	fname[12 + 1];	/* Object name */
#endif
} FILINFO;



/* Format parameter structure (MKFS_PARM) used for f_mkfs() */

typedef struct {
	BYTE fmt;			/* Format option (FM_FAT, FM_FAT32, FM_EXFAT and FM_SFD) */
	BYTE n_fat;			/* Number of FATs */
	UINT align;			/* Data area alignment (sector) */
	UINT n_root;		/* Number of root directory entries */
	DWORD au_size;		/* Cluster size (byte) */
} MKFS_PARM;



/* File function return code (FRESULT) */

typedef enum {
	FR_OK = 0,				/* (0) Function succeeded */
	FR_DISK_ERR,			/* (1) A hard error occurred in the low level disk I/O layer */
	FR_INT_ERR,				/* (2) Assertion failed */
	FR_NOT_READY,			/* (3) The physical drive does not work */
	FR_NO_FILE,				/* (4) Could not find the file */
	FR_NO_PATH,				/* (5) Could not find the path */
	FR_INVALID_NAME,		/* (6) The path name format is invalid */
	FR_DENIED,				/* (7) Access denied due to a prohibited access or directory full */
	FR_EXIST,				/* (8) Access denied due to a prohibited access */
	FR_INVALID_OBJECT,		/* (9) The file/directory object is invalid */
	FR_WRITE_PROTECTED,		/* (10) The physical drive is write protected */
	FR_INVALID_DRIVE,		/* (11) The logical drive number is invalid */
	FR_NOT_ENABLED,			/* (12) The volume has no work area */
	FR_NO_FILESYSTEM,		/* (13) Could not find a valid FAT volume */
	FR_MKFS_ABORTED,		/* (14) The f_mkfs function aborted due to some problem */
	FR_TIMEOUT,				/* (15) Could not take control of the volume within defined period */
	FR_LOCKED,				/* (16) The operation is rejected according to the file sharing policy */
	FR_NOT_ENOUGH_CORE,		/* (17) LFN working buffer could not be allocated, given buffer size is insufficient or too deep path */
	FR_TOO_MANY_OPEN_FILES,	/* (18) Number of open files > FF_FS_LOCK */
	FR_INVALID_PARAMETER	/* (19) Given parameter is invalid */
} FRESULT;




/*--------------------------------------------------------------*/
/* FatFs Module Application Interface                           */
/*--------------------------------------------------------------*/

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* Open or create a file */
FRESULT f_close (FIL* fp);											/* Close an open file object */
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* Read data from the file */
FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	/* Write data to the file */
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								/* Move file pointer of the file object */
FRESULT f_truncate (FIL* fp);										/* Truncate the file */
FRESULT f_sync (FIL* fp);											/* Flush cached data of the writing file */
FRESULT f_opendir (DIR* dp, const TCHAR* path);						/* Open a directory */
FRESULT f_closedir (DIR* dp);										/* Close an open directory */
FRESULT f_readdir (DIR* dp, FILINFO* fno);							/* Read a directory item */
FRESULT f_findfirst (DIR* dp, FILINFO* fno, const TCHAR* path, const TCHAR* pattern);	/* Find first file */
FRESULT f_findnext (DIR* dp, FILINFO* fno);							/* Find next file */
FRESULT f_mkdir (const TCHAR* path);								/* Create a sub directory */
FRESULT f_unlink (const TCHAR* path);								/* Delete an existing file or directory */
FRESULT f_rename (const TCHAR* path_old, const TCHAR* path_new);	/* Rename/Move a file or directory */
FRESULT f_stat (const TCHAR* path, FILINFO* fno);					/* Get file status */
FRESULT f_chmod (const TCHAR* path, BYTE attr, BYTE mask);			/* Change attribute of a file/dir */
FRESULT f_utime (const TCHAR* path, const FILINFO* fno);			/* Change timestamp of a file/dir */
FRESULT f_chdir (const TCHAR* path);								/* Change current directory */
FRESULT f_chdrive (const TCHAR* path);								/* Change current drive */
FRESULT f_getcwd (TCHAR* buff, UINT len);							/* Get current directory */
FRESULT f_getfree (const TCHAR* path, DWORD* nclst, FATFS** fatfs);	/* Get number of free clusters on the drive */
FRESULT f_getlabel (const TCHAR* path, TCHAR* label, DWORD* vsn);	/* Get volume label */
FRESULT f_setlabel (const TCHAR* label);							/* Set volume label */
FRESULT f_forward (FIL* fp, UINT(*func)(const BYTE*,UINT), UINT btf, UINT* bf);	/* Forward data to the stream */
FRESULT f_expand (FIL* fp, FSIZE_t fsz, BYTE opt);					/* Allocate a contiguous block to the file */
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */
FRESULT f_mkfs (const TCHAR* path, const MKFS_PARM* opt, void* work, UINT len);	/* Create a FAT volume */
FRESULT f_fdisk (BYTE pdrv, const LBA_t ptbl[], void* work);		/* Divide a physical drive into some partitions */
FRESULT f_setcp (WORD cp);											/* Set current code page */
int f_putc (TCHAR c, FIL* fp);										/* Put a character to the file */
int f_puts (const TCHAR* str, FIL* cp);								/* Put a string to the file */
int f_printf (FIL* fp, const TCHAR* str, ...);						/* Put a formatted string to the file */
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* Get a string from the file */

/* Some API fucntions are implemented as macro */

#define f_eof(fp) ((int)((fp)->fptr == (fp)->obj.objsize))
#define f_error(fp) ((fp)->err)
#define f_tell(fp) ((fp)->fptr)
#define f_size(fp) ((fp)->obj.objsize)
#define f_rewind(fp) f_lseek((fp), 0)
#define f_rewinddir(dp) f_readdir((dp), 0)
#define f_rmdir(path) f_unlink(path)
#define f_unmount(path) f_mount(0, path, 0)




/*--------------------------------------------------------------*/
/* Additional Functions                                         */
/*--------------------------------------------------------------*/

/* RTC function (provided by user) */
#if !FF_FS_READONLY && !FF_FS_NORTC
DWORD get_fattime (void);	/* Get current time */
#endif


/* LFN support functions (defined in ffunicode.c) */

#if FF_USE_LFN >= 1
WCHAR ff_oem2uni (WCHAR oem, WORD cp);	/* OEM code to Unicode conversion */
WCHAR ff_uni2oem (DWORD uni, WORD cp);	/* Unicode to OEM code conversion */
DWORD ff_wtoupper (DWORD uni);			/* Unicode upper-case conversion */
#endif


/* O/S dependent functions (samples available in ffsystem.c) */

#if FF_USE_LFN == 3		/* Dynamic memory allocation */
void* ff_memalloc (UINT msize);		/* Allocate memory block */
void ff_memfree (void* mblock);		/* Free memory block */
#endif
#if FF_FS_REENTRANT		/* Sync functions */
int ff_mutex_create (int vol);		/* Create a sync object */
void ff_mutex_delete (int vol);		/* Delete a sync object */
int ff_mutex_take (int vol);		/* Lock sync object */
void ff_mutex_give (int vol);		/* Unlock sync object */
#endif




/*--------------------------------------------------------------*/
/* Flags and Offset Address                                     */
/*--------------------------------------------------------------*/

/* File access mode and open method flags (3rd argument of f_open function) */
#define	FA_READ				0x01
#define	FA_WRITE			0x02
#define	FA_OPEN_EXISTING	0x00
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define	FA_OPEN_APPEND		0x30

/* Fast seek controls (2nd argument of f_lseek function) */
#define CREATE_LINKMAP	((FSIZE_t)0 - 1)

/* Format options (2nd argument of f_mkfs function) */
#define FM_FAT		0x01
#define FM_FAT32	0x02
#define FM_EXFAT	0x04
#define FM_ANY		0x07
#define FM_SFD		0x08

/* Filesystem type (FATFS.fs_type) */
#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3
#define FS_EXFAT	4

/* File attribute bits for directory entry (FILINFO.fattrib) */
#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */


#ifdef __cplusplus
}
#endif

#endif /* FF_DEFINED */
