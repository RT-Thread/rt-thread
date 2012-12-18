#ifndef CYGONCE_ISO_FCNTL_H
#define CYGONCE_ISO_FCNTL_H
#if defined(__CC_ARM) || defined(MSVC)
/* File access modes used for open() and fnctl() */
#define O_RDONLY     (1<<0)   /* Open for reading only */
#define O_WRONLY     (1<<1)   /* Open for writing only */
#define O_RDWR       (O_RDONLY|O_WRONLY) /* Open for reading and writing */

/* File access mode mask */
#define O_ACCMODE    (O_RDONLY|O_RDWR|O_WRONLY)

/* open() mode flags */

#define O_CREAT      (1<<3)    /* Create file it it does not exist */
#define O_EXCL       (1<<4)    /* Exclusive use */
#define O_NOCTTY     (1<<5)    /* Do not assign a controlling terminal */
#define O_TRUNC      (1<<6)    /* Truncate */

/* File status flags used for open() and fcntl() */
#define O_APPEND     (1<<7)    /* Set append mode */
#define O_DSYNC      (1<<8)    /* Synchronized I/O data integrity writes */
#define O_NONBLOCK   (1<<9)    /* No delay */
#define O_RSYNC      (1<<10)   /* Synchronized read I/O */
#define O_SYNC       (1<<11)   /* Synchronized I/O file integrity writes */

/*------------------------------------------------------------------------*/
/* for dfs_jffs2.c                                                             */
/*------------------------------------------------------------------------*/
/* File access modes used for open() and fnctl() */
#define JFFS2_O_RDONLY     (1<<0)   /* Open for reading only */
#define JFFS2_O_WRONLY     (1<<1)   /* Open for writing only */
#define JFFS2_O_RDWR       (O_RDONLY|O_WRONLY) /* Open for reading and writing */

/* File access mode mask */
#define JFFS2_O_ACCMODE    (O_RDONLY|O_RDWR|O_WRONLY)

/* open() mode flags */

#define JFFS2_O_CREAT      (1<<3)    /* Create file it it does not exist */
#define JFFS2_O_EXCL       (1<<4)    /* Exclusive use */
#define JFFS2_O_NOCTTY     (1<<5)    /* Do not assign a controlling terminal */
#define JFFS2_O_TRUNC      (1<<6)    /* Truncate */

/* File status flags used for open() and fcntl() */
#define JFFS2_O_APPEND     (1<<7)    /* Set append mode */
#define JFFS2_O_DSYNC      (1<<8)    /* Synchronized I/O data integrity writes */
#define JFFS2_O_NONBLOCK   (1<<9)    /* No delay */
#define JFFS2_O_RSYNC      (1<<10)   /* Synchronized read I/O */
#define JFFS2_O_SYNC       (1<<11)   /* Synchronized I/O file integrity writes */

#elif defined(__GNUC__)

/*------------------------------------------------------------------------*/
/* for dfs_jffs2.c                                                        */
/*------------------------------------------------------------------------*/
/* File access modes used for open() and fnctl() */
#define JFFS2_O_RDONLY     (DFS_O_RDONLY)   /* Open for reading only */
#define JFFS2_O_WRONLY     (DFS_O_WRONLY)   /* Open for writing only */
#define JFFS2_O_RDWR       (DFS_O_RDONLY|DFS_O_WRONLY) /* Open for reading and writing */

/* File access mode mask */
#define JFFS2_O_ACCMODE    (DFS_O_RDONLY|DFS_O_RDWR|DFS_O_WRONLY)

/* open() mode flags */

#define JFFS2_O_CREAT      (DFS_O_CREAT)   /* Create file it it does not exist */
#define JFFS2_O_EXCL       (DFS_O_EXCL)    /* Exclusive use */
#define JFFS2_O_NOCTTY     (DFS_O_NOCTTY)  /* Do not assign a controlling terminal */
#define JFFS2_O_TRUNC      (DFS_O_TRUNC)   /* Truncate */

/* File status flags used for open() and fcntl() */
#define JFFS2_O_APPEND     (DFS_O_APPEND)  /* Set append mode */
#define JFFS2_O_DSYNC      (DFS_O_DSYNC)   /* Synchronized I/O data integrity writes */
#define JFFS2_O_NONBLOCK   (DFS_O_NONBLOCK)/* No delay */
#define JFFS2_O_RSYNC      (DFS_O_RSYNC)   /* Synchronized read I/O */
#define JFFS2_O_SYNC       (DFS_O_SYNC)    /* Synchronized I/O file integrity writes */

#endif
#endif
/* EOF fcntl.h */
