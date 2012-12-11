#ifndef __TYPES_H__
#define __TYPES_H__

#include <rtthread.h>

typedef long    	off_t;
typedef rt_size_t 	size_t;
typedef signed long ssize_t;		/* Used for a count of bytes or an error indication. */

typedef rt_uint8_t 	u_char;
typedef rt_uint16_t u_short;
typedef rt_ubase_t 	u_int;
typedef rt_uint32_t u_long;

typedef rt_time_t time_t;
typedef int mode_t;

typedef unsigned long clockid_t;
typedef int pid_t;

#ifndef NULL
#define NULL RT_NULL
#endif

#define __u_char_defined

#endif
