#ifndef JFFS2_CONFIG_H
#define JFFS2_CONFIG_H

#define __ECOS  /* must be defined */

#define FILE_PATH_MAX                128  /* the longest file path */
#define CONFIG_JFFS2_ENTRY_NAME_MAX  23
#define	JFFS2_NAME_MAX   CONFIG_JFFS2_ENTRY_NAME_MAX  
#define	JFFS2_PATH_MAX   FILE_PATH_MAX

#define DEVICE_PART_MAX   1  /* the max partions on a nand deivce*/

/* memory page size in kernel/asm/page.h, it is correspond with flash read/write
 * option, so this size has a great impact on reading/writing speed */
#define CONFIG_JFFS2_PAGE_SHIFT  12  /* (1<<12) 4096bytes*/

/* jffs2 support relative dir, command "ls" will get
 * +-------------------------------+
 * |   finsh>>ls("/")              |
 * |   Directory /:                |
 * |   .                   <DIR>   |
 * |   ..                  <DIR>   |
 * |   dir1                <DIR>   |
 * +-------------------------------+
 */
#define CONFIG_JFFS2_NO_RELATIVEDIR

//#define CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE
#if defined(CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE)
	#define CYGPKG_FILEIO_DIRENT_DTYPE
#endif

#define CYGOPT_FS_JFFS2_WRITE /* if not defined, jffs2 is read only*/

/* jffs2 debug output opion */
#define CONFIG_JFFS2_FS_DEBUG 		0  /* 1 or 2 */

/* jffs2 gc thread section */
//#define CYGOPT_FS_JFFS2_GCTHREAD
#define CYGNUM_JFFS2_GC_THREAD_PRIORITY  (RT_THREAD_PRIORITY_MAX-2) /* GC thread's priority */
#define CYGNUM_JFFS2_GS_THREAD_TICKS  20  /* event timeout ticks */
#define CYGNUM_JFFS2_GC_THREAD_TICKS  20  /* GC thread's running ticks */

//#define CONFIG_JFFS2_FS_WRITEBUFFER /* should not be enabled */

/* zlib section*/
//#define CONFIG_JFFS2_ZLIB
//#define CONFIG_JFFS2_RTIME
//#define CONFIG_JFFS2_RUBIN
//#define CONFIG_JFFS2_CMODE_NONE
//#define CONFIG_JFFS2_CMODE_SIZE

#endif
