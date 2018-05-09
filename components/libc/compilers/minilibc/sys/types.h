#ifndef __TYPES_H__
#define __TYPES_H__

typedef long        off_t;
typedef unsigned long size_t;
typedef signed long   ssize_t;      /* Used for a count of bytes or an error indication. */

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef unsigned long  u_long;

typedef int mode_t;

typedef unsigned long clockid_t;
typedef int pid_t;

typedef	unsigned long clock_t; /* clock() */

#ifndef NULL
#define NULL        (0)
#endif

#define __u_char_defined

#endif

