#ifndef CYGONCE_ISO_FCNTL_H
#define CYGONCE_ISO_FCNTL_H

/*------------------------------------------------------------------------*/
/* for dfs_jffs2.c                                                        */
/*------------------------------------------------------------------------*/
/* File access modes used for open() and fnctl() */
#define JFFS2_O_RDONLY     (O_RDONLY)   /* Open for reading only */
#define JFFS2_O_WRONLY     (O_WRONLY)   /* Open for writing only */
#define JFFS2_O_RDWR       (O_RDONLY|O_WRONLY) /* Open for reading and writing */

/* File access mode mask */
#define JFFS2_O_ACCMODE    (O_RDONLY|O_RDWR|O_WRONLY)

/* open() mode flags */

#define JFFS2_O_CREAT      (O_CREAT)   /* Create file it it does not exist */
#define JFFS2_O_EXCL       (O_EXCL)    /* Exclusive use */
#define JFFS2_O_NOCTTY     (O_NOCTTY)  /* Do not assign a controlling terminal */
#define JFFS2_O_TRUNC      (O_TRUNC)   /* Truncate */

/* File status flags used for open() and fcntl() */
#define JFFS2_O_APPEND     (O_APPEND)  /* Set append mode */
#define JFFS2_O_DSYNC      (O_DSYNC)   /* Synchronized I/O data integrity writes */
#define JFFS2_O_NONBLOCK   (O_NONBLOCK)/* No delay */
#define JFFS2_O_RSYNC      (O_RSYNC)   /* Synchronized read I/O */
#define JFFS2_O_SYNC       (O_SYNC)    /* Synchronized I/O file integrity writes */

#endif

/* EOF fcntl.h */
