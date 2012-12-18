#ifndef _PORTING_H 
#define _PORTING_H

#include "jffs2_config.h"
/* the following should be same with os_sys_stat.h */
#define JFFS2_S_IFMT	 0x000003FF
#define JFFS2_S_IFDIR	 (1<<0)
#define JFFS2_S_IFREG	 (1<<3)

struct jffs2_fs_info
{
	unsigned sector_size; /* a erasing block size*/
	unsigned nr_blocks; /* number of blocks in flash */
	unsigned free_size;
};

struct jffs2_stat {
    unsigned long   st_mode;     /* File mode */
    unsigned int    st_ino;      /* File serial number */
    unsigned int    st_dev;      /* ID of device containing file */
    unsigned short  st_nlink;    /* Number of hard links */
    unsigned short  st_uid;      /* User ID of the file owner */
    unsigned short  st_gid;      /* Group ID of the file's group */
    long  st_size;     /* File size (regular files only) */
    long  st_atime;    /* Last access time */
    long  st_mtime;    /* Last data modification time */
    long  st_ctime;    /* Last file status change time */
};

struct jffs2_dirent
{
#ifdef CYGPKG_FILEIO_DIRENT_DTYPE

	unsigned long  d_type; // Only supported with FATFS, RAMFS, ROMFS,
	// and JFFS2.
	// d_type is not part of POSIX so
	// should be used with caution.
#endif
	char        d_name[JFFS2_NAME_MAX+1];
};

extern cyg_fileops jffs2_fileops;
extern cyg_fileops jffs2_dirops;
extern struct cyg_fstab_entry jffs2_fste;

time_t jffs2_get_timestamp(void);
void jffs2_get_info_from_sb(void * data, struct jffs2_fs_info * info);
int jffs2_porting_stat(cyg_mtab_entry * mte, cyg_dir dir, const char *name,
		      void * stat_buf);

#endif
