#ifndef JFFS2_CONFIG_H
#define JFFS2_CONFIG_H

#define __ECOS  /* must be defined */

#define FILE_PATH_MAX   256 /* the longest file path */

#define DEVICE_PART_MAX   1  /* the max partions on a nand deivce*/

#define CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE /* should be enabled */
#if defined(CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE)
	#define CYGPKG_FILEIO_DIRENT_DTYPE
#endif

#define CYGOPT_FS_JFFS2_WRITE /* if not defined, jffs2 is read only*/

/* jffs2 debug output opion */
#define CONFIG_JFFS2_FS_DEBUG 		0  /* 1 or 2 */

/* jffs2 gc thread section */
//#define CYGOPT_FS_JFFS2_GCTHREAD
#define CYGNUM_JFFS2_GC_THREAD_PRIORITY  20 
#define CYGNUM_JFFS2_GS_THREAD_TICKS  20
#define CYGNUM_JFFS2_GC_THREAD_TICKS  20

//#define CONFIG_JFFS2_FS_WRITEBUFFER /* should not be enabled */

/* zlib section*/
//#define CONFIG_JFFS2_ZLIB
//#define CONFIG_JFFS2_RTIME
//#define CONFIG_JFFS2_RUBIN
//#define CONFIG_JFFS2_CMODE_NONE
//#define CONFIG_JFFS2_CMODE_SIZE

#endif
